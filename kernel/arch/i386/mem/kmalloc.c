/*
*This file is part of Dan's Open Source Disk Operating System (DOSDOS).
*
*    DOSDOS is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    DOSDOS is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with DOSDOS.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <kernel/mem/kmalloc.h>

memheader_t* memstart = NULL;

void print_memheader(memheader_t* cur){
  printf("\nAddr: %p", (void*) cur);
  printf("\nSize: %d", (int) (*cur).size);
  printf("\nStatus: %p\n", (void*) (*cur).status);
}

inline memheader_t* prev_memheader(memheader_t* current){
  return (memheader_t*) ((*current).status & 0xFFFFFFFE);
}

inline size_t memheader_space(memheader_t* cur, memheader_t* next){
  return (size_t) (( ((void*)next) - ((void*)cur)) - sizeof(memheader_t));
}

//numextrablocks is 0 if we are only registering one block (firstblock)
void register_blocks(size_t firstblock, size_t numextrablocks){
  //TODO: Register blocks in the Paging Directory as belonging to the kernel

  //This code is just so our compiler won't yell at us for warnings
  firstblock = numextrablocks;
  numextrablocks = firstblock;
}

memheader_t* next_memheader(memheader_t* current){

  memheader_t* nextheader;
  
  if((*current).size){
    nextheader = (((void*)current) + (*current).size + sizeof(memheader_t));
  }else{
    nextheader = prev_memheader(current);
  }

  return nextheader;
}

inline bool is_blockstart_header(memheader_t* current){
  return ((!prev_memheader(current)) || (next_memheader(prev_memheader(current)) != current));
}

memheader_t* final_memheader(){

  memheader_t* trav = memstart;
  memheader_t* prev = NULL;
  
  while(trav){
    prev = trav;
    trav = next_memheader(trav);
  }
  
  return prev;
}

bool section_spansblocks(memheader_t* header){
  void* next = next_memheader(header);
  return (addr_to_block(next) != addr_to_block(header));
}

inline bool is_free(memheader_t* head){
  return (!((*head).status % 2));
}

void set_memheader_prev(memheader_t* cur, memheader_t* prev){
  //If cur is the block-end header, then we actually want the next header
  //to point backwards
  if( !(*cur).size )
    cur = next_memheader(cur);

  //If our original cur was the final block header, then it doesn't have a next
  //so we can't have its next point back to a previous.  Do nothing then
  if(cur){
    uint32_t status = !is_free(cur);
    (*cur).status = (uint32_t) ( (uint32_t) prev  | status);
  }
}

memheader_t* first_fit_fwd(const size_t req){

  for(memheader_t* trav = memstart; trav; trav = next_memheader(trav) ){
    if( ( (*trav).size >= req) && is_free(trav) )
      return trav;
  }

  return NULL;
}

void printheaders(){
  memheader_t* trav = memstart;
  while(trav){
    print_memheader(trav);
    trav = next_memheader(trav);
  }
}

memheader_t* request_blocks(size_t size){

  memheader_t* blockstart;
  
  //Figure out how many blocks we need to request
  //We need enough space for 3 headers, our requested size, and a minimum
  //sized-section of two bytes for our intermediary blank space
  size_t extra_blocks_to_get = ( ( (size + 2) + (3 * sizeof(memheader_t) ) ) / 4096);
  if(!extra_blocks_to_get){
    blockstart = (memheader_t*) physmm_alloc_blocks(extra_blocks_to_get + 1);
  }else{
    blockstart = (memheader_t*) physmm_alloc_block();
  }
  
  //Register our newly alloc'd blocks in the page-dir as belonging to the kernel
  register_blocks(addr_to_block(blockstart), extra_blocks_to_get);
  
  ++extra_blocks_to_get;
  
  (*blockstart).size = size;
  (*blockstart).status = 0x00000001;
  
  //Our size 0 pointer at the end of the block
  memheader_t* last = (((void*)blockstart) + (4096 * extra_blocks_to_get) ) - sizeof(memheader_t);
  (*last).status = 0;
  (*last).size = 0;

  //Use the next memheader and set the rest of the space between our requested
  //space and the end of the block as free.
  //Then set the last part of our last block as a header with size 0
  memheader_t* next = next_memheader(blockstart);
  (*next).status = (uint32_t) (((uint32_t) blockstart) & 0xFFFFFFFE);
  (*next).size = memheader_space(next, last);

  return blockstart;
}

void* kmalloc(size_t size){

  //Size cannot be 0
  if(!size)
    return NULL;
  
  //Size must always be even
  if(size % 2)
    ++size;

  //If this our first ever request, then do some setup
  if(!memstart){
    memstart = request_blocks(size);
    return ((void*) memstart + sizeof(memheader_t));
  }

  //We do not need to initialize.  Do we need to allocate more blocks?
  memheader_t* fit = first_fit_fwd(size);

  if(fit){

    //Set it as allocated
    (*fit).status = ( (*fit).status | 0x00000001);
    
    //Do we have enough space to fit in a new space header?
    //If not, we'll just eat the remaining space.  We can't do anything with it
    if( ((*fit).size - size) > sizeof(memheader_t) ){
      memheader_t* oldneigh = next_memheader(fit);
      
      //Cut fit to size
      (*fit).size = size;
      
      memheader_t* newneigh = next_memheader(fit);

      //Create new neighboring header
      (*newneigh).size = memheader_space(newneigh, oldneigh);
      (*newneigh).status = (uint32_t) (((uint32_t) fit) & 0xFFFFFFFE);

      //Now point oldneigh back to newneigh
      set_memheader_prev(oldneigh, newneigh);
    }
    return ((void*) fit + sizeof(memheader_t));
  }
  
  //We do not currently have enough space.  Ask for more blocks.
  memheader_t* newblockhead = request_blocks(size);

  if(newblockhead){
    //Get our final headers
    memheader_t* oldlast = final_memheader();
    
    memheader_t* penultimate = NULL;
    memheader_t* trav = memstart;
    
    while(trav != oldlast){
      penultimate = trav;
      trav = next_memheader(trav);
    }
    
    //Now link them.  Note that our newblockhead actually points back to the header
    //BEFORE oldlast (That is to say, penultimate)
    set_memheader_prev(newblockhead, penultimate);
    (*oldlast).status = (uint32_t) newblockhead;

    return newblockhead;
  }

  //We don't have enough memory
  //OH SHIT
  printf("Out of RAM");
  while(1){};
  return NULL;
}

void kfree(void* ptr){
  memheader_t* tofree = (ptr - sizeof(memheader_t));
  
  (*tofree).status = ((*tofree).status & 0xFFFFFFFE);
  
  //Get our next neighbor
  memheader_t* next = next_memheader(tofree);
  if(!(*next).size)
    next = next_memheader(next);

  //Now try to get our previous neighbor and merge
  if(!is_blockstart_header(tofree)){
    memheader_t* prev = prev_memheader(tofree);
    if(is_free(prev)){
      (*prev).size += (*tofree).size + sizeof(memheader_t);
      set_memheader_prev(next, prev);
      tofree = prev;
    }
  }

  //Now try to merge our next memheader back onto our new space
  if(!is_blockstart_header(next)){
    memheader_t* nextnext = next_memheader(next);
    if(is_free(next)){
      (*tofree).size += (*next).size + sizeof(memheader_t);
      set_memheader_prev(nextnext, tofree);
    }
  }

  //TODO:  Search for any blocks that are (aside from their headers) completely
  //       free.  Free them via the physmm

}
