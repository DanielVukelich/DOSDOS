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

#include <kernel/desc_tables.h>

static void write_tss(int32_t, uint16_t, uint32_t);
  
struct gdt_entry gdt[6];
struct gdt_ptr gdt_p;

struct idt_entry idt[256];
struct idt_ptr idt_p;

tss_entry_t tss_entry;

static void gdt_set_gate(size_t num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
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
  gdt_p.limit = (sizeof(gdt_entry_t) * 6) - 1;
  gdt_p.base = (uint32_t)&gdt;
  
  gdt_set_gate(0, 0, 0, 0, 0); 
  gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);  
  gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);  
  gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);  
  gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
  
  write_tss(5, 0x10, 0x0);
  
  gdt_flush();
  tss_flush();
}

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
  idt[num].base_low = base & 0xFFFF;
  idt[num].base_hi = (base >> 16) & 0xFFFF;

  idt[num].sel = sel;
  idt[num].always0 = 0;

  // We must uncomment the OR below when we get to using user-mode.
  // It sets the interrupt gate's privilege level to 3.
  idt[num].flags   = flags /*| 0x60*/;
}

void idt_init(){
  idt_p.limit = sizeof(idt_entry_t) * 256 - 1;
  idt_p.base  = (uint32_t)&idt;

  memset(&idt, 0, sizeof(idt_entry_t) * 256);

  idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
  idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
  idt_set_gate(2, (uint32_t)isr2, 0x08, 0x8E);
  idt_set_gate(3, (uint32_t)isr3, 0x08, 0x8E);
  idt_set_gate(4, (uint32_t)isr4, 0x08, 0x8E);
  idt_set_gate(5, (uint32_t)isr5, 0x08, 0x8E);
  idt_set_gate(6, (uint32_t)isr6, 0x08, 0x8E);
  idt_set_gate(7, (uint32_t)isr7, 0x08, 0x8E);
  idt_set_gate(8, (uint32_t)isr8, 0x08, 0x8E);
  idt_set_gate(9, (uint32_t)isr9, 0x08, 0x8E);
  idt_set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
  idt_set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
  idt_set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
  idt_set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
  idt_set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
  idt_set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
  idt_set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
  idt_set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
  idt_set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
  idt_set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
  idt_set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
  idt_set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
  idt_set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
  idt_set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
  idt_set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
  idt_set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
  idt_set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
  idt_set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
  idt_set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
  idt_set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
  idt_set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
  idt_set_gate(31, (uint32_t)isr31, 0x08, 0x8E);  
  
  idt_flush();
}

static void write_tss(int32_t num, uint16_t ss0, uint32_t esp0)
{
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
