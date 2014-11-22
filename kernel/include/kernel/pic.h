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

#ifndef _KERNEL_PIC_H
#define _KERNEL_PIC_H

#include <stdint.h>
#include <stdio.h>

#include <kernel/dos.h>

void PIC_sendEOI(uint8_t irq);
void PIC_remap(int offset1, int offset2);

void IRQ_set_mask(unsigned char IRQline);
void IRQ_clear_mask(unsigned char IRQline);

uint16_t pic_get_irr();
uint16_t pic_get_isr();

void enable_IRQ();

#endif
