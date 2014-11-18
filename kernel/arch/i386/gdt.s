;This file is part of Dan's Open Source Disk Operating System (DOSDOS).
;
;    DOSDOS is free software: you can redistribute it and/or modify
;    it under the terms of the GNU General Public License as published by
;    the Free Software Foundation, either version 3 of the License, or
;    (at your option) any later version.
;
;    DOSDOS is distributed in the hope that it will be useful,
;    but WITHOUT ANY WARRANTY; without even the implied warranty of
;    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;    GNU General Public License for more details.
;
;    You should have received a copy of the GNU General Public License
;    along with DOSDOS.  If not, see <http://www.gnu.org/licenses/>.

	;; gdt_flush()
	global gdt_flush
	extern gp
gdt_flush:
				; Load the GDT
	lgdt [gp]
				; Flush the values to 0x10
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:flush2
flush2:
	ret

	;; tss_flush()
	global tss_flush
tss_flush:
	mov ax, 0x2B
	ltr ax
	ret
