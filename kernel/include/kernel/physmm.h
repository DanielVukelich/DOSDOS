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

#include "kernel/multiboot.h"

//Number of blocks represented by one byte in out bitmap
#define BLOCKS_PER_BYTE 8

//Size in bytes of each block as well as block alignment
#define BLOCK_SIZE 4096

static uint32_t mem_used_blocks = 0;
static uint32_t mem_full_size_kb = 0;
static uint32_t mem_full_size_blocks = 0;

static uint32_t* mem_bitmap = 0;  //Pointer to our block bitmap

inline void mmap_bitset(int bit);
inline void mmap_bitunset(int bit);
inline bool mmap_checkstatus(int bit);
inline uint32_t mmap_get_max_blocks();
int mmap_first_free();
int mmap_first_free_s(size_t size);

//Memorysize is taken in Kb
//Return the size of the memory bitmap
size_t physmm_init(size_t memorysize, void* bitmap);
void physmm_init_region(void* baseaddr, size_t size);
void physmm_deinit_region(void* baseaddr, size_t size);
void physmm_free_block(void* p);
void physmm_free_blocks(void* p, size_t size);
void* physmm_alloc_block();
void* physmm_alloc_blocks(size_t size);
uint32_t physmm_freeblock_count();

#endif
