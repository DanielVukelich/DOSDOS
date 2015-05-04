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

#include <stdlib.h>
#include <kernel/mem/paging.h>

extern void loadPageDirectory(uint32_t*);
extern void enablePaging();

uint32_t* last_dirptr;

uint32_t emergencyblock[4096];
uint32_t* emblock_ptr;

void init_pageDir(uint32_t* dirptr){

  //Init all tables to:
  //Supervisor (only kernel can access)
  //Read+Write
  //Not present
  
  for(int i = 0; i < 1024; ++i){
    dirptr[i] = 0x00000002;
  }

  last_dirptr = dirptr;
  
}

void init_KernelPT(uint32_t* tabptr){

  for(int i = 0; i < 1024; ++i){
    //Supervisor
    //Read+Write
    //Not Present
    tabptr[i] = ((i * 0x1000) | 2);
  }
  
}

void insert_Kernel_PTValue(uint32_t* tabptr, uint32_t tabindex){
  //Supervisor
  //Read_Write
  //Present
  tabptr[tabindex] = ((tabindex * 0x1000) | 3);
}

void remove_Kernel_PTValue(uint32_t* tabptr, uint32_t tabindex){
  //Supervisor
  //Read_Write
  //Not Present
  tabptr[tabindex] = ((tabindex * 0x1000) | 2);
}

void insert_KernelPTentry(uint32_t* dirptr, uint32_t* tabptr, uint32_t dirindex){
  //Supervisor
  //Read+Write
  //Present
  dirptr[dirindex] = ( (uint32_t) tabptr ) | 3;
}

uint32_t* get_dirptr(){
  return  last_dirptr;
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

bool register_block_for_kernel(uint32_t* dirptr, size_t block){

  //TODO* Fix this piece of shit

  uint32_t dindex = block_to_DirIndex(block);
  uint32_t* ptptr = get_pagetable_ptr(dirptr, dindex);

  if(block == 900){
    remove_Kernel_PTValue(ptptr,dindex);
    //abort();
  }

  printf("Registering block: %d\n", (int) block);
  printf("Dindex: %d\n", (int) dindex);
  
  bool needednewblock = false;
  printf("G:%p\n", ptptr);
  if(!ptptr){
    init_KernelPT(emblock_ptr);
    insert_KernelPTentry(dirptr, emblock_ptr, dindex);
    ptptr = emblock_ptr;
    emblock_ptr = physmm_alloc_block();
    printf("****GOING DEEPER****\n");
    register_block_for_kernel(dirptr, addr_to_block((void*) emblock_ptr));
    printf("****DONE GOING DEEPER****\n");
    needednewblock = true;
    printf("Needed new block%p\n", (void*) emblock_ptr);
  }

  uint32_t pindex = block_to_PTIndex(block);
  printf("Ptptr: %p\n", (void*) ptptr);

  if(block == 1027){
    abort();
  }
  
  insert_Kernel_PTValue(ptptr, pindex);

  
  return needednewblock;
}

void init_paging(uint32_t* dirptr, uint32_t* tabptr, const void* krnl_start, const void* krnl_end){

  //TODO:  See if it's possible to limit the amount of registered blocks to only
  //Those in the kernel-space, as opposed to the entire address space

  init_pageDir(dirptr);
  init_KernelPT(tabptr);

  ++krnl_start;
  ++krnl_end;

  for(uint32_t i = 0; i < 1024; ++i){
    insert_Kernel_PTValue(tabptr, i);
  }

  for(uint32_t i = 0; i < 1024; ++i){
    insert_KernelPTentry(dirptr, tabptr, i);
  }
    
  /*
  //Identity paging for the whole kernel address space
  size_t kstblock = addr_to_block(krnl_start);
  size_t kenblock = addr_to_block(krnl_end);
  uint32_t kstDI = block_to_DirIndex(kstblock);
  uint32_t kenDI = block_to_DirIndex(kenblock);
  //uint32_t kstPT = block_to_PTIndex(kstblock);
  //uint32_t kenPT = block_to_PTIndex(kenblock);

  uint32_t DIspan = kenDI - kstDI;

  init_pageDir(dirptr);
  
  for(uint32_t i = 0; i <= DIspan; ++i){

    init_KernelPT(tabptr);
    uint32_t currentDI = kstDI + i;

    //uint32_t PTst = 0;
    //uint32_t PTen = 1024;

    //if(currentDI == kstDI)
    //  PTst = kstPT;
    //if(currentDI == kenDI)
    //  PTen = kenPT;

    //for(; PTst <= PTen+10; ++PTst){
    // insert_Kernel_PTValue(tabptr, PTst);
    //}

    for(uint32_t i = 0; i < 1024; ++i){
      insert_Kernel_PTValue(tabptr, i);
    }
    
    insert_KernelPTentry(dirptr, tabptr, currentDI);

    tabptr += 4096;
  }

  */
  loadPageDirectory(dirptr);
  enablePaging();
}
