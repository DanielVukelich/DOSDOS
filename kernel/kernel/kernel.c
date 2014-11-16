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

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include <kernel/tty.h>
#include <kernel/cursor.h>
#include <kernel/multiboot.h>

extern uint32_t endkernel;
memory_map_t* init_mmap(multiboot_info_t* mbt);
   
void kernel_early(void)
{
  terminal_initialize();
}

void kernel_main(multiboot_info_t* mbt, unsigned int magicvoid)
{
  
  init_mmap(mbt);
  
  cursor_hide();
  abort();
}

memory_map_t* init_mmap(multiboot_info_t* mbt){

  unsigned long flags = (mbt->flags) >> 6;

  if(!(flags % 2)){
    printf("Multiboot memory map error");
    return NULL;
  }

  unsigned long mmap_entries = mbt->mmap_length / sizeof(memory_map_t);
  memory_map_t* mmap = mbt->mmap_addr;

  printf("\n                   MEMORY MAP\n\n");
  printf("Type |         Start         |         Length\n");
  
  for(int i = 0; i < mmap_entries; i++){
    char type = mmap[i].type;
    void* start = mmap[i].base_addr_low;
    void* start_h = mmap[i].base_addr_high;
    void* length = mmap[i].length_low;
    void* length_h = mmap[i].length_high;

    printf("%d    | %p:%p | %p:%p\n", type, start_h, start, length_h, length);
    
  }

  printf("\n\n");

  return mmap;
  
}
