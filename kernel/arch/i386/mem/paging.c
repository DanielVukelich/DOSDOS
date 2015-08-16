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
static uint32_t* PageDir_Ptr;

static int helper_insert = 0;

const uint32_t HELPER_DIR_INDEX = 1;
const uint32_t MAX_TABLE_ENTRY = 1023;
const uint32_t HELPER_BLOCK_INSERT_INDEX = 0;
//4MiB Kernel + 16MiB full size tables = 5120 Blocks
const uint32_t START_OF_FREE_RAM_BLOCKS = 5120;

static inline uint32_t* index_to_virtual(uint32_t dirindex, uint32_t tabindex){
  return (uint32_t*) ((dirindex) *  PHYSMM_BLOCK_SIZE * (MAX_TABLE_ENTRY + 1) + ((tabindex) * PHYSMM_BLOCK_SIZE));
}

static inline void invlpg(const void* m)
{
  asm volatile ( "invlpg (%0)" :: "r" (m) : "memory" );
}

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

inline void insert_Kernel_PTValue(uint32_t* tabptr, const uint32_t tabindex, const uint32_t physical_block){
  //Supervisor
  //Read_Write
  //Present
  tabptr[tabindex] = ((physical_block * 0x1000) | 3);
}

inline void remove_Kernel_PTValue(uint32_t* tabptr, const uint32_t tabindex){
  tabptr[tabindex] = 0;
}

inline void insert_KernelPTentry(uint32_t* dirptr, const uint32_t* tabptr, const uint32_t dirindex){
  //Supervisor
  //Read+Write
  //Present
  dirptr[dirindex] = ( (uint32_t) tabptr ) | 3;
}

inline void insert_User_PTValue(uint32_t* tabptr, const uint32_t tabindex, const uint32_t physical_block){
  //Supervisor
  //Read_Write
  //Present
  tabptr[tabindex] = ((physical_block * 0x1000) | 7);
}

inline void insert_UserPTentry(uint32_t* dirptr, const uint32_t* tabptr, const uint32_t dirindex){
  //Present
  dirptr[dirindex] = ( (uint32_t) tabptr ) | 1;
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

void init_paging(uint32_t* dirptr, const void* krnl_start){

  //dirptr = Page_Directory;
  uint32_t* tabptr = physmm_alloc_block();
  init_pageDir(dirptr);
  //Identity map the first 4MiB
  for(uint32_t i = 0; i <= MAX_TABLE_ENTRY; ++i){
    insert_Kernel_PTValue(tabptr, i, i);
  }

  
  //Put helper_block as the last entry in the Page Table Directory
  init_KernelPT(helper_block);
  insert_KernelPTentry(dirptr, helper_block, HELPER_DIR_INDEX);

  helper_insert = 0;
  
  size_t kstblock = addr_to_block(krnl_start);
  uint32_t kdirst = block_to_DirIndex(kstblock);
  insert_KernelPTentry(dirptr, tabptr, kdirst);  
  
  PageDir_Ptr = dirptr;
  loadPageDirectory(dirptr);
  enablePaging();


}

static uint32_t oldcr2 = 0;

void handle_page_fault(uint32_t errcode){
  
  uint32_t cr2;
  asm volatile("mov %%cr2, %0" : "=r" (cr2));
  //Get the middle 10 bits
  uint32_t pagetab_entry = ((cr2 >> 12) & 0x3FF);
  //Get the upper 10 bits
  uint32_t pagedir_entry = (cr2 >> 22);
  
  bool isPresent = (errcode % 2);
  bool isUser = ((errcode >> 2) % 2);
  
  
  if(!isPresent){
    
    //We need to put a new block in the page directory
    uint32_t* newblock = physmm_alloc_block();

    //Point to it with our helper block so we can use it
    insert_Kernel_PTValue(helper_block, HELPER_BLOCK_INSERT_INDEX + helper_insert, addr_to_block_32((void*)newblock));
        
    //Now we can zero it (Initialize it from the address it is mapped to in the helper block)
    init_KernelPT(index_to_virtual(HELPER_DIR_INDEX, HELPER_BLOCK_INSERT_INDEX + helper_insert) );
    
    //Now put this new page table in the page directory
    insert_KernelPTentry(PageDir_Ptr, newblock, pagedir_entry);

    ++helper_insert;
    if(helper_insert > (int)MAX_TABLE_ENTRY){
       printf("Helper insert too large: %i", helper_insert);
      while(1);
    }

    //And now stop pointing to it from helper block
    loadPageDirectory(PageDir_Ptr);
  }

  uint32_t* tabptr = get_pagetable_ptr(PageDir_Ptr, pagedir_entry);    
  void* toallocate = physmm_alloc_block();
    
  uint32_t toallocate_block = addr_to_block_32(toallocate);
  if(isUser){
    //Map the block with user privilege
    insert_User_PTValue(tabptr, pagetab_entry, toallocate_block);
  }else{
    //Map the block with kernel privilege
    insert_Kernel_PTValue(tabptr, pagetab_entry, toallocate_block);
  }

  invlpg((void*) cr2);
  oldcr2 = cr2;
}

