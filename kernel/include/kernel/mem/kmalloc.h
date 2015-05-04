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

#ifndef _KERNEL_KMALLOC_H
#define _KERNEL_KMALLOC_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

#include <kernel/mem/physmm.h>
#include <kernel/mem/paging.h>

//The headers need to be even-byte aligned
//Status has the following layout:
//Bit 0:  Whether or not the memory section this header refers to is free
//Bits 1-31:  The address of the previous memory section's header
//The next memory section can be found by (&memheader + size)+sizeof(memheader_t)
//and then rounding it up to the nearest even number.
//Note that if size is 0, then the upper 31 bits of status are instead treated as a
//pointer to the next memory section.  This next memory section's 31 status bits
//will, in turn, point to the memory header of the section that pointed to the 0
//size header.  That is to say:  While traversing the memory list backwards, one
//will never encounter any headers with size 0.

//Also note that size is always an even number.  kalloc will round up the requested
//memory such that this invariant always holds true.
typedef struct memheader{
  size_t size;
  uint32_t status;
}memheader_t;

void* kmalloc(size_t size);
void kfree(void* ptr);
void printheaders();

#endif
