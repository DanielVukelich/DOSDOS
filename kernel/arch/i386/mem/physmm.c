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

#include <kernel/mem/physmm.h>

uint32_t mem_used_blocks;
uint32_t mem_full_size_kb;
uint32_t mem_full_size_blocks;

uint32_t* mem_bitmap;  //Pointer to our block bitmap

void mmap_bitset(int bit){
  mem_bitmap[bit /32] = mem_bitmap[bit / 32] | (1 << (bit % 32));
}

void mmap_bitunset(int bit){
  mem_bitmap[bit / 32] = mem_bitmap[bit / 32] & ~(1 << (bit % 32));
}

bool mmap_checkstatus(int bit){
  return mem_bitmap[bit / 32] & (1 << (bit % 32));
}

uint32_t mmap_get_max_blocks(){
  return mem_full_size_blocks;
}

size_t init_mmap(multiboot_info_t* mbt, uint32_t* physmm_bitmap, const void* START_OF_KERNEL, const void* END_OF_KERNEL){

  unsigned long flags = (mbt->flags) >> 6;

  if(!(flags % 2)){
    printf("Multiboot memory map error\n");
    return 0;
  }

  unsigned long mmap_entries = mbt->mmap_length / sizeof(memory_map_t);
  memory_map_t* mmap = (memory_map_t*) mbt->mmap_addr;

  unsigned long totmem = 0;
  int last_addressable_index = -1;

  //First, loop through to get the total amount of memory to play with
  for(unsigned int i = 0; i < mmap_entries; i++){

    unsigned long start = mmap[i].base_addr_low;
    unsigned long start_h = mmap[i].base_addr_high;
    unsigned long length = mmap[i].length_low;
    unsigned long length_h = mmap[i].length_high;

    //Only do stuff if the region is 32 bit addressable
    if(start_h == 0 && length_h == 0){

      
      //If we are going to overshoot the addressable 32 bit range with a region,
      //then truncate it
      unsigned long maxu32 = 0xFFFFFFFF;
      if( (start + length) < length)
	length = maxu32 - start;

      totmem += length;
      last_addressable_index = i;
    }
    
  }

  if( last_addressable_index == -1){
    printf("No memory regions are addressable by this operating system\n");
    return 0;
  }

  //Initialize the bitmap
  size_t mmap_size = physmm_init(totmem / 1024, physmm_bitmap);

  //Now, loop through and initialize only the regions that are addressable
  for(int i = 0; i <= last_addressable_index; ++i){

    char type = mmap[i].type;
    unsigned long start = mmap[i].base_addr_low;
    unsigned long length = mmap[i].length_low;


    //If we are going to overshoot the addressable 32 bit range with a region,
    //then truncate it
    unsigned long maxu32 = 0xFFFFFFFF;
    if( (start + length) < length)
      length = maxu32 - start;

    //Now just initialize the region if it is type 1
    if(type == 1)
      physmm_init_region( (void*) start, length);

  }

  //Deinit our kernel's space so that nobody tries to overwrite it
  size_t kernelsize_rounded = (END_OF_KERNEL - START_OF_KERNEL);
  kernelsize_rounded += (4096 - ((size_t) END_OF_KERNEL % 4096));
  size_t mmapsize_round = mmap_size + (4096 - (mmap_size % 4096));

  physmm_deinit_region(START_OF_KERNEL, kernelsize_rounded);
  physmm_deinit_region(END_OF_KERNEL, mmapsize_round);
  
  return mmap_size;
  
}

void physmm_init_region(const void* baseaddr, size_t size){

  uint32_t align = (uint32_t) baseaddr / PHYSMM_BLOCK_SIZE;
  int blocks = size / PHYSMM_BLOCK_SIZE;

  while(blocks > 0){
    mmap_bitunset(align++);
    --mem_used_blocks;
    --blocks;
  }

  mmap_bitset(0);
  
}

uint32_t physmm_freeblock_count(){
  return (mem_full_size_blocks - mem_used_blocks);
}

void* physmm_alloc_block(){
  
  if(physmm_freeblock_count() <= 0){
    return 0;
  }

  int pageframe = mmap_first_free();

  if(pageframe == -1){
    return 0;
  }

  mmap_bitset(pageframe);  

  uint32_t address = (pageframe * PHYSMM_BLOCK_SIZE);

  ++mem_used_blocks;

  return (void*) address;
}

void* physmm_alloc_blocks(size_t size){

  if(physmm_freeblock_count() <= 0)
    return 0;

  int pageframe = mmap_first_free_s(size);

  if(pageframe == -1)
    return 0;

  for(unsigned int i = 0; i < size; ++i)
    mmap_bitset(pageframe + i);

  uint32_t address = (pageframe * PHYSMM_BLOCK_SIZE);

  mem_used_blocks += size;

  return (void*) address;

}

void physmm_free_block(const void* p){
  
  uint32_t address = (uint32_t) p;
  
  int pageframe = address / PHYSMM_BLOCK_SIZE;

  mmap_bitunset(pageframe);
  --mem_used_blocks;
  
}

void physmm_free_blocks(const void* p, size_t size){

  uint32_t address = (uint32_t) p;
  int pageframe = address / PHYSMM_BLOCK_SIZE;

  for(size_t i = 0; i < size; ++i){
    mmap_bitunset(pageframe + i);
  }

  mem_used_blocks -= size;
  
}

void physmm_deinit_region(const void* baseaddr, size_t size){

  uint32_t align = (uint32_t) baseaddr / PHYSMM_BLOCK_SIZE;
  unsigned int blocks = size / PHYSMM_BLOCK_SIZE;

  while(blocks > 0){
    mmap_bitset(align++);
    ++mem_used_blocks;
    --blocks;
  }
 
}

//Memorysize is taken in Kb
//Return the size of the memory bitmap
size_t physmm_init(size_t memorysize, void* bitmap){
  mem_full_size_kb = memorysize;
  mem_bitmap = (uint32_t*) bitmap;
  mem_full_size_blocks = (memorysize * 1024) / PHYSMM_BLOCK_SIZE;

  //Default to setting all of our memory as 'in use'
  mem_used_blocks = mmap_get_max_blocks();
  memset(mem_bitmap, 0xF, mmap_get_max_blocks() / BLOCKS_PER_BYTE);

  return (mmap_get_max_blocks() / BLOCKS_PER_BYTE);
}

int mmap_first_free(){

  //Find the first zero bit in our bitmap.  This corresponds to the first free
  //Block of 4kb in RAM
  
  for(uint32_t i = 0; i < mem_full_size_blocks / 32; ++i){
    if(mem_bitmap[i] != 0xFFFFFFFF){
      for(uint32_t j = 0; j < 32; ++j){
	int bit = 1 << j;
	if(! (mem_bitmap[i] & bit) ){
	  return ( (i * 4 * 8) + j);
	}
      }
    }
  }

  return -1;
}

int mmap_first_free_s(size_t size){
  
  if (size == 0)
    return -1;

  if (size == 1)
    return mmap_first_free();

  for (uint32_t i = 0; i < mem_full_size_blocks / 32; ++i)
    if (mem_bitmap[i] != 0xffffffff)
      for (int j=0; j < 32; j++) {	//! test each bit in the dword
	int bit = 1 << j;
	if (! (mem_bitmap[i] & bit) ) {
	  int startingBit = i * 32;
	  startingBit += bit;//get the free bit in the dword at index i
	  
	  uint32_t free = 0; //loop through each bit to see if its enough space
	  for (uint32_t count = 0; count <= size; ++count) {
	    
	    if (!mmap_checkstatus(startingBit + count) )
	      ++free;	// this bit is free
	    
	    if (free == size)
	      return (i * 4 * 8 + j); //free count==size needed; return index
	  }
	}
      }
  
  return -1;
}

inline uint32_t mmap_get_max_size_blocks(){
  return mem_full_size_blocks;
}


