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
#include <kernel/low_level/isr.h>

static bool isFatal(uint32_t interrupt){
  return (interrupt != 99);
}

static char* interrupt_name(uint32_t intr){
  switch(intr){
  case 0:
    return "DIVIDE-BY-ZERO";
  case 1:
    return "DEBUG";
  case 2:
    return "NON-MASKABLE INTERRUPT";
  case 3:
    return "BREAKPOINT";
  case 4:
    return "OVERFLOW";
  case 5:
    return "BOUND RANGE EXCEEDED";
  case 6:
    return "INVALID OPCODE";
  case 7:
    return "DEVICE NOT AVAILABLE";
  case 8:
    return "DOUBLE FAULT";
  case 9:
    return "COPROCESSOR SEGMENT OVERRUN";
  case 10:
    return "INVALID TSS";
  case 11:
    return "SEGMENT NOT PRESENT";
  case 12:
    return "STACK-SEGMENT FAULT";
  case 13:
    return "GENERAL PROTECTION FAULT";
  case 14:
    return "PAGE FAULT";
  case 16:
    return "x87 FLOATING-POINT EXCEPTION";
  case 17:
    return "ALIGNMENT CHECK";
  case 18:
    return "MACHINE CHECK";
  case 19:
    return "SIMD FLOATING-POINT EXCEPTION";
  case 20:
    return "VIRTUALIZATION EXCEPTION";
  case 30:
    return "SECURITY EXCEPTION";
  default:
    return "UNKNOWN EXCEPTION";
  }
}

void isr_handler(registers_t* regs)
{
  if((regs->int_no < 32) && (isFatal(regs->int_no))){

    terminal_bluescreen();
    char* name = interrupt_name(regs->int_no);

    printf("\t\t\t\t\t\tSOMETHING JUST WENT VERY WRONG\n\nI'd like to");
    printf(" interject for a moment.  What you're referring to as:\n\n\t");
    printf("Interrupt %d\n\nIs in fact, a fatal exception, ", (int) regs->int_no);
    printf("or as I've recently taken to  calling it:\n\n");
    printf("\t%s with error code %p\n", name, (void *) regs->err_code);
    
    //Halt the machine
    while(1);
    
  }

  //Handle our IRQs
  //interrupt numbers 0-31 are reserved by intel, so subtract 32
  //to get the isa irq code.  32 is an arbitary number decided in the
  //PIC initialization code
  int isa_irq = (regs->int_no - 32);
  
  switch(isa_irq){
  case 0:
    //Programmable interval timer interrupt
    break;
  case 1:
    //Keyboard interrupt
    handle_keyboard_interrupt();
    break;
  }
  
  PIC_sendEOI(regs->int_no);
  
  return;
}


