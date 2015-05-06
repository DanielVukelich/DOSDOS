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

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include <kernel/display/tty.h>
#include <kernel/display/cursor.h>
#include <kernel/utils/multiboot.h>
#include <kernel/mem/physmm.h>
#include <kernel/tables/desc_tables.h>
#include <kernel/low_level/isr.h>
#include <kernel/low_level/pic.h>
#include <kernel/mem/paging.h>
#include <kernel/mem/kmalloc.h>
#include <kernel/drivers/keyboard.h>

extern uint32_t endkernel;
extern uint32_t startkernel;

static const void* END_OF_KERNEL = (void*) (&endkernel + 2);
static const void* START_OF_KERNEL = (void*) (&startkernel);
static uint32_t* physmm_bitmap;
static size_t physmm_bitmap_size;

void kernel_early(void)
{
  terminal_initialize();
}

void kernel_main(multiboot_info_t* mbt)
{
  cursor_hide();
  printf("Kernel loaded from %p to %p\n\n", START_OF_KERNEL, END_OF_KERNEL);

  printf("Initializing PIC Interrupts... ");
  PIC_remap(0x20, 0x28);
  printf("Done\n");
  
  printf("Initializing Physical Memory Manager... ");
  physmm_bitmap = (uint32_t*) END_OF_KERNEL;
  physmm_bitmap_size = init_mmap(mbt, physmm_bitmap, START_OF_KERNEL, END_OF_KERNEL);
  if(physmm_bitmap_size == 0){
    printf("Error initializing Physical Memory Manager\n");
      abort();
  }
  printf("Done (%d pages)\n", (unsigned int)physmm_freeblock_count());

  printf("Initializing GDT... ");
  gdt_init();
  printf("Done\n");

  printf("Initializing IDT... ");
  idt_init();
  printf("Done\n");

  printf("Enabling Interrupts... ");
  enable_IRQ();
  printf("Done\n");

  printf("Enabling Paging... ");
  uint32_t* PDirTabl = physmm_alloc_block();
  uint32_t* PTabl = physmm_alloc_block();  
  init_paging(PDirTabl, PTabl, START_OF_KERNEL, END_OF_KERNEL);
  printf("Done\n");

  printf("Initializing Keyboard Driver... ");
  int kbd_drv_res = initialize_ps2_keyboard();
  switch(kbd_drv_res){
  case -1:
    printf("Failed to configure keyboard controller");
    break;
  case 0:
    printf("Done\n");
    break;
  case 1:
    printf("Failed self test\n");
    break;
  case 2:
    printf("Failed to set scan code\n");
    break;
  case 3:
    printf("Failed to set typematic data\n");
    break;
  case 4:
    printf("Failed to set keyboard LEDs\n");
    break;
  case 5:
    printf("Failed to enable key reading\n");
    break;
  default:
    printf("Unknown Error\n");
    break;
  }
  
  while(1){};
  
}
