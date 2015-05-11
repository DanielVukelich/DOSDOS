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

#ifndef _KERNEL_KEYCODES_H
#define _KERNEL_KEYCODES_H

#include <stdint.h>

//Our Function keys
const uint16_t F1_PRES;
const uint16_t F1_RLSD;
const uint16_t F2_PRES;
const uint16_t F2_RLSD;
const uint16_t F3_PRES;
const uint16_t F3_RLSD;
const uint16_t F4_PRES;
const uint16_t F4_RLSD;
const uint16_t F5_PRES;
const uint16_t F5_RLSD;
const uint16_t F6_PRES;
const uint16_t F6_RLSD;
const uint16_t F7_PRES;
const uint16_t F7_RLSD;
const uint16_t F8_PRES;
const uint16_t F8_RLSD;
const uint16_t F9_PRES;
const uint16_t F9_RLSD;

//Our letter keys
const uint16_t A_PRES;
const uint16_t A_RLSD;
const uint16_t B_PRES;
const uint16_t B_RLSD;
const uint16_t C_PRES;
const uint16_t C_RLSD;
const uint16_t D_PRES;
const uint16_t D_RLSD;
const uint16_t E_PRES;
const uint16_t E_RLSD;
const uint16_t F_PRES;
const uint16_t F_RLSD;
const uint16_t G_PRES;
const uint16_t G_RLSD;
const uint16_t H_PRES;
const uint16_t H_RLSD;
const uint16_t I_PRES;
const uint16_t I_RLSD;
const uint16_t J_PRES;
const uint16_t J_RLSD;
const uint16_t K_PRES;
const uint16_t K_RLSD;
const uint16_t L_PRES;
const uint16_t L_RLSD;
const uint16_t M_PRES;
const uint16_t M_RLSD;
const uint16_t N_PRES;
const uint16_t N_RLSD;
const uint16_t O_PRES;
const uint16_t O_RLSD;
const uint16_t P_PRES;
const uint16_t P_RLSD;
const uint16_t Q_PRES;
const uint16_t Q_RLSD;
const uint16_t R_PRES;
const uint16_t R_RLSD;
const uint16_t S_PRES;
const uint16_t S_RLSD;
const uint16_t T_PRES;
const uint16_t T_RLSD;
const uint16_t U_PRES;
const uint16_t U_RLSD;
const uint16_t V_PRES;
const uint16_t V_RLSD;
const uint16_t W_PRES;
const uint16_t W_RLSD;
const uint16_t X_PRES;
const uint16_t X_RLSD;
const uint16_t Y_PRES;
const uint16_t Y_RLSD;
const uint16_t Z_PRES;
const uint16_t Z_RLSD;

//Our symbol keys
const uint16_t BACKTICK_PRES;
const uint16_t BACKTICK_RLSD;
const uint16_t DASH_PRES;
const uint16_t DASH_RLSD;
const uint16_t EQUAL_PRES;
const uint16_t EQUAL_RLSD;
const uint16_t BKSLSH_PRES;
const uint16_t BKSLSH_RLSD;
const uint16_t FWSLSH_PRES;
const uint16_t FWSLSH_RLSD;
const uint16_t LSQBRACE_PRES;
const uint16_t LSQBRACE_RLSD;
const uint16_t SEMICLN_PRES;
const uint16_t SEMICLN_RLSD;
const uint16_t COMMA_PRES;
const uint16_t COMMA_RLSD;
const uint16_t PERIOD_PRES;
const uint16_t PERIOD_RLSD;
const uint16_t APOSTROPHE_PRES;
const uint16_t APOSTROPHE_RLSD;

//Our top row number keys
//They are prefixed with T to help distinguish from the keypad numbers
const uint16_t T0_PRES;
const uint16_t T0_RLSD;
const uint16_t T1_PRES;
const uint16_t T1_RLSD;
const uint16_t T2_PRES;
const uint16_t T2_RLSD;
const uint16_t T3_PRES;
const uint16_t T3_RLSD;
const uint16_t T4_PRES;
const uint16_t T4_RLSD;
const uint16_t T5_PRES;
const uint16_t T5_RLSD;
const uint16_t T6_PRES;
const uint16_t T6_RLSD;
const uint16_t T7_PRES;
const uint16_t T7_RLSD;
const uint16_t T8_PRES;
const uint16_t T8_RLSD;
const uint16_t T9_PRES;
const uint16_t T9_RLSD;

//Our functional keys
const uint16_t ESC_PRES;
const uint16_t ESC_RLSD;
const uint16_t ENTER_PRES;
const uint16_t ENTER_RLSD;
const uint16_t TAB_PRES;
const uint16_t TAB_RLSD;
const uint16_t BKSPACE_PRES;
const uint16_t BKSPACE_RLSD;
const uint16_t SPACE_PRES;
const uint16_t SPACE_RLSD;
const uint16_t DELETE_PRES;
const uint16_t DELETE_RLSD;
const uint16_t CPSLCK_PRES;
const uint16_t CPSLCK_RLSD;
const uint16_t LSHIFT_PRES;
const uint16_t LSHIFT_RLSD;
const uint16_t RSHIFT_PRES;
const uint16_t RSHIFT_RLSD;
const uint16_t LCTRL_PRES;
const uint16_t LCTRL_RLSD;
const uint16_t RCTRL_PRES;
const uint16_t RCTRL_RLSD;
const uint16_t LALT_PRES;
const uint16_t LALT_RLSD;
const uint16_t RALT_PRES;
const uint16_t RALT_RLSD;

//Our arrow keys
const uint16_t UPARROW_PRES;
const uint16_t UPARROW_RLSD;
const uint16_t DNARROW_PRES;
const uint16_t DNARROW_RLSD;
const uint16_t LEFTARROW_PRES;
const uint16_t LEFTARROW_RLSD;
const uint16_t RIGHTARROW_PRES;
const uint16_t RIGHTARROW_RLSD;

//Misc keys on the main part of the keyboard
const uint16_t HOME_PRES;
const uint16_t HOME_RLSD;
const uint16_t PAUSE_PRES;
//const uint16_t PAUSE_RLSD;  There is no scan code for pause key released
const uint16_t INSERT_PRES;
const uint16_t INSERT_RLSD;
const uint16_t END_PRES;
const uint16_t END_RLSD;
const uint16_t BREAK_PRES;
const uint16_t BREAK_RLSD;
const uint16_t SCROLLCK_PRES;
const uint16_t SCROLLCK_RLSD;
const uint16_t PGUP_PRES;
const uint16_t PGUP_RLSD;
const uint16_t PGDN_PRES;
const uint16_t PGDN_RLSD;
const uint16_t PRINTSC_PRES;
const uint16_t PRINTSC_RLSD;

//Keypad keys
const uint16_t K0_PRES;
const uint16_t K0_RLSD;
const uint16_t K1_PRES;
const uint16_t K1_RLSD;
const uint16_t K2_PRES;
const uint16_t K2_RLSD;
const uint16_t K3_PRES;
const uint16_t K3_RLSD;
const uint16_t K4_PRES;
const uint16_t K4_RLSD;
const uint16_t K5_PRES;
const uint16_t K5_RLSD;
const uint16_t K6_PRES;
const uint16_t K6_RLSD;
const uint16_t K7_PRES;
const uint16_t K7_RLSD;
const uint16_t K8_PRES;
const uint16_t K8_RLSD;
const uint16_t K9_PRES;
const uint16_t K9_RLSD;
const uint16_t KENTER_PRES;
const uint16_t KENTER_RLSD;
const uint16_t KPERIOD_PRES;
const uint16_t KPERIOD_RLSD;
const uint16_t KDASH_PRES;
const uint16_t KDASH_RLSD;
const uint16_t KPLUS_PRES;
const uint16_t KPLUS_RLSD;
const uint16_t KSLASH_PRES;
const uint16_t KSLASH_RLSD;
const uint16_t KSTAR_PRES;
const uint16_t KSTAR_RLSD;
const uint16_t NUMLCK_PRES;
const uint16_t NUMLCK_RLSD;

//ACPI keys
const uint16_t PWR_PRES;
const uint16_t PWR_RLSD;
const uint16_t SLP_PRES;
const uint16_t SLP_RLSD;
const uint16_t WAKE_PRES;
const uint16_t WAKE_RLSD;

//Multimedia keys
const uint16_t WWWSRCH_PRES;
const uint16_t WWWSRCH_RLSD;
const uint16_t PREVTRCK_PRES;
const uint16_t PREVTRCK_RLSD;
const uint16_t WWWFAVS_PRES;
const uint16_t WWWFAVS_RLSD;
const uint16_t WWWREFRSH_PRES;
const uint16_t WWWREFRESH_RLSD;
const uint16_t VOLDN_PRES;
const uint16_t VOLDN_RLSD;
const uint16_t VOLUP_PRES;
const uint16_t VOLUP_RLSD;
const uint16_t MUTE_PRES;
const uint16_t MUTE_RLSD;
const uint16_t WWWSTOP_PRES;
const uint16_t WWWSTOP_RLSD;
const uint16_t WWWFWD_PRES;
const uint16_t WWWFWD_RLSD;
const uint16_t WWWREV_PRES;
const uint16_t WWWREV_RLSD;
const uint16_t PLAYPAUSE_PRES;
const uint16_t PLAYPAUSE_RLSD;
const uint16_t STOP_PRES;
const uint16_t STOP_RLSD;
const uint16_t WWWHOME_PRES;
const uint16_t WWWHOME_RLSD;
const uint16_t MYCMP_PRES;
const uint16_t MYCMP_RLSD;
const uint16_t EMAIL_PRES;
const uint16_t EMAIL_RLSD;
const uint16_t NEXTTRCK_PRES;
const uint16_t NEXTTRCK_RLSD;
const uint16_t MEDIASEL_PRES;
const uint16_t MEDIASEL_RLSD;

//WTF keys (Who knows what they're supposed to do?)
const uint16_t APPS_PRES;
const uint16_t APPS_RLSD;
const uint16_t LEFTGUI_PRES;
const uint16_t LEFTGUI_RLSD;
const uint16_t RIGHTGUI_PRES;
const uint16_t RIGHTGUI_RLSD;

#endif
