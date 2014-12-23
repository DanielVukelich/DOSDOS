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

#include "kernel/kmalloc.h"

memheader_t* memstart = NULL;

bool header_status(const memheader_t header){
  return (header.status % 2);
}

inline memheader_t* prev_memheader(memheader_t* current){
  return (memheader_t*) ((*current).status & 0xFFFFFFFE);
}

memheader_t* next_memheader(memheader_t* current){

  memheader_t* nextheader;
  
  if((*current).size){
    nextheader = (current + (*current).size + sizeof(memheader_t));
  }else{
    nextheader = prev_memheader(current);
  }

  return nextheader;
}

bool section_spansblocks(memheader_t* header){
  void* next = next_memheader(header);
  return (addr_to_block(next) != addr_to_block(header));
}

void* kmalloc(size_t size){

  //Size cannot be 0
  if(!size)
    return NULL;
  
  //Size must always be even
  if(size % 2)
    ++size;
  
  if(!memstart){
    size_t extra_blocks_to_get = ( (size + sizeof(memheader_t) ) / 4096);
    if(!extra_blocks_to_get){
      memstart = (memheader_t*) physmm_alloc_blocks(extra_blocks_to_get + 1);
    }else{
      memstart = (memheader_t*) physmm_alloc_block();
    }
    
    ++extra_blocks_to_get;

    //Register all of our newly alloc'd blocks here in the page-dir as belonging
    //To the kernel
    /*
    uint32_t* pagedirptr;
    for(size_t i = 0; i < extra_blocks_to_get; ++i){

    }
    */
    
    (*memstart).size = size;
    (*memstart).status = 0x00000001;
    
  }


  return NULL;
}
