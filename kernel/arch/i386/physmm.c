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

#include "kernel/physmm.h"

void physmm_init_region(void* baseaddr, size_t size){

  uint32_t align = (uint32_t) baseaddr / BLOCK_SIZE;
  int blocks = size / BLOCK_SIZE;

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

  if(physmm_freeblock_count() <= 0)
    return 0;

  int pageframe = mmap_first_free();

  if(pageframe == -1)
    return 0;

  mmap_bitset(pageframe);

  uint32_t address = (pageframe * BLOCK_SIZE);

  ++mem_used_blocks;

  return (void*) address;
}

void* physmm_alloc_blocks(size_t size){

  if(physmm_freeblock_count() <= 0)
    return 0;

  int pageframe = mmap_first_free_s(size);

  if(pageframe == -1)
    return 0;

  for(int i = 0; i < size; ++i)
  mmap_bitset(pageframe + i);

  uint32_t address = (pageframe * BLOCK_SIZE);

  mem_used_blocks += size;

  return (void*) address;

}

void physmm_free_block(void* p){
  
  uint32_t address = (uint32_t) p;
  int pageframe = address / BLOCK_SIZE;

  mmap_bitunset(pageframe);
  --mem_used_blocks;
  
}

void physmm_free_blocks(void* p, size_t size){

  uint32_t address = (uint32_t) p;
  int pageframe = address / BLOCK_SIZE;

  for(size_t i = 0; i < size; ++i){
    mmap_bitunset(pageframe + i);
  }

  mem_used_blocks -= size;
  
}

void physmm_deinit_region(void* baseaddr, size_t size){

  uint32_t align = (uint32_t) baseaddr / BLOCK_SIZE;
  int blocks = size / BLOCK_SIZE;

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
  mem_full_size_blocks = (memorysize * 1024) / BLOCK_SIZE;

  //Default to setting all of our memory as 'in use'
  mem_used_blocks = mmap_get_max_blocks();
  memset(mem_bitmap, 0xF, mmap_get_max_blocks() / BLOCKS_PER_BYTE);

  return (mmap_get_max_blocks() / BLOCKS_PER_BYTE);
}

inline uint32_t mmap_get_max_blocks(){
  return mem_full_size_blocks;
}

inline void mmap_bitset(int bit){
  mem_bitmap[bit /32] = mem_bitmap[bit / 32] | (1 << (bit % 32));
}

inline void mmap_bitunset(int bit){
  mem_bitmap[bit / 32] = mem_bitmap[bit / 32] & ~(1 << (bit % 32));
}

inline bool mmap_checkstatus(int bit){
  return mem_bitmap[bit / 32] & (1 << (bit % 32));
}

int mmap_first_free(){

  //Find the first zero bit in our bitmap.  This corresponds to the first free
  //Block of 4kb in RAM
  
  for(uint32_t i = 0; i < mem_full_size_blocks / 32; ++i){
    if(mem_bitmap[i] != 0xFFFFFFFF){
      for(int j = 0; j < 32; ++j){
	int bit = 1 << j;
	if(! (mem_bitmap[i] & bit) )
	  return ( (i * 4 * 8) + j);
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
