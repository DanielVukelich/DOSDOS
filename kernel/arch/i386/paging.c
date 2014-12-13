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

#include "kernel/paging.h"

extern void loadPageDirectory(uint32_t*);
extern void enablePaging();

void init_pageDir(uint32_t* dirptr){

  //Init all tables to:
  //Supervisor (only kernel can access)
  //Read+Write
  //Not present
  
  for(int i = 0; i < 1024; ++i){
    dirptr[i] = 0x00000002;
  }
  
}

void init_KernelPT(uint32_t* tabptr){

  for(int i = 0; i < 1024; ++i){
    //Supervisor
    //Read+Write
    //Present
    tabptr[i] = (i * 0x1000) | 3;
  }
  
}

void insert_KernelPTentry(uint32_t* dirptr, uint32_t* tabptr, uint32_t dirindex){
  //Supervisor
  //Read+Write
  //Present
  dirptr[dirindex] = ( (uint32_t) tabptr ) | 3;
}

void init_paging(uint32_t* dirptr, uint32_t* tabptr){
  init_pageDir(dirptr);
  init_KernelPT(tabptr);

  //Identity paging for the whole address space
  //This is, of course, only temporary
  for(int i = 0; i < 1024; ++i){
    insert_KernelPTentry(dirptr, tabptr, i);
  }
  
  loadPageDirectory(dirptr);
  enablePaging();
}

