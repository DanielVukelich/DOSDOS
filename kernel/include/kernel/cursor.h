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

#ifndef _KERNEL_CURSOR_H
#define _KERNEL_CURSOR_H

//const unsigned short CRTC_ADDR = 0x3D4;

bool cursor_setpos(unsigned short x, unsigned short y);
bool cursor_toggle();
bool cursor_ishidden();

void cursor_hide();
void cursor_show();

#endif
