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

#include <kernel/drivers/ps2_keyboard/ps2_scancode_fsm.h>

//Define all the states for our fsm
#define BEGIN                0
#define FIRST_E0             1
#define FIRST_F0             2
#define E0_F0                3
#define E0_12_E0             4
#define E0_12                5
#define E0_F0_7C_E0_F0       6
#define E0_F0_7C             7
#define E0_F0_7C_E0          8
#define E1                   9
#define E1_14                10
#define E1_14_77             11
#define E1_14_77_E1          12
#define E1_14_77_E1_F0       13
#define E1_14_77_E1_F0_14    14
#define E1_14_77_E1_F0_14_F0 15

static uint16_t last_keycode = UNKWN;

static uint8_t state = BEGIN;
static uint8_t nstate = BEGIN;

uint8_t register_scanbyte(uint8_t byte){

  uint8_t makes_code = 0;
  
  switch(state){
  case BEGIN:
    //All the 1 byte scancodes
    switch(byte){
    case 0x01:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F9_PRES;
      break;
    case 0x03:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F5_PRES;
      break;
    case 0x04:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F3_PRES;
      break;
    case 0x05:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F1_PRES;
      break;
    case 0x06:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F2_PRES;
      break;
    case 0x07:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F12_PRES;
      break;
    case 0x09:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F10_PRES;
      break;
    case 0x0A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F8_PRES;
      break;
    case 0x0B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F6_PRES;
      break;
    case 0x0C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F4_PRES;
      break;
    case 0x0D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = TAB_PRES;
      break;
    case 0x0E:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = BACKTICK_PRES;
      break;
    case 0x11:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = LALT_PRES;
      break;
    case 0x12:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = LSHIFT_PRES;
      break;
    case 0x14:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = LCTRL_PRES;
      break;
    case 0x15:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = Q_PRES;
      break;
    case 0x16:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T1_PRES;
      break;
    case 0x1A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = Z_PRES;
      break;
    case 0x1B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = S_PRES;
      break;
    case 0x1C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = A_PRES;
      break;
    case 0x1D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = W_PRES;
      break;
    case 0x1E:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T2_PRES;
      break;
    case 0x21:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = C_PRES;
      break;
    case 0x22:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = X_PRES;
      break;
    case 0x23:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = D_PRES;
      break;
    case 0x24:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = E_PRES;
      break;
    case 0x25:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T4_PRES;
      break;
    case 0x26:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T3_PRES;
      break;
    case 0x29:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = SPACE_PRES;
      break;
    case 0x2A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = V_PRES;
      break;
    case 0x2B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F_PRES;
      break;
    case 0x2C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T_PRES;
      break;
    case 0x2D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = R_PRES;
      break;
    case 0x2E:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T5_PRES;
      break;
    case 0x31:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = N_PRES;
      break;
    case 0x32:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = B_PRES;
      break;
    case 0x33:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = H_PRES;
      break;
    case 0x34:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = G_PRES;
      break;
    case 0x35:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = Y_PRES;
      break;
    case 0x36:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T6_PRES;
      break;
    case 0x3A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = M_PRES;
      break;
    case 0x3B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = J_PRES;
      break;
    case 0x3C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = U_PRES;
      break;
    case 0x3D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T7_PRES;
      break;
    case 0x3E:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T8_PRES;
      break;
    case 0x41:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = COMMA_PRES;
      break;
    case 0x42:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K_PRES;
      break;
    case 0x43:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = I_PRES;
      break;
    case 0x44:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = O_PRES;
      break;
    case 0x45:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T0_PRES;
      break;
    case 0x46:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T9_PRES;
      break;
    case 0x49:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = PERIOD_PRES;
      break;
    case 0x4A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = FWSLSH_PRES;
      break;
    case 0x4B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = L_PRES;
      break;
    case 0x4C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = SEMICLN_PRES;
      break;
    case 0x4D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = P_PRES;
      break;
    case 0x4E:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = DASH_PRES;
      break;
    case 0x52:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = APOSTROPHE_PRES;
      break;
    case 0x54:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = LSQBRACE_PRES;
      break;
    case 0x55:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = EQUAL_PRES;
      break;
    case 0x58:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = CPSLCK_PRES;
      break;
    case 0x59:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = RSHIFT_PRES;
      break;
    case 0x5A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = ENTER_PRES;
      break;
    case 0x5B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = RSQBRACE_PRES;
      break;
    case 0x5D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = BKSLSH_PRES;
      break;
    case 0x66:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = BKSPACE_PRES;
      break;
    case 0x69:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K1_PRES;
      break;
    case 0x6B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K4_PRES;
      break;
    case 0x6C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K7_PRES;
      break;
    case 0x70:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K0_PRES;
      break;
    case 0x71:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = KPERIOD_PRES;
      break;
    case 0x72:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K2_PRES;
      break;
    case 0x73:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K5_PRES;
      break;
    case 0x74:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K6_PRES;
      break;
    case 0x75:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K8_PRES;
      break;
    case 0x76:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = ESC_PRES;
      break;
    case 0x77:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = NUMLCK_PRES;
      break;
    case 0x78:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F11_PRES;
      break;
    case 0x79:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = KPLUS_PRES;
      break;
    case 0x7A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K3_PRES;
      break;
    case 0x7B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = KDASH_PRES;
      break;
    case 0x7C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = KSTAR_PRES;
      break;
    case 0x7D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K9_PRES;
      break;
    case 0x7E:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = SCROLLCK_PRES;
      break;
    case 0x83:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F7_PRES;
      break;
    case 0xE0:
      nstate = FIRST_E0;
      break;
    case 0xF0:
      nstate = FIRST_F0;
      break;
    case 0xE1:
      nstate = E1;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;
    }
    break;
  case FIRST_E0:
    //All the scancodes starting with E0
    switch(byte){
    case 0x10:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WWWSRCH_PRES;      
      break;
    case 0x11:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = RALT_PRES;      
      break;
    case 0x14:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = RCTRL_PRES;      
      break;
    case 0x15:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = PREVTRCK_PRES;      
      break;
    case 0x18:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WWWFAVS_PRES;      
      break;
    case 0x1F:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = LGUI_PRES;      
      break;
    case 0x20:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WWWREFRESH_PRES;      
      break;
    case 0x21:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = VOLDN_PRES;      
      break;
    case 0x23:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = MUTE_PRES;      
      break;
    case 0x27:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = RGUI_PRES;      
      break;
    case 0x28:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WWWSTOP_PRES;      
      break;
    case 0x2B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = CALC_PRES;      
      break;
    case 0x2F:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = APPS_PRES;      
      break;
    case 0x30:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WWWFWD_PRES;      
      break;
    case 0x32:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = VOLUP_PRES;      
      break;
    case 0x34:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = PLAYPAUSE_PRES;      
      break;
    case 0x37:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = PWR_PRES;      
      break;
    case 0x38:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WWWREV_PRES;      
      break;
    case 0x3A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WWWHOME_PRES;      
      break;
    case 0x3B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = STOP_PRES;      
      break;
    case 0x3F:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = SLP_PRES;      
      break;
    case 0x40:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = MYCMP_PRES;      
      break;
    case 0x48:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = EMAIL_PRES;      
      break;
    case 0x4A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = KSLASH_PRES;      
      break;
    case 0x4D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = NEXTTRCK_PRES;      
      break;
    case 0x50:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = MEDIASEL_PRES;      
      break;
    case 0x5A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = KENTER_PRES;      
      break;
    case 0x5E:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WAKE_PRES;      
      break;
    case 0x69:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = END_PRES;      
      break;
    case 0x6B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = LEFTARROW_PRES;      
      break;
    case 0x6C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = HOME_PRES;      
      break;
    case 0x70:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = INSERT_PRES;      
      break;
    case 0x71:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = DELETE_PRES;      
      break;
    case 0x72:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = DNARROW_PRES;      
      break;
    case 0x74:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = RIGHTARROW_PRES;      
      break;
    case 0x75:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UPARROW_PRES;      
      break;
    case 0x7A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = PGDN_PRES;      
      break;
    case 0x7D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = PGUP_PRES;      
      break;      
    case 0xF0:
      nstate = E0_F0;
      break;
    case 0x12:
      nstate = E0_12;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;      
    }
    break;
  case FIRST_F0:
    switch(byte){
      //All the scancodes starting with F0 are the release codes of the
      //1 byte scancodes
    case 0x01:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F9_RLSD;
      break;
    case 0x03:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F5_RLSD;
      break;
    case 0x04:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F3_RLSD;
      break;
    case 0x05:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F1_RLSD;
      break;
    case 0x06:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F2_RLSD;
      break;
    case 0x07:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F12_RLSD;
      break;
    case 0x09:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F10_RLSD;
      break;
    case 0x0A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F8_RLSD;
      break;
    case 0x0B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F6_RLSD;
      break;
    case 0x0C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F4_RLSD;
      break;
    case 0x0D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = TAB_RLSD;
      break;
    case 0x0E:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = BACKTICK_RLSD;
      break;
    case 0x11:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = LALT_RLSD;
      break;
    case 0x12:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = LSHIFT_RLSD;
      break;
    case 0x14:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = LCTRL_RLSD;
      break;
    case 0x15:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = Q_RLSD;
      break;
    case 0x16:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T1_RLSD;
      break;
    case 0x1A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = Z_RLSD;
      break;
    case 0x1B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = S_RLSD;
      break;
    case 0x1C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = A_RLSD;
      break;
    case 0x1D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = W_RLSD;
      break;
    case 0x1E:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T2_RLSD;
      break;
    case 0x21:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = C_RLSD;
      break;
    case 0x22:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = X_RLSD;
      break;
    case 0x23:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = D_RLSD;
      break;
    case 0x24:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = E_RLSD;
      break;
    case 0x25:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T4_RLSD;
      break;
    case 0x26:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T3_RLSD;
      break;
    case 0x29:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = SPACE_RLSD;
      break;
    case 0x2A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = V_RLSD;
      break;
    case 0x2B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F_RLSD;
      break;
    case 0x2C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T_RLSD;
      break;
    case 0x2D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = R_RLSD;
      break;
    case 0x2E:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T5_RLSD;
      break;
    case 0x31:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = N_RLSD;
      break;
    case 0x32:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = B_RLSD;
      break;
    case 0x33:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = H_RLSD;
      break;
    case 0x34:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = G_RLSD;
      break;
    case 0x35:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = Y_RLSD;
      break;
    case 0x36:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T6_RLSD;
      break;
    case 0x3A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = M_RLSD;
      break;
    case 0x3B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = J_RLSD;
      break;
    case 0x3C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = U_RLSD;
      break;
    case 0x3D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T7_RLSD;
      break;
    case 0x3E:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T8_RLSD;
      break;
    case 0x41:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = COMMA_RLSD;
      break;
    case 0x42:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K_RLSD;
      break;
    case 0x43:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = I_RLSD;
      break;
    case 0x44:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = O_RLSD;
      break;
    case 0x45:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T0_RLSD;
      break;
    case 0x46:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = T9_RLSD;
      break;
    case 0x49:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = PERIOD_RLSD;
      break;
    case 0x4A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = FWSLSH_RLSD;
      break;
    case 0x4B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = L_RLSD;
      break;
    case 0x4C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = SEMICLN_RLSD;
      break;
    case 0x4D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = P_RLSD;
      break;
    case 0x4E:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = DASH_RLSD;
      break;
    case 0x52:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = APOSTROPHE_RLSD;
      break;
    case 0x54:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = LSQBRACE_RLSD;
      break;
    case 0x55:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = EQUAL_RLSD;
      break;
    case 0x58:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = CPSLCK_RLSD;
      break;
    case 0x59:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = RSHIFT_RLSD;
      break;
    case 0x5A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = ENTER_RLSD;
      break;
    case 0x5B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = RSQBRACE_RLSD;
      break;
    case 0x5D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = BKSLSH_RLSD;
      break;
    case 0x66:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = BKSPACE_RLSD;
      break;
    case 0x69:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K1_RLSD;
      break;
    case 0x6B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K4_RLSD;
      break;
    case 0x6C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K7_RLSD;
      break;
    case 0x70:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K0_RLSD;
      break;
    case 0x71:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = KPERIOD_RLSD;
      break;
    case 0x72:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K2_RLSD;
      break;
    case 0x73:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K5_RLSD;
      break;
    case 0x74:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K6_RLSD;
      break;
    case 0x75:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K8_RLSD;
      break;
    case 0x76:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = ESC_RLSD;
      break;
    case 0x77:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = NUMLCK_RLSD;
      break;
    case 0x78:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F11_RLSD;
      break;
    case 0x79:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = KPLUS_RLSD;
      break;
    case 0x7A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K3_RLSD;
      break;
    case 0x7B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = KDASH_RLSD;
      break;
    case 0x7C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = KSTAR_RLSD;
      break;
    case 0x7D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = K9_RLSD;
      break;
    case 0x7E:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = SCROLLCK_RLSD;
      break;
    case 0x83:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = F7_RLSD;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;      
    }
    break;
  case E0_F0:
    switch(byte){
      //All the scancodes starting with E0 then F0 are the release codes of
      //the codes starting with E0
    case 0x10:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WWWSRCH_RLSD;      
      break;
    case 0x11:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = RALT_RLSD;      
      break;
    case 0x14:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = RCTRL_RLSD;      
      break;
    case 0x15:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = PREVTRCK_RLSD;      
      break;
    case 0x18:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WWWFAVS_RLSD;      
      break;
    case 0x1F:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = LGUI_RLSD;      
      break;
    case 0x20:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WWWREFRESH_RLSD;      
      break;
    case 0x21:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = VOLDN_RLSD;      
      break;
    case 0x23:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = MUTE_RLSD;      
      break;
    case 0x27:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = RGUI_RLSD;      
      break;
    case 0x28:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WWWSTOP_RLSD;      
      break;
    case 0x2B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = CALC_RLSD;      
      break;
    case 0x2F:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = APPS_RLSD;      
      break;
    case 0x30:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WWWFWD_RLSD;      
      break;
    case 0x32:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = VOLUP_RLSD;      
      break;
    case 0x34:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = PLAYPAUSE_RLSD;      
      break;
    case 0x37:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = PWR_RLSD;      
      break;
    case 0x38:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WWWREV_RLSD;      
      break;
    case 0x3A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WWWHOME_RLSD;      
      break;
    case 0x3B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = STOP_RLSD;      
      break;
    case 0x3F:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = SLP_RLSD;      
      break;
    case 0x40:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = MYCMP_RLSD;      
      break;
    case 0x48:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = EMAIL_RLSD;      
      break;
    case 0x4A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = KSLASH_RLSD;      
      break;
    case 0x4D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = NEXTTRCK_RLSD;      
      break;
    case 0x50:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = MEDIASEL_RLSD;      
      break;
    case 0x5A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = KENTER_RLSD;      
      break;
    case 0x5E:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = WAKE_RLSD;      
      break;
    case 0x69:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = END_RLSD;      
      break;
    case 0x6B:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = LEFTARROW_RLSD;      
      break;
    case 0x6C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = HOME_RLSD;      
      break;
    case 0x70:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = INSERT_RLSD;      
      break;
    case 0x71:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = DELETE_RLSD;      
      break;
    case 0x72:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = DNARROW_RLSD;      
      break;
    case 0x74:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = RIGHTARROW_RLSD;      
      break;
    case 0x75:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UPARROW_RLSD;      
      break;
    case 0x7A:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = PGDN_RLSD;      
      break;
    case 0x7D:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = PGUP_RLSD;      
      break;
    case 0x7C:
      nstate = E0_F0_7C;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;      
    }
    break;
    //Everything below this line in the finite state machine is to deal with the misc.
    //scancodes that are super long wastes of time
  case E0_12:
    switch(byte){
    case 0xE0:
      nstate = E0_12_E0;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;      
    }
    break;
  case E0_12_E0:
    switch(byte){
    case 0x7C:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = PRINTSC_PRES;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;        
    }
    break;
  case E0_F0_7C:
    switch(byte){
    case 0xE0:
      nstate = E0_F0_7C_E0;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;      
    }
    break;
  case E0_F0_7C_E0:
    switch(byte){
    case 0xF0:
      nstate = E0_F0_7C_E0_F0;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;      
    }
    break;
  case E0_F0_7C_E0_F0:
    switch(byte){
    case 0x12:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = PRINTSC_RLSD;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;      
    }
    break;
  case E1:
    switch(byte){
    case 0x14:
      nstate = E1_14;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;      
    }
    break;
  case E1_14:
    switch(byte){
    case 0x77:
      nstate = E1_14_77;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;      
    }
    break;
  case E1_14_77:
    switch(byte){
    case 0xE1:
      nstate = E1_14_77_E1;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;      
    }
    break;
  case E1_14_77_E1:
    switch(byte){
    case 0xF0:
      nstate = E1_14_77_E1_F0;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;      
    }
    break;
  case E1_14_77_E1_F0:
    switch(byte){
    case 0x14:
      nstate = E1_14_77_E1_F0_14;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;      
    }
    break;
  case E1_14_77_E1_F0_14:
    switch(byte){
    case 0xF0:
      nstate = E1_14_77_E1_F0_14_F0;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;      
    }
    break;
  case E1_14_77_E1_F0_14_F0:
    switch(byte){
    case 0x77:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = PAUSE_PRES;
      break;
    default:
      ++makes_code;
      nstate = BEGIN;
      last_keycode = UNKWN;
      break;      
    }
    break;        
  default:
    //We are in an invalid state
    nstate = BEGIN;
    break;
  }

  state = nstate;
  return makes_code;
}
  
uint16_t get_last_ps2_keycode(){
  return last_keycode;
}
