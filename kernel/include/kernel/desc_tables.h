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

extern void gdt_flush();
extern void tss_flush();

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

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

struct gdt_entry
{
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t  base_middle;
  uint8_t  access;
  uint8_t  granularity;
  uint8_t  base_high;
} __attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

struct gdt_ptr{
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

struct idt_entry
{
  uint16_t base_low;
  uint16_t sel;
  uint8_t  always0;
  uint8_t  flags;
  uint16_t base_hi;
} __attribute__((packed));
typedef struct idt_entry idt_entry_t;

struct idt_ptr{
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

void gdt_init();
void idt_init();

#endif
