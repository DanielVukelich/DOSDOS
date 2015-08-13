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

#include <kernel/mem/paging.h>

extern void loadPageDirectory(uint32_t*);
extern void enablePaging();

//This block exists so that we can manipulate tables of memory that we shouldn't be allowed to access
static uint32_t helper_block[1024] __attribute__((aligned(4096)));

//Keep track of where we've been consecutively adding blocks
static uint32_t last_entered_Kblock;
static uint32_t last_entered_KMemblock;

const uint32_t MAX_TABLE_ENTRY = 1023;
//4MiB Kernel + 16MiB full size tables = 5120 Blocks
const uint32_t START_OF_FREE_RAM_BLOCKS = 5120;

void init_pageDir(uint32_t* dirptr){
  
  for(int i = 0; i < 1024; ++i){
    dirptr[i] = 0;
  }
  
}

void init_KernelPT(uint32_t* tabptr){

  for(int i = 0; i < 1024; ++i){
    tabptr[i] = 0;
  }
  
}

inline size_t get_last_entered_Kernel_block(){
  return (size_t) last_entered_Kblock;
}

void insert_Kernel_PTValue(uint32_t* tabptr, uint32_t tabindex, uint32_t physical_block){
  //Supervisor
  //Read_Write
  //Present
  tabptr[tabindex] = ((physical_block * 0x1000) | 3);
}

void remove_Kernel_PTValue(uint32_t* tabptr, uint32_t tabindex){
  //Supervisor
  //Read_Write
  //Not Present
  tabptr[tabindex] = 0;
}

void insert_KernelPTentry(uint32_t* dirptr, uint32_t* tabptr, uint32_t dirindex){
  //Supervisor
  //Read+Write
  //Present
  dirptr[dirindex] = ( (uint32_t) tabptr ) | 3;
}

//Attempts to get the page table at Page Directory index DirIndex
//Returns NULL if no such page table is present
uint32_t* get_pagetable_ptr(uint32_t* dirptr, uint32_t DirIndex){
  uint32_t* PT = NULL;
  
  if(dirptr[DirIndex] % 2){
    //Mask out the low 12 bits to get our 4096 bit aligned address
    PT = (void*) (dirptr[DirIndex] & 0xFFFFF000);
  }

  return PT;
}

//Attempts to get the block table at Page table index tabIndex
//Returns NULL if no such block is present
uint32_t* get_block_ptr(uint32_t* tabptr, uint32_t tabIndex){
  uint32_t* PT = NULL;
  
  if(tabptr[tabIndex] % 2){
    //Mask out the low 12 bits to get our 4096 bit aligned address
    PT = (void*) (tabptr[tabIndex] & 0xFFFFF000);
  }

  return PT;
}

bool register_block_for_kernel(uint32_t* dirptr, size_t physical_block, bool isForMem, bool override_current){

  uint32_t* mapto_block = &last_entered_Kblock;
  if(isForMem){
    mapto_block = &last_entered_KMemblock;
  }

  ++(*mapto_block);
  
  //Can we fit this block in an already existing page table?
  uint32_t dindex = block_to_DirIndex(*mapto_block);
  uint32_t* tabptr = get_pagetable_ptr(dirptr, dindex);
  
  if(tabptr == NULL){  
    //We must request a new block for a new page table
    printf("\nNeeded new Pagetable to map to: #%i",(int)*mapto_block);
    
    uint32_t* newtable = physmm_alloc_block();
    //If we have no more blocks to allocate, return with an error
    if(newtable == NULL){
      printf("Invalid mem error.  %i free blocks", (int) physmm_freeblock_count());
      return false;
    }
    //Now put newtable in our helper block so that we are able to manipulate it without getting page faults
    insert_Kernel_PTValue(helper_block, 0, addr_to_block((void*)newtable));

    
    if(isForMem && (*mapto_block > START_OF_FREE_RAM_BLOCKS)){
      printf("\nHit it %p & %p", (void*) newtable, (void*) helper_block[0]);
      newtable[0] = 12;
      while(1);
    }

    //Now that we can modify newtable, zero it out, and then add it to the directory
    init_KernelPT(newtable);
    insert_KernelPTentry(dirptr, newtable, dindex);
    
    //Now remove newtable from our helper block
    remove_Kernel_PTValue(helper_block, 0);
    tabptr = newtable;
    //Register newtable within itself and add increment the paging block counter
    insert_Kernel_PTValue(tabptr, block_to_PTIndex(last_entered_Kblock), addr_to_block_32((void*) tabptr));
    printf("\tNew pagetable mapped from #%i to #%i", (int)addr_to_block_32((void*) tabptr), (int)last_entered_Kblock);
    ++last_entered_Kblock;

    
  }
  
  //Now we know we have a valid table, try to put the block in the table
  uint32_t tabindex = block_to_PTIndex(*mapto_block);
  uint32_t* blockptr = get_block_ptr(tabptr, tabindex);
  
  if(blockptr != NULL && !override_current){
    //If there is a block already in that space, and we aren't allowed to override it, then return false
    printf("\nBlock already mapped to #%i, had value %p at address %p", (int)*mapto_block, (void*)tabptr[tabindex], (void*) tabptr + tabindex);
    return false;
  }
  //Else, we are free to put the block in the spot
  insert_Kernel_PTValue(tabptr, tabindex, physical_block);
  //printf("\nBlock #%i mapped to #%i", (int)physical_block, (int)*mapto_block);
  return true;
}

void init_paging(uint32_t* dirptr, const void* krnl_start){

  uint32_t* tabptr = physmm_alloc_block();
  while(tabptr == NULL){
    tabptr = physmm_alloc_block();
  }
    printf("%p", (void*) tabptr);
  
  init_pageDir(dirptr);
  init_KernelPT(tabptr);

  size_t kstblock = addr_to_block(krnl_start);
  
  //Identity map the first 4MiB
  for(uint32_t i = 0; i <= MAX_TABLE_ENTRY; ++i){
    insert_Kernel_PTValue(tabptr, i, i);
    last_entered_Kblock = i;
  }

  //Subtract 1 to prevent off-by-one errors
  last_entered_KMemblock = START_OF_FREE_RAM_BLOCKS - 1;

  //Now, we must make sure that the paging directory and the page table themselves are mapped
  size_t dirblock = addr_to_block((void*) dirptr);
  size_t tabblock = addr_to_block((void*) tabptr);
  register_block_for_kernel(dirptr, dirblock, false, true);
  register_block_for_kernel(dirptr, tabblock, false, true);
  
  uint32_t kdirst = block_to_DirIndex(kstblock);
  
  insert_KernelPTentry(dirptr, tabptr, kdirst);
  loadPageDirectory(dirptr);
  enablePaging();

}

void handle_page_fault(uint32_t errcode){
  uint32_t cr2;
  asm volatile("mov %%cr2, %0" : "=r" (cr2));
  printf("\nErrorcode = %p\nAddress = %p", (void*)errcode, (void*)cr2);
}
