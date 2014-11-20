#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
 
#include <kernel/vga.h>
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize(void);
void terminal_setcolor(uint8_t);
void terminal_putentryat(char, uint8_t, size_t, size_t);
void terminal_putchar(char);
bool terminal_putspecialchar(char);
void terminal_write(const char*, size_t);
void terminal_writestring(const char*);
void terminal_rowreplace(size_t oldrow, size_t newrow);
void terminal_rowblank(size_t row);

void terminal_clear(){
  for(size_t i = 0; i < VGA_HEIGHT; ++i){
    terminal_rowblank(i);
  }
  terminal_row = 0;
  terminal_column = 0;
}

void terminal_rowreplace(size_t oldrow, size_t newrow){

  if( (oldrow >= VGA_HEIGHT) || (newrow >= VGA_HEIGHT) || (oldrow < 0) || (newrow < 0) )
    return;

  for(int x = 0; x < VGA_WIDTH; ++x){
    int indexold = (oldrow * VGA_WIDTH) + x;
    int indexnew = (newrow * VGA_WIDTH) + x;

    terminal_buffer[indexold] = terminal_buffer[indexnew];
    
  }

}

void terminal_rowblank(size_t row){

  if(row >= VGA_HEIGHT || row < 0)
    return;

  for(int x = 0; x < VGA_WIDTH; ++x){
    int index = (row * VGA_WIDTH) + x;
    terminal_buffer[index] = make_vgaentry("\0", terminal_color);
  }
  
}

void terminal_initialize(void)
{
  terminal_row = 0;
  terminal_column = 0;
  terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
  terminal_buffer = VGA_MEMORY;
  for ( size_t y = 0; y < VGA_HEIGHT; y++ )
    {
      for ( size_t x = 0; x < VGA_WIDTH; x++ )
	{
	  const size_t index = y * VGA_WIDTH + x;
	  terminal_buffer[index] = make_vgaentry(' ', terminal_color);
	}
    }
}
 
void terminal_setcolor(uint8_t color)
{
  terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = make_vgaentry(c, color);
}
 
void terminal_putchar(char c)
{
  if(!terminal_putspecialchar(c)){
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    ++terminal_column;
  }

  if(terminal_column == VGA_WIDTH){
    terminal_column = 0;
    ++terminal_row;
  }

  if(terminal_row == VGA_HEIGHT){
    //Scroll the screen
    for(int y = 0; y < VGA_HEIGHT; y++){
      terminal_rowreplace(y,y+1);
    }

    terminal_row = VGA_HEIGHT - 1;
    terminal_rowblank(terminal_row);
    
  }
  
}

bool terminal_putspecialchar(char c)
{
  
  char* tab = "    ";

  switch (c)
    {
    case '\n':
      terminal_row++;
      terminal_column = 0;
      return true;
      break;
    case '\t':
      terminal_writestring(tab);
      return true;
      break;
    default:
      return false;
    }
  
}
 
void terminal_write(const char* data, size_t size)
{
  for ( size_t i = 0; i < size; i++ )
    terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data)
{
  terminal_write(data, strlen(data));
}

void terminal_bluescreen(){
  terminal_color = make_color(COLOR_WHITE, COLOR_BLUE);
  terminal_clear();
}
