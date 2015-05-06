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

#include <kernel/drivers/keyboard.h>

#include <stdio.h>

//Commands you can send
#define SET_LEDS             0xED
#define GET_SET_SCAN_CODE    0xF0
#define SET_TYPEMATIC_RATE   0xF3
#define ENABLE_SCANNING      0xF4
#define DISABLE_SCANNING     0xF5

//Typical responses
#define ACK                  0xFA
#define RESEND               0xFE

//Self test commands and responses
#define SELF_TEST            0xFF
#define SELF_TEST_PASS       0xAA
#define SELF_TEST_FAIL1      0xFC
#define SELF_TEST_FAIL2      0xFD

//Values we may commonly wish to send
#define SCAN_CODE_2          0x02
#define TYPEMATIC_DATA       0x6E  //Repeat rate close to 10Hz, Delay before repeat 250ms

//Data registers of the PS/2 Controller
#define PS2_DATA_REG         0x60
#define PS2_STATUS_CMD_REG   0x64

//Define bytes to send to the PS/2 Controller
#define PS2_CONFIG_MASK      0xBD  //Disable bits 1 and 6
#define GET_CONFIG_BYTE      0x20
#define SET_CONFIG_BYTE      0x60

//Max number of times we poll the PS/2 Status register
#define MAX_PS2_POLLS        1000
//Max number of times to attempt to resend a byte
#define MAX_RESEND_ATTEMPTS    3

static uint8_t led_states;
volatile bool received_interrupt;
static bool initialized = false;

typedef struct kbd_response{
  //Whether or not there was an error sending
  bool send_error;
  //The response code from the keyboard's data register
  uint8_t response_code;
}kbd_response_t;

//Sends one byte (either data or command) to the keyboard
//Returns true if there was an error
bool send_byte_to_kbd(uint8_t cmd){
  
  //Poll the PS/2 status register until we time out or get a
  //response with bit 1 clear
  int i;  
  for(i = 0; i < MAX_PS2_POLLS; ++i){
    uint8_t response = inb(PS2_STATUS_CMD_REG);

    //If we have a clear bit 1, then we can send a command
    if(!(response & 2))
      break;
  }

  //Did we time out?
  if(i == MAX_PS2_POLLS)
    return true;

  //Now write the command to the PS/2 Data register
  outb(PS2_DATA_REG, cmd);

  //Now we wait for the keyboard interrupt to tell us the response
  return false;
}

//Sends a command byte to the keyboard.
kbd_response_t send_command_byte(uint8_t cmd){

  int i = 0;

  kbd_response_t toreturn = {true, RESEND};
  
  do{
    bool waserror = send_byte_to_kbd(cmd);
    received_interrupt = false;
    //No error when sending the byte?  Then check for the response
    if(!waserror){
      
      //Loop until out keyboard interrupt says we received a response
      while(!received_interrupt);
      
      uint8_t response = inb(PS2_DATA_REG);
      
      //If we didn't get asked for a resend, then it was sent successfully
      if(response != RESEND){
	toreturn.send_error = false;
	toreturn.response_code = response;
	return toreturn;
      }
    }
  }
  while(i < MAX_RESEND_ATTEMPTS);

  //Return a keyboard response saying we encountered an error
  return toreturn;
}

kbd_response_t send_command(uint8_t cmd, uint8_t data){

  int i = 0;
  kbd_response_t toreturn = {true, RESEND};
  received_interrupt = false;
    
  do{
    bool waserror = send_byte_to_kbd(cmd);
    
    //Loop infinitely until we get an interrupt
    //printf(" ");
    while(!received_interrupt);
    received_interrupt = false;

    uint8_t response = inb(PS2_DATA_REG);
    
    //If we sent the command successfully, try sending the data
    if(!waserror && response != RESEND){
      
      waserror = send_byte_to_kbd(data);

      //Loop infinitely until we get an interrupt
      while(!received_interrupt);
      response = inb(PS2_DATA_REG);
      
      //If we sent the data successfully, read the response
      if(!waserror){
	
	//If we didn't get asked to resend, then the command and the data were sent successfully
	if(response != RESEND){
	  toreturn.send_error = false;
	  toreturn.response_code = response;
	  return toreturn;
	}
      }
    }
  }
  while(i < MAX_RESEND_ATTEMPTS);
  
  //We couldn't send both the command byte and the data byte
  return toreturn;
}


//Initializes the Keyboard.
//Error codes:
//0 No error
//1 Failed self test
//2 Failed to set to scan code mode 2
//3 Failed to set typematic data
//4 Failed to set the key lock LEDs
//5 Failed to enable key scanning
int initialize_ps2_keyboard(){

  //Read from the ps2 controller's config byte
  outb(PS2_STATUS_CMD_REG, GET_CONFIG_BYTE);
  //Wait for the status register to say we have the config byte
  while(!(inb(PS2_STATUS_CMD_REG) % 2)){
    io_wait();
  }
  //Read the config byte
  uint8_t configbyte = inb(PS2_DATA_REG);
  //Mask it with what we want it to be and then send it back in
  configbyte &= PS2_CONFIG_MASK;
  outb(PS2_STATUS_CMD_REG, SET_CONFIG_BYTE);
  //Wait until we can send the new config byte
  while(inb(PS2_STATUS_CMD_REG & 2)){
    io_wait();
  }
  //Write our new config byte out
  outb(PS2_DATA_REG, configbyte);
  
  //Run the keyboard self test
  kbd_response_t response = send_command_byte(SELF_TEST);
  io_wait();
  response.response_code = inb(PS2_DATA_REG);
  if(response.send_error || (response.response_code != SELF_TEST_PASS))
    return 1;
  
  //Now set it to use scan code mode 2
  //response = send_command(GET_SET_SCAN_CODE, SCAN_CODE_2);
  response = send_command_byte(GET_SET_SCAN_CODE);
  if(response.send_error)
    return 2;
  
  //Now set the typematic settings
  response = send_command(SET_TYPEMATIC_RATE, TYPEMATIC_DATA);
  if(response.send_error)
    return 3;

  //Not set the key lock LEDS to all be on
  led_states = 3;
  response = send_command(SET_LEDS, led_states);
  if(response.send_error)
    return 4;
  
  //Now enable key scanning
  response = send_command_byte(ENABLE_SCANNING);
  if(response.send_error)
    return 5;

  initialized = true;
  return 0;
}

void set_lock_led(uint8_t lock){
  led_states |= lock;
  send_command(SET_LEDS, led_states);
}

void unset_lock_led(uint8_t lock){
  led_states &= (~lock);
  send_command(SET_LEDS, led_states);
}

void toggle_lock_led(uint8_t lock){
  led_states ^= lock;
  send_command(SET_LEDS, led_states);
}

bool get_lock_led(uint8_t lock){
  return (led_states & lock);
}

void handle_keyboard_interrupt(){
  if(!initialized){
    received_interrupt = true;
    return;
  }
  
  printf("Pressed a key %i ", (int) inb(0x60));
}
