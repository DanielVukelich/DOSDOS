#!/bin/sh
set -e
. ./build.sh
 
mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

#cp grub/efi.img isodir/efi.img
cp sysroot/boot/dosdos.kernel isodir/boot/dosdos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "DOSDOS" {
	multiboot /boot/dosdos.kernel
}
EOF
grub-mkrescue -d /usr/lib/grub/i386-pc/ -o dosdos.iso isodir
