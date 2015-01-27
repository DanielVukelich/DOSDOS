# DOSDOS
####Dan's Open Source Operating System

DOSDOS is a 32-bit hobby OS by Daniel Vukelich.  It's goal is to be a fun project exploring OS development, and nothing more.  It implements a kernel written completely from scratch as well as its own implementation of the C standard library.

## Current State
DOSDOS currently supports the following functionality:
* Hardware and Software Interrupts
* Exception and Fault catching
* Physcial Memory Management
* Paging
* Virtual Memory Management
* A minimal subset of the C standard library

## Immediate Future Plans
 The next steps in plan for DOSDOS include:
 * Streamlining Virtual Memory management
 * Writing keyboard drivers
 * Expanding the C standard library to the point where meaningful programs can be written with it
 * Basic CLI

## Farther Future Plans:
These are the very long term plans for DOSDOS are:
* Add a filesystem
* Write HDD drivers
* Have DOSDOS run on a HDD with persistence
* Build various open-source programs to run on DOSDOS
* Have DOSDOS be able to compile itself from source

## Building:
 DODSDOS requires a crossplatform build of gcc in order to build.  Instructions for obtaining a crossplatform build of gcc is beyond the scope of this readme, but suffice to say that instructions can be found here: http://wiki.osdev.org/GCC_Cross-Compiler.
 
 Once you have a working version of `i686-elf-gcc` in your `$PATH`, you are able to now build DOSDOS.  Building requires no additional dependencies.  To build, simply run `build.sh`.
 If you want to turn the build into a bootable .iso, installing GRUB and running `iso.sh`.  Lastly, if you have qemu installed, you can run the dosdos.iso in a virtual machine by running `qemu.sh`.
 All of the above steps, from building to loading the iso into qemu, can be run in one go by running `fullbuild` from the root project directory.
