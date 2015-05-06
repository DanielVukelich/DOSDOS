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

#ifndef _KERNEL_KEYBOARD_H
#define _KERNEL_KEYBOARD_H

#include <stdint.h>

#include <kernel/utils/dos.h>
#include <kernel/low_level/isr.h>
//Valid choices for lock are as follows:
//0: Scroll lock
//1: Num lock
//2: Caps lock
void set_lock_led(uint8_t lock);
void unset_lock_led(uint8_t lock);
void toggle_lock_led(uint8_t lock);
bool get_lock_led(uint8_t lock);

int initialize_ps2_keyboard();

void handle_keyboard_interrupt();

#endif
