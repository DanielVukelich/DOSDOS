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

#ifndef _KERNEL_DESC_TABLES
#define _KERNEL_DESC_TABLES

#include <stddef.h>
#include <stdint.h>

extern void gdt_flush(void);
extern void tss_flush(void);

typedef struct tss_entry {
  uint32_t	prev_tss;
  uint32_t	esp0;
  uint32_t	ss0;
  uint32_t	esp1;
  uint32_t	ss1;
  uint32_t	esp2;
  uint32_t	ss2;
  uint32_t	cr3;
  uint32_t	eip;
  uint32_t	eflags;
  uint32_t	eax;
  uint32_t	ecx;
  uint32_t	edx;
  uint32_t	ebx;
  uint32_t	esp;
  uint32_t	ebp;
  uint32_t	esi;
  uint32_t	edi;
  uint32_t	es;
  uint32_t	cs;
  uint32_t	ss;
  uint32_t	ds;
  uint32_t	fs;
  uint32_t	gs;
  uint32_t	ldt;
  uint16_t	trap;
  uint16_t	iomap_base;
} __attribute__ ((packed)) tss_entry_t;

void gdt_init();

#endif
