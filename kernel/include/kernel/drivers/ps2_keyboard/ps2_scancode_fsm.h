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

#ifndef _KERNEL_PS2_SCANCODE_FSM_H
#define _KERNEL_PS2_SCANCODE_FSM_H

#include <stdint.h>

#include <kernel/services/keyboard_event/key_codes.h>

//Give the fsm a byte belonging to a scancode and return
//nonzero if the byte completes the scancode to a key press event.
//If it returns nonzero, then the last valid keycode submitted
//to the fsm will be updated and ready to read via get_last_keycode()
uint8_t register_scanbyte(uint8_t byte);

//Returns the last keycode submitted to the scancode fsm
uint16_t get_last_ps2_keycode();

#endif
