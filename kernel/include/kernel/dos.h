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

#ifndef _KERNEL_DOS_H
#define _KERNEL_DOS_H

#include <stdbool.h>

static inline void outb(uint16_t port, uint8_t val){
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

static inline uint8_t inb(uint16_t port){
    uint8_t ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

static inline void io_wait(void){
    asm volatile ( "outb %%al, $0x80" : : "a"(0) );
}

#endif
