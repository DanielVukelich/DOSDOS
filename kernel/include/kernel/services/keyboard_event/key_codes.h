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

//Unrecognized key event
#define UNKWN 65535

//Our Function keys
#define F1_PRES 0
#define F1_RLSD 1
#define F2_PRES 2
#define F2_RLSD 3
#define F3_PRES 4
#define F3_RLSD 5
#define F4_PRES 6
#define F4_RLSD 7
#define F5_PRES 8
#define F5_RLSD 9
#define F6_PRES 10
#define F6_RLSD 11
#define F7_PRES 12
#define F7_RLSD 13
#define F8_PRES 14
#define F8_RLSD 15
#define F9_PRES 16
#define F9_RLSD 17
#define F10_PRES 18
#define F10_RLSD 19
#define F11_PRES 20
#define F11_RLSD 21
#define F12_PRES 22
#define F12_RLSD 23

//Our letter keys
#define A_PRES 24
#define A_RLSD 25
#define B_PRES 26
#define B_RLSD 27
#define C_PRES 28
#define C_RLSD 29
#define D_PRES 30
#define D_RLSD 31
#define E_PRES 32
#define E_RLSD 33
#define F_PRES 34
#define F_RLSD 35
#define G_PRES 36
#define G_RLSD 37
#define H_PRES 38
#define H_RLSD 39
#define I_PRES 40
#define I_RLSD 41
#define J_PRES 42
#define J_RLSD 43
#define K_PRES 44
#define K_RLSD 45
#define L_PRES 46
#define L_RLSD 47
#define M_PRES 48
#define M_RLSD 49
#define N_PRES 50
#define N_RLSD 51
#define O_PRES 52
#define O_RLSD 53
#define P_PRES 54
#define P_RLSD 55
#define Q_PRES 56
#define Q_RLSD 57
#define R_PRES 58
#define R_RLSD 59
#define S_PRES 60
#define S_RLSD 61
#define T_PRES 62
#define T_RLSD 63
#define U_PRES 64
#define U_RLSD 65
#define V_PRES 66
#define V_RLSD 67
#define W_PRES 68
#define W_RLSD 69
#define X_PRES 70
#define X_RLSD 71
#define Y_PRES 72
#define Y_RLSD 73
#define Z_PRES 74
#define Z_RLSD 75

//Our symbol keys
#define BACKTICK_PRES 76
#define BACKTICK_RLSD 77
#define DASH_PRES 78
#define DASH_RLSD 79
#define EQUAL_PRES 80
#define EQUAL_RLSD 81
#define BKSLSH_PRES 82
#define BKSLSH_RLSD 83
#define FWSLSH_PRES 83
#define FWSLSH_RLSD 85
#define LSQBRACE_PRES 86
#define LSQBRACE_RLSD 87
#define RSQBRACE_PRES 88
#define RSQBRACE_RLSD 89
#define SEMICLN_PRES 90
#define SEMICLN_RLSD 91
#define COMMA_PRES 92
#define COMMA_RLSD 93
#define PERIOD_PRES 94
#define PERIOD_RLSD 95
#define APOSTROPHE_PRES 96
#define APOSTROPHE_RLSD 97

//Our top row number keys
//They are prefixed with T to help distinguish from the keypad numbers
#define T0_PRES 98
#define T0_RLSD 99
#define T1_PRES 100
#define T1_RLSD 101
#define T2_PRES 102
#define T2_RLSD 103
#define T3_PRES 104
#define T3_RLSD 104
#define T4_PRES 106
#define T4_RLSD 107
#define T5_PRES 108
#define T5_RLSD 109
#define T6_PRES 110
#define T6_RLSD 111
#define T7_PRES 112
#define T7_RLSD 113
#define T8_PRES 114
#define T8_RLSD 115
#define T9_PRES 116
#define T9_RLSD 117

//Our functional keys
#define ESC_PRES 118
#define ESC_RLSD 119
#define ENTER_PRES 120
#define ENTER_RLSD 121
#define TAB_PRES 122
#define TAB_RLSD 123
#define BKSPACE_PRES 124
#define BKSPACE_RLSD 125
#define SPACE_PRES 126
#define SPACE_RLSD 127
#define DELETE_PRES 128
#define DELETE_RLSD 129
#define CPSLCK_PRES 130
#define CPSLCK_RLSD 131
#define LSHIFT_PRES 132
#define LSHIFT_RLSD 133
#define RSHIFT_PRES 134
#define RSHIFT_RLSD 135
#define LCTRL_PRES 136
#define LCTRL_RLSD 137
#define RCTRL_PRES 138
#define RCTRL_RLSD 139
#define LALT_PRES 140
#define LALT_RLSD 141
#define RALT_PRES 142
#define RALT_RLSD 143

//Our arrow keys
#define UPARROW_PRES 144
#define UPARROW_RLSD 145
#define DNARROW_PRES 146
#define DNARROW_RLSD 147
#define LEFTARROW_PRES 148
#define LEFTARROW_RLSD 149
#define RIGHTARROW_PRES 150
#define RIGHTARROW_RLSD 151

//Misc keys on the main part of the keyboard
#define HOME_PRES 152
#define HOME_RLSD 153
#define PAUSE_PRES 154
//#define PAUSE_RLSD 155 There is no scan code for pause key released
#define INSERT_PRES 156
#define INSERT_RLSD 157
#define END_PRES 158
#define END_RLSD 159
#define BREAK_PRES 160
#define BREAK_RLSD 161
#define SCROLLCK_PRES 162
#define SCROLLCK_RLSD 163
#define PGUP_PRES 164
#define PGUP_RLSD 165
#define PGDN_PRES 166
#define PGDN_RLSD 167
#define PRINTSC_PRES 168
#define PRINTSC_RLSD 169

//Keypad keys
#define K0_PRES 170
#define K0_RLSD 171
#define K1_PRES 172
#define K1_RLSD 173
#define K2_PRES 174
#define K2_RLSD 175
#define K3_PRES 176
#define K3_RLSD 177
#define K4_PRES 178
#define K4_RLSD 179
#define K5_PRES 180
#define K5_RLSD 181
#define K6_PRES 182
#define K6_RLSD 183
#define K7_PRES 184
#define K7_RLSD 184
#define K8_PRES 186
#define K8_RLSD 187
#define K9_PRES 188
#define K9_RLSD 189
#define KENTER_PRES 190
#define KENTER_RLSD 191
#define KPERIOD_PRES 192
#define KPERIOD_RLSD 193
#define KDASH_PRES 194
#define KDASH_RLSD 195
#define KPLUS_PRES 196
#define KPLUS_RLSD 197
#define KSLASH_PRES 198
#define KSLASH_RLSD 199
#define KSTAR_PRES 200
#define KSTAR_RLSD 201
#define NUMLCK_PRES 202
#define NUMLCK_RLSD 203

//ACPI keys
#define PWR_PRES 204
#define PWR_RLSD 205
#define SLP_PRES 206
#define SLP_RLSD 207
#define WAKE_PRES 208
#define WAKE_RLSD 209

//Multimedia keys
#define WWWSRCH_PRES 210
#define WWWSRCH_RLSD 211
#define PREVTRCK_PRES 212
#define PREVTRCK_RLSD 213
#define WWWFAVS_PRES 214
#define WWWFAVS_RLSD 215
#define WWWREFRESH_PRES 216
#define WWWREFRESH_RLSD 217
#define VOLDN_PRES 218
#define VOLDN_RLSD 219
#define VOLUP_PRES 220
#define VOLUP_RLSD 221
#define MUTE_PRES 222
#define MUTE_RLSD 223
#define WWWSTOP_PRES 224
#define WWWSTOP_RLSD 225
#define WWWFWD_PRES 226
#define WWWFWD_RLSD 227
#define WWWREV_PRES 228
#define WWWREV_RLSD 229
#define PLAYPAUSE_PRES 230
#define PLAYPAUSE_RLSD 231
#define STOP_PRES 232
#define STOP_RLSD 233
#define WWWHOME_PRES 234
#define WWWHOME_RLSD 235
#define MYCMP_PRES 236
#define MYCMP_RLSD 237
#define EMAIL_PRES 238
#define EMAIL_RLSD 239
#define NEXTTRCK_PRES 240
#define NEXTTRCK_RLSD 241
#define MEDIASEL_PRES 242
#define MEDIASEL_RLSD 243
#define CALC_PRES 244
#define CALC_RLSD 245

//WTF keys (Who knows what they're supposed to do?)
#define APPS_PRES 246
#define APPS_RLSD 247
#define LGUI_PRES 248
#define LGUI_RLSD 249
#define RGUI_PRES 250
#define RGUI_RLSD 251

#endif
