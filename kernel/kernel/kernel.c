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

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include <kernel/tty.h>
#include <kernel/cursor.h>
#include <kernel/multiboot.h>
#include <kernel/physmm.h>

extern uint32_t endkernel;

static const  uint32_t* END_OF_KERNEL = (uint32_t*) (&endkernel + 1);
static uint32_t* physmm_bitmap;

static size_t physmm_bitmap_size;

size_t init_mmap(multiboot_info_t* mbt);
   
void kernel_early(void)
{
  terminal_initialize();
}

void kernel_main(multiboot_info_t* mbt, unsigned int magicvoid)
{
  cursor_hide();

  //Now initialize out physical memory manager
  physmm_bitmap = END_OF_KERNEL;
  physmm_bitmap_size = init_mmap(mbt);
  if(physmm_bitmap_size == 0){
    printf("Error initializing physical memory manager\n");
      abort();
  }

  //A little test for out physical memory manager
  printf("Free blocks: %d\n", physmm_freeblock_count());
  void* block = physmm_alloc_block();
  printf("Allocated 4Kib block at %p\n",  block);
  size_t allocsiz = 4;
  void* blocks = physmm_alloc_blocks(allocsiz);
  printf("Allocated %dx4Kib blocks at %p\n", allocsiz, blocks);
  printf("Free blocks: %d\n", physmm_freeblock_count());
  physmm_free_block(block);
  printf("Freed block at %p\n", block);
  printf("Free blocks: %d\n", physmm_freeblock_count());
  block = physmm_alloc_blocks(allocsiz);
  printf("Allocated %dx4Kib blocks at %p\n", allocsiz, block);
  printf("Free blocks: %d\n", physmm_freeblock_count());
  physmm_free_blocks(blocks, allocsiz);
  printf("Freed blocks at %p\n", blocks);
  printf("Free blocks: %d\n", physmm_freeblock_count());
  physmm_free_blocks(block, allocsiz);
  printf("Freed blocks at %p\n", block);
  printf("Free blocks: %d\n", physmm_freeblock_count());

  
  abort();
}

size_t init_mmap(multiboot_info_t* mbt){

  printf("Initializing physical memory\n");
  
  unsigned long flags = (mbt->flags) >> 6;

  if(!(flags % 2)){
    printf("Multiboot memory map error\n");
    return 0;
  }

  unsigned long mmap_entries = mbt->mmap_length / sizeof(memory_map_t);
  memory_map_t* mmap = mbt->mmap_addr;

  unsigned long totmem = 0;
  int last_addressable_index = -1;

  //First, loop through to get the total amount of memory to play with
  for(int i = 0; i < mmap_entries; i++){

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
  size_t mmap_size = physmm_init(totmem, physmm_bitmap);

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

    printf("\nEncountered region %d at %p\n", (i + 1), start);
    printf("\tRegion has type %d and size %p\n", type, length);
    
    //Now just initialize the region if it is type 1
    if(type == 1){
      printf("\tMemory manager is initializing memory region...\n");
      physmm_init_region(start, length);
    }

  }

  return mmap_size;
  
}
