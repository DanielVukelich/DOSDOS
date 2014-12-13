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

#ifndef _KERNEL_PAGING_H
#define _KERNEL_PAGING_H

#include <stdint.h>

void init_paging(uint32_t* dirptr, uint32_t* tabptr);
void init_KernelPT(uint32_t* tabptr);
void init_pageDir(uint32_t* dirptr);
void insert_KernelPTentry(uint32_t* dirptr, uint32_t* tabptr, uint32_t dirindex);

inline uint32_t block_to_DirIndex(uint32_t block){
  return (block / 1024);
}

inline uint32_t block_to_PTIndex(uint32_t block){
  return (block % 1024);
}

inline uint32_t addr_to_block(void* addr){
  return ( ( (uint32_t) addr) / 4096);
}

#endif
