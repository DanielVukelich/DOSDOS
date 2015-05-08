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

#include <kernel/drivers/key_codes.h>

//Our Function keys
const uint16_t F1_PRES = 0;
const uint16_t F1_RLSD = 1;
const uint16_t F2_PRES = 2;
const uint16_t F2_RLSD = 3;
const uint16_t F3_PRES = 4;
const uint16_t F3_RLSD = 5;
const uint16_t F4_PRES = 6;
const uint16_t F4_RLSD = 7;
const uint16_t F5_PRES = 8;
const uint16_t F5_RLSD = 9;
const uint16_t F6_PRES = 10;
const uint16_t F6_RLSD = 11;
const uint16_t F7_PRES = 12;
const uint16_t F7_RLSD = 13;
const uint16_t F8_PRES = 14;
const uint16_t F8_RLSD = 15;
const uint16_t F9_PRES = 16;
const uint16_t F9_RLSD = 17;

//Our letter keys
const uint16_t A_PRES = 18;
const uint16_t A_RLSD = 19;
const uint16_t B_PRES = 20;
const uint16_t B_RLSD = 21;
const uint16_t C_PRES = 22;
const uint16_t C_RLSD = 23;
const uint16_t D_PRES = 24;
const uint16_t D_RLSD = 25;
const uint16_t E_PRES = 26;
const uint16_t E_RLSD = 27;
const uint16_t F_PRES = 28;
const uint16_t F_RLSD = 29;
const uint16_t G_PRES = 30;
const uint16_t G_RLSD = 31;
const uint16_t H_PRES = 32;
const uint16_t H_RLSD = 33;
const uint16_t I_PRES = 34;
const uint16_t I_RLSD = 35;
const uint16_t J_PRES = 36;
const uint16_t J_RLSD = 37;
const uint16_t K_PRES = 38;
const uint16_t K_RLSD = 39;
const uint16_t L_PRES = 40;
const uint16_t L_RLSD = 41;
const uint16_t M_PRES = 42;
const uint16_t M_RLSD = 43;
const uint16_t N_PRES = 44;
const uint16_t N_RLSD = 45;
const uint16_t O_PRES = 46;
const uint16_t O_RLSD = 47;
const uint16_t P_PRES = 48;
const uint16_t P_RLSD = 49;
const uint16_t Q_PRES = 50;
const uint16_t Q_RLSD = 51;
const uint16_t R_PRES = 52;
const uint16_t R_RLSD = 53;
const uint16_t S_PRES = 54;
const uint16_t S_RLSD = 55;
const uint16_t T_PRES = 56;
const uint16_t T_RLSD = 57;
const uint16_t U_PRES = 58;
const uint16_t U_RLSD = 59;
const uint16_t V_PRES = 60;
const uint16_t V_RLSD = 61;
const uint16_t W_PRES = 62;
const uint16_t W_RLSD = 63;
const uint16_t X_PRES = 64;
const uint16_t X_RLSD = 65;
const uint16_t Y_PRES = 66;
const uint16_t Y_RLSD = 67;
const uint16_t Z_PRES = 68;
const uint16_t Z_RLSD = 69;

//Our symbol keys
const uint16_t BACKTICK_PRES = 70;
const uint16_t BACKTICK_RLSD = 71;
const uint16_t DASH_PRES = 72;
const uint16_t DASH_RLSD = 73;
const uint16_t EQUAL_PRES = 74;
const uint16_t EQUAL_RLSD = 75;
const uint16_t BKSLSH_PRES = 76;
const uint16_t BKSLSH_RLSD = 77;
const uint16_t FWSLSH_PRES = 78;
const uint16_t FWSLSH_RLSD = 79;
const uint16_t LSQBRACE_PRES = 80;
const uint16_t LSQBRACE_RLSD = 81;
const uint16_t SEMICLN_PRES = 82;
const uint16_t SEMICLN_RLSD = 83;
const uint16_t COMMA_PRES = 84;
const uint16_t COMMA_RLSD = 85;
const uint16_t PERIOD_PRES = 86;
const uint16_t PERIOD_RLSD = 87;
const uint16_t APOSTROPHE_PRES = 88;
const uint16_t APOSTROPHE_RLSD = 89;

//Our top row number keys
//They are prefixed with T to help distinguish from the keypad numbers
const uint16_t T0_PRES = 90;
const uint16_t T0_RLSD = 91;
const uint16_t T1_PRES = 92;
const uint16_t T1_RLSD = 93;
const uint16_t T2_PRES = 94;
const uint16_t T2_RLSD = 95;
const uint16_t T3_PRES = 96;
const uint16_t T3_RLSD = 97;
const uint16_t T4_PRES = 98;
const uint16_t T4_RLSD = 99;
const uint16_t T5_PRES = 100;
const uint16_t T5_RLSD = 101;
const uint16_t T6_PRES = 102;
const uint16_t T6_RLSD = 103;
const uint16_t T7_PRES = 104;
const uint16_t T7_RLSD = 105;
const uint16_t T8_PRES = 106;
const uint16_t T8_RLSD = 107;
const uint16_t T9_PRES = 108;
const uint16_t T9_RLSD = 109;

//Our functional keys
const uint16_t ESC_PRES = 110;
const uint16_t ESC_RLSD = 111;
const uint16_t ENTER_PRES = 112;
const uint16_t ENTER_RLSD = 113;
const uint16_t TAB_PRES = 114;
const uint16_t TAB_RLSD = 115;
const uint16_t BKSPACE_PRES = 116;
const uint16_t BKSPACE_RLSD = 117;
const uint16_t SPACE_PRES = 118;
const uint16_t SPACE_RLSD = 119;
const uint16_t DELETE_PRES = 120;
const uint16_t DELETE_RLSD = 121;
const uint16_t CPSLCK_PRES = 122;
const uint16_t CPSLCK_RLSD = 123;
const uint16_t LSHIFT_PRES = 124;
const uint16_t LSHIFT_RLSD = 125;
const uint16_t RSHIFT_PRES = 126;
const uint16_t RSHIFT_RLSD = 127;
const uint16_t LCTRL_PRES = 128;
const uint16_t LCTRL_RLSD = 129;
const uint16_t RCTRL_PRES = 130;
const uint16_t RCTRL_RLSD = 131;
const uint16_t LALT_PRES = 132;
const uint16_t LALT_RLSD = 133;
const uint16_t RALT_PRES = 134;
const uint16_t RALT_RLSD = 135;

//Our arrow keys
const uint16_t UPARROW_PRES = 136;
const uint16_t UPARROW_RLSD = 137;
const uint16_t DNARROW_PRES = 138;
const uint16_t DNARROW_RLSD = 139;
const uint16_t LEFTARROW_PRES = 140;
const uint16_t LEFTARROW_RLSD = 141;
const uint16_t RIGHTARROW_PRES = 142;
const uint16_t RIGHTARROW_RLSD = 143;

//Misc keys on the main part of the keyboard
const uint16_t HOME_PRES = 144;
const uint16_t HOME_RLSD = 145;
const uint16_t PAUSE_PRES = 146;
//const uint16_t PAUSE_RLSD = 147;  There is no scan code for pause key released
const uint16_t INSERT_PRES = 148;
const uint16_t INSERT_RLSD = 149;
const uint16_t END_PRES = 150;
const uint16_t END_RLSD = 151;
const uint16_t BREAK_PRES = 152;
const uint16_t BREAK_RLSD = 153;
const uint16_t SCROLLCK_PRES = 154;
const uint16_t SCROLLCK_RLSD = 155;
const uint16_t PGUP_PRES = 156;
const uint16_t PGUP_RLSD = 157;
const uint16_t PGDN_PRES = 158;
const uint16_t PGDN_RLSD = 159;
const uint16_t PRINTSC_PRES = 160;
const uint16_t PRINTSC_RLSD = 161;

//Keypad keys
const uint16_t K0_PRES = 162;
const uint16_t K0_RLSD = 163;
const uint16_t K1_PRES = 164;
const uint16_t K1_RLSD = 165;
const uint16_t K2_PRES = 166;
const uint16_t K2_RLSD = 167;
const uint16_t K3_PRES = 168;
const uint16_t K3_RLSD = 169;
const uint16_t K4_PRES = 170;
const uint16_t K4_RLSD = 171;
const uint16_t K5_PRES = 172;
const uint16_t K5_RLSD = 173;
const uint16_t K6_PRES = 174;
const uint16_t K6_RLSD = 175;
const uint16_t K7_PRES = 176;
const uint16_t K7_RLSD = 177;
const uint16_t K8_PRES = 178;
const uint16_t K8_RLSD = 179;
const uint16_t K9_PRES = 180;
const uint16_t K9_RLSD = 181;
const uint16_t KENTER_PRES = 182;
const uint16_t KENTER_RLSD = 183;
const uint16_t KPERIOD_PRES = 184;
const uint16_t KPERIOD_RLSD = 185;
const uint16_t KDASH_PRES = 186;
const uint16_t KDASH_RLSD = 187;
const uint16_t KPLUS_PRES = 188;
const uint16_t KPLUS_RLSD = 189;
const uint16_t KSLASH_PRES = 190;
const uint16_t KSLASH_RLSD = 191;
const uint16_t KSTAR_PRES = 192;
const uint16_t KSTAR_RLSD = 193;
const uint16_t NUMLCK_PRES = 194; 
const uint16_t NUMLCK_RLSD = 195;

//ACPI keys
const uint16_t PWR_PRES = 196;
const uint16_t PWR_RLSD = 197;
const uint16_t SLP_PRES = 198;
const uint16_t SLP_RLSD = 199;
const uint16_t WAKE_PRES = 200;
const uint16_t WAKE_RLSD = 201;

//Multimedia keys
const uint16_t WWWSRCH_PRES = 202;
const uint16_t WWWSRCH_RLSD = 203;
const uint16_t PREVTRCK_PRES = 204;
const uint16_t PREVTRCK_RLSD = 205;
const uint16_t WWWFAVS_PRES = 206;
const uint16_t WWWFAVS_RLSD = 207;
const uint16_t WWWREFRSH_PRES = 208;
const uint16_t WWWREFRESH_RLSD = 209;
const uint16_t VOLDN_PRES = 210;
const uint16_t VOLDN_RLSD = 211;
const uint16_t VOLUP_PRES = 212;
const uint16_t VOLUP_RLSD = 213;
const uint16_t MUTE_PRES = 214;
const uint16_t MUTE_RLSD = 215;
const uint16_t WWWSTOP_PRES = 216;
const uint16_t WWWSTOP_RLSD = 217;
const uint16_t WWWFWD_PRES = 218;
const uint16_t WWWFWD_RLSD = 219;
const uint16_t WWWREV_PRES = 220;
const uint16_t WWWREV_RLSD = 221;
const uint16_t PLAYPAUSE_PRES = 222;
const uint16_t PLAYPAUSE_RLSD = 223;
const uint16_t STOP_PRES = 224;
const uint16_t STOP_RLSD = 225;
const uint16_t WWWHOME_PRES = 226;
const uint16_t WWWHOME_RLSD = 227;
const uint16_t MYCMP_PRES = 228;
const uint16_t MYCMP_RLSD = 229;
const uint16_t EMAIL_PRES = 230;
const uint16_t EMAIL_RLSD = 231;
const uint16_t NEXTTRCK_PRES = 232;
const uint16_t NEXTTRCK_RLSD = 233;
const uint16_t MEDIASEL_PRES = 234;
const uint16_t MEDIASEL_RLSD = 235;

//WTF keys (Who knows what they're supposed to do?)
const uint16_t APPS_PRES = 236;
const uint16_t APPS_RLSD = 237;
const uint16_t LEFTGUI_PRES = 238;
const uint16_t LEFTGUI_RLSD = 239;
const uint16_t RIGHTGUI_PRES = 240;
const uint16_t RIGHTGUI_RLSD = 241;
