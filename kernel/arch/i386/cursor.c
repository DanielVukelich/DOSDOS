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

#include <stdint.h>

#include <kernel/dos.h>

void cursor_setpos(unsigned short x, unsigned short y);

void cursor_setpos(unsigned short x, unsigned short y){
  
  unsigned short crtc_adr = 0x3D4; /* 0x3B4 for monochrome */

  unsigned short offset = x + y * 80;
  outb(crtc_adr + 0, 14);
  outb(crtc_adr + 1, offset >> 8);
  outb(crtc_adr + 0, 15);
  outb(crtc_adr + 1, offset);

  return;
}


