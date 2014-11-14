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

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
 
#if defined(__is_dosdos_kernel)
#include <kernel/tty.h>
#endif

const char* NUMBER_LIST = "0123456789ABCDEF";

int print_int(const int);
int print_anyhex(const char, const unsigned long);

static void print(const char* data, size_t data_length)
{
  for ( size_t i = 0; i < data_length; i++ )
    putchar((int) ((const unsigned char*) data)[i]);
}

int printf(const char* restrict format, ...)
{
  va_list parameters;
  va_start(parameters, format);
 
  int written = 0;
  size_t amount;
  bool rejected_bad_specifier = false;
 
  while ( *format != '\0' )
    {
      if ( *format != '%' )
	{
	print_c:
	  amount = 1;
	  while ( format[amount] && format[amount] != '%' )
	    amount++;
	  print(format, amount);

	  format += amount;
	  written += amount;
	  continue;
	}
 
      const char* format_begun_at = format;
 
      if ( *(++format) == '%' )
	goto print_c;
 
      if ( rejected_bad_specifier )
      {
	incomprehensible_conversion:
	rejected_bad_specifier = true;
	format = format_begun_at;
	goto print_c;
      }
 
      if ( *format == 'c' )
      {
	format++;
	char c = (char) va_arg(parameters, int);
	print(&c, sizeof(c));
	written++;
      }
      else if ( *format == 's' )
      {
	format++;
	const char* s = va_arg(parameters, const char*);
	print(s, strlen(s));
	written += strlen(s);
      }
      else if( *format == 'p'){
	format++;
	const void* p = va_arg(parameters, const void*);
	written += print_anyhex(sizeof(p), (unsigned long) p);
      }
      else if( *format == 'd' || *format == 'i'){
	format++;
	const int i = va_arg(parameters, const int);
	written += print_int(i);
      }
      else
      {
	goto incomprehensible_conversion;
      }
    }
 
  va_end(parameters);
 
  return written;
}

int print_anyhex(const char sizeof_ptr, const unsigned long cast_ptr){
  int siz = 2 * sizeof_ptr;

  printf("0x");
  
  for(int i = 0; i < siz; ++i){
    unsigned long copy = cast_ptr;
    copy = copy << (4 * i);	
    copy = (copy >> (4 * (siz - (i + 1)) + (4 * i)  )) % 16;
    char hex = NUMBER_LIST[copy];
    print(&hex,sizeof(hex));
  }
  
  return (2 + siz);
}

int print_int(const int val){

  int copy = val;
  int toreturn = 0;
	
  if(copy < 0){
    copy *= -1;
    char neg = '-';
    print(&neg, sizeof(neg));
    toreturn++;
  }

  //How many digits will we print?
  int baseten = 0;
  for(int j = copy; j > 0; j = j/ 10){
    ++baseten;
  }

  if(baseten == 0){
    char zero = '0';
    print(&zero, sizeof(zero));
    toreturn = 1;
  }
  
  for(baseten; baseten > 0; --baseten){

   toreturn++;
    
    int maskone = 1;
    //Maskone will be 10^baseten

    for(int j = 0; j < (baseten - 1); j++){
      maskone = maskone * 10;
    }
	  
    int masktwo =  (copy / maskone);
    //Masktwo is the leftmost digit of copy

    char digit = NUMBER_LIST[(masktwo % 10)];
    print(&digit, sizeof(digit));
    copy =  copy - (maskone * masktwo);
  }

  return toreturn;
}
