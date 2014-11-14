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
#include <stdbool.h>

#include <kernel/dos.h>

const unsigned short CRTC_ADDR = 0x3D4;

bool cursor_setpos(unsigned short x, unsigned short y);
bool cursor_toggle();
bool cursor_ishidden();

void cursor_hide();
void cursor_show();

bool cursorhidden = false;

bool cursor_ishidden(){
  return cursorhidden;
}

bool cursor_toggle(){
  if(cursorhidden)
    cursor_show();
  else
    cursor_hide();

  return cursorhidden;
}

void cursor_hide(){
  outb(CRTC_ADDR + 0, 0x0A);
  outb(CRTC_ADDR + 1, 0x2F);
  outb(CRTC_ADDR + 0, 0x0B);
  outb(CRTC_ADDR + 1, 0x0F);
  cursorhidden = true;
  return;
}

void cursor_show(){
  outb(CRTC_ADDR + 0, 0x0A);
  outb(CRTC_ADDR + 1, 0x0F);
  outb(CRTC_ADDR + 0, 0x0B);
  outb(CRTC_ADDR + 1, 0x0F);
  cursorhidden = false;
  return;
}

bool cursor_setpos(unsigned short x, unsigned short y){
  
  unsigned short offset = x + y * 80;
  outb(CRTC_ADDR + 0, 14);
  outb(CRTC_ADDR + 1, offset >> 8);
  outb(CRTC_ADDR + 0, 15);
  outb(CRTC_ADDR + 1, offset);

  return cursorhidden;
}


