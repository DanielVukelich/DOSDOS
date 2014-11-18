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

#include "kernel/desc_tables.h"

static void write_tss(int32_t, uint16_t, uint32_t);
tss_entry_t tss_entry;

struct gdt_entry {
  unsigned short limit_low;
  unsigned short base_low;
  unsigned char base_middle;
  unsigned char access;
  unsigned char granularity;
  unsigned char base_high;
} __attribute__((packed));

struct gdt_ptr{
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

struct gdt_entry gdt[6];
struct gdt_ptr gp;

void gdt_set_gate(size_t num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
  gdt[num].base_low = (base & 0xFFFF);
  gdt[num].base_middle = (base >> 16) & 0xFF;
  gdt[num].base_high = (base >> 24) & 0xFF;
  gdt[num].limit_low = (limit & 0xFFFF);
  gdt[num].granularity = (limit >> 16) & 0X0F;
  gdt[num].granularity |= (gran & 0xF0);
  gdt[num].access = access;
}

void gdt_init()
{
  gp.limit = (sizeof(struct gdt_entry) * 6) - 1;
  gp.base = (unsigned int)&gdt;
  
  gdt_set_gate(0, 0, 0, 0, 0); 
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);  
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);  
  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);  
  gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
  
  write_tss(5, 0x10, 0x0);
  
  gdt_flush();
  tss_flush();
}

static void write_tss(int32_t num, uint16_t ss0, uint32_t esp0) {
  
  uintptr_t base = (uintptr_t)&tss_entry;
  uintptr_t limit = base + sizeof(tss_entry);
  
  gdt_set_gate(num, base, limit, 0xE9, 0x00);
  memset(&tss_entry, 0x0, sizeof(tss_entry));
  
  tss_entry.ss0 = ss0;
  tss_entry.esp0 = esp0;
  tss_entry.cs = 0x0b;
  tss_entry.ss =
    tss_entry.ds =
    tss_entry.es =
    tss_entry.fs =
    tss_entry.gs = 0x13;
  
  tss_entry.iomap_base = sizeof(tss_entry);
}
