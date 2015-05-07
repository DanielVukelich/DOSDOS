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
#define MAX_RESEND_ATTEMPTS  3

//Max bytes to try to send asynchronously to the keyboard
#define MAX_COMMAND_BUFFER_SIZE  100

typedef struct async_cmd{
  uint8_t cmd;
  uint8_t tries;
  uint8_t data_size;
}async_cmd_t;

static uint8_t led_states;

volatile bool scanning_is_enabled;

static async_cmd_t command_buffer[MAX_COMMAND_BUFFER_SIZE];
static uint8_t command_buffer_head;
static uint8_t command_buffer_tail;
static uint8_t command_buffer_size;
static uint8_t last_answered_cmd;

volatile bool awaiting_async_command;

volatile bool received_interrupt;
static bool initialized;

//Sends one byte (either data or command) to the keyboard
//Returns true if there was an error
bool send_byte_to_controller(uint8_t cmd){
  
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

kbd_response_t run_self_test(){
  int i = 0;

  kbd_response_t toreturn = {true, RESEND};
  
  do{
    
    received_interrupt = false;
    bool waserror = send_byte_to_controller(SELF_TEST);
    //No error when sending the byte?  Then check for the response
    if(!waserror){
      
      //Loop until our keyboard interrupt says we received a response
      while(!received_interrupt);
      received_interrupt = false;
      
      uint8_t response = inb(PS2_DATA_REG);
      
      //If we didn't get asked for a resend, then it was sent successfully
      if(response != RESEND){
	//We may still have to wait for the test results if all we get is
	//an acknowledgement of the test command being received
	if(response == ACK){
	  while(!received_interrupt);
	  response = inb(PS2_DATA_REG);
	}
	toreturn.send_error = false;
	toreturn.response_code = response;
	return toreturn;
      }
    }
    ++i;
  }
  while(i < MAX_RESEND_ATTEMPTS);
  
  //Return a keyboard response saying we encountered an error
  return toreturn;
}

//Sends a command byte to the keyboard.
//Note that this is blocking and not asynchronous
kbd_response_t send_command_byte(uint8_t cmd){

  int i = 0;

  kbd_response_t toreturn = {true, RESEND};
  
  do{
    
    received_interrupt = false;
    bool waserror = send_byte_to_controller(cmd);
    //No error when sending the byte?  Then check for the response
    if(!waserror){
      
      //Loop until our keyboard interrupt says we received a response
      while(!received_interrupt);
      
      uint8_t response = inb(PS2_DATA_REG);
      
      //If we didn't get asked for a resend, then it was sent successfully
      if(response != RESEND){
	toreturn.send_error = false;
	toreturn.response_code = response;
	return toreturn;
      }
    }
    ++i;
  }
  while(i < MAX_RESEND_ATTEMPTS);
  
  //Return a keyboard response saying we encountered an error
  return toreturn;
}

//Sends a command and data byte to the keyboard.  Note that this
//is blocking and not asynchronous
kbd_response_t send_command(uint8_t cmd, uint8_t data){

  int i = 0;
  kbd_response_t toreturn = {true, RESEND};
    
  do{
    received_interrupt = false;
    bool waserror = send_byte_to_controller(cmd);
    
    //Loop infinitely until we get an interrupt
    while(!received_interrupt);

    uint8_t response = inb(PS2_DATA_REG);

    //If we sent the command successfully, try sending the data
    if(!waserror && response != RESEND){
      
      received_interrupt = false;
      waserror = send_byte_to_controller(data);

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
    ++i;
  }
  while(i < MAX_RESEND_ATTEMPTS);
  
  //We couldn't send both the command byte and the data byte
  return toreturn;
}


//Initializes the Keyboard.
//Error codes:
//-1 Failed to configure keyboard conroller
//0 No error
//1 Failed self test
//2 Failed to set to scan code mode 2
//3 Failed to set typematic data
//4 Failed to set the key lock LEDs
//5 Failed to enable key scanning
int initialize_ps2_keyboard(){

  initialized = false;

  kbd_response_t response;

  //Disable scanning
  response = send_command_byte(DISABLE_SCANNING);
  if(response.send_error)
    return -1;

  scanning_is_enabled = false;
  
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

  //Write our new config byte
  //First the command
  outb(PS2_STATUS_CMD_REG, SET_CONFIG_BYTE);
  //And then write the config byte
  if(send_byte_to_controller(configbyte))
    return -1;

  //Run the keyboard self test
  response = run_self_test();
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

  //Turn the key lock LEDs off and then on
  //Turn them off
  led_states = 3;
  response = send_command(SET_LEDS, led_states);
  if(response.send_error)
    return 4;
  //Now turn them on
  led_states = 0;
  response = send_command(SET_LEDS, led_states);
  if(response.send_error)
    return 4;
  
  //Now enable key scanning
  response = send_command_byte(ENABLE_SCANNING);
  if(response.send_error)
    return 5;

  scanning_is_enabled = true;

  command_buffer_head = 0;
  command_buffer_tail = 0;
  command_buffer_size = 0;
  last_answered_cmd = 0;
  awaiting_async_command = false;
  initialized = true;
  return 0;
}

void send_next_async_cmd(){
  //If our buffer is empty, then do nothing
  if(!command_buffer_size)
    return;
  //Our buffer is not empty, so send the byte and let our interrupt handler know that we
  //are expecting an async interrupt
  awaiting_async_command = true;
  outb(PS2_DATA_REG, command_buffer[command_buffer_head].cmd);
  return;
}

//Attempts to queue an asynchronus keyboard command.
//Returns true if there was an error
bool queue_async_cmd_byte(uint8_t cmd, uint8_t data_size){
  //Fuck off, we're full :^)
  if(command_buffer_size == MAX_COMMAND_BUFFER_SIZE)
    return true;
  
  //Add our command to the end of the buffer queue.
  command_buffer[command_buffer_tail].cmd = cmd;
  command_buffer[command_buffer_tail].tries = 0;
  command_buffer[command_buffer_tail].data_size = data_size;
  //Move the tail of the queue back
  ++command_buffer_size;
  command_buffer_tail = (command_buffer_tail + 1) % MAX_COMMAND_BUFFER_SIZE;
  
  //If we're not already waiting for an async cmd, then send this one right off
  if(!awaiting_async_command)
    send_next_async_cmd();
  
  return false;
}

//Tries to queue up an asynchronus command with data
//Returns true if one or both could not be fitted in the buffer
bool queue_async_cmd_bytes(uint8_t cmd, uint8_t data, uint8_t data_size){
  if((command_buffer_size + 2) >= MAX_COMMAND_BUFFER_SIZE)
    return true;
  queue_async_cmd_byte(cmd, 1);
  queue_async_cmd_byte(data, data_size);
  return false;
}

kbd_response_t recv_async_cmd(){

  //Keep track of the command that this response belongs to
  last_answered_cmd = command_buffer_head;
  
  kbd_response_t toreturn = {false, RESEND};
  //We received our interrupt, now read what we got
  uint8_t response = inb(PS2_DATA_REG);
  //If we must resend, increment the number of tries for the current datum
  if(response == RESEND){
    ++(command_buffer[command_buffer_head].tries);
    //If we failed too many times.  Give up on the current command
    if(command_buffer[command_buffer_head].tries >= MAX_RESEND_ATTEMPTS){
      --command_buffer_size;
      command_buffer_head = (command_buffer_head + 1) % MAX_COMMAND_BUFFER_SIZE;
      awaiting_async_command = false;
      send_next_async_cmd();
      toreturn.send_error = true;
    }
    return toreturn;
  }
  //We got a response, take note of it.
  //Decrement the amount of data the we still need to read
  toreturn.response_code = response;
  --(command_buffer[command_buffer_head].data_size);
  //If we have no data left to read, then we can stop waiting for this command
  if(!command_buffer[command_buffer_head].data_size){
    --command_buffer_size;
    command_buffer_head = (command_buffer_head + 1) % MAX_COMMAND_BUFFER_SIZE;
    awaiting_async_command = false;
    send_next_async_cmd();
  }
  return toreturn;
}

void set_lock_led(uint8_t lock){
  if(!initialized)
    return;
  led_states |= (1 << (lock % 3));
  queue_async_cmd_bytes(SET_LEDS, led_states, 1);
}

void unset_lock_led(uint8_t lock){
  if(!initialized)
    return;
  led_states &= ~(1 << (lock % 3));
  queue_async_cmd_bytes(SET_LEDS, led_states, 1);
}

void toggle_lock_led(uint8_t lock){
  if(!initialized)
    return;
  led_states ^= (1 << (lock % 3));
  queue_async_cmd_bytes(SET_LEDS, led_states, 1);
}

bool get_lock_led(uint8_t lock){
  return (led_states & (1 << (lock % 3)));
}
    
void disable_key_scanning(){
  if(!scanning_is_enabled || !initialized)
    return;
  queue_async_cmd_byte(DISABLE_SCANNING, 1);
  return;
}

void enable_key_scanning(){
  if(scanning_is_enabled || !initialized)
    return;
  queue_async_cmd_byte(ENABLE_SCANNING, 1);
  return;
}

bool key_scanning_is_enabled(){
  return scanning_is_enabled;
}

void handle_keyboard_interrupt(){
  
  if(!initialized){
    received_interrupt = true;
    return;
  }

  if(awaiting_async_command){
    kbd_response_t resp = recv_async_cmd();
    //We've received the response.  Now get the command it belonged to,
    //and do different things based off of what that command was
    async_cmd_t command = command_buffer[last_answered_cmd];
    switch(command.cmd){
    case DISABLE_SCANNING:
      if(resp.response_code == ACK)
	scanning_is_enabled = false;
      break;
    case ENABLE_SCANNING:
      if(resp.response_code == ACK)
	scanning_is_enabled = true;
      break;
    default:
      break;
    }
    return;
  }
  
  printf("Scan code %i ", (int) inb(0x60));
  return;
}
