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

#ifndef _KERNEL_PHYSMM_H
#define _KERNEL_PHYSMM_H

#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

#include <kernel/utils/multiboot.h>

//Number of blocks represented by one byte in out bitmap
#define BLOCKS_PER_BYTE 8

//Size in bytes of each block as well as block alignment
#define PHYSMM_BLOCK_SIZE 4096

int mmap_first_free();
int mmap_first_free_s(size_t size);

size_t init_mmap(multiboot_info_t* mbt, uint32_t* physmm_bitmap, const void* START_OF_KERNEL, const void* END_OF_KERNEL);
size_t physmm_init(size_t memorysize_kb, void* bitmap);
void physmm_init_region(const void* baseaddr, size_t size);
void physmm_deinit_region(const void* baseaddr, size_t size);
void physmm_free_block(const void* p);
void physmm_free_blocks(const void* p, size_t size);
void* physmm_alloc_block();
void* physmm_alloc_blocks(size_t size);
uint32_t physmm_freeblock_count();

void mmap_bitset(int bit);
  
void mmap_bitunset(int bit);

bool mmap_checkstatus(int bit);

uint32_t mmap_get_max_blocks();

inline size_t round_size_to_blocks(size_t siz){
  size_t blocks = siz / PHYSMM_BLOCK_SIZE;
  if(siz % 4096)
    ++blocks;
  return blocks;
}

#endif
