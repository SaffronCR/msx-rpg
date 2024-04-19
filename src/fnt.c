//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_sprites.h"
#include "fusion-c/header/vdp_graph2.h"

#include "main.h"
#include "gfx.h"
#include "fnt.h"

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

// Font images offset.

#define FONT_OFFSET_X 0
#define FONT_OFFSET_Y 44

// Lowercase.

#define LOWER_A_X		8
#define LOWER_A_Y		196
#define LOWER_B_X		16
#define LOWER_B_Y		196
#define LOWER_C_X		24
#define LOWER_C_Y		196
#define LOWER_D_X		32
#define LOWER_D_Y		196
#define LOWER_E_X		40
#define LOWER_E_Y		196
#define LOWER_F_X		48
#define LOWER_F_Y		196
#define LOWER_G_X		56
#define LOWER_G_Y		196
#define LOWER_H_X		64
#define LOWER_H_Y		196
#define LOWER_I_X		72
#define LOWER_I_Y		196
#define LOWER_J_X		80
#define LOWER_J_Y		196
#define LOWER_K_X		88
#define LOWER_K_Y		196
#define LOWER_L_X		96
#define LOWER_L_Y		196
#define LOWER_M_X		104
#define LOWER_M_Y		196
#define LOWER_N_X		112
#define LOWER_N_Y		196
#define LOWER_O_X		120
#define LOWER_O_Y		196
#define LOWER_P_X		0
#define LOWER_P_Y		204
#define LOWER_Q_X		8
#define LOWER_Q_Y		204
#define LOWER_R_X		16
#define LOWER_R_Y		204
#define LOWER_S_X		24
#define LOWER_S_Y		204
#define LOWER_T_X		32
#define LOWER_T_Y		204
#define LOWER_U_X		40
#define LOWER_U_Y		204
#define LOWER_V_X		48
#define LOWER_V_Y		204
#define LOWER_W_X		56
#define LOWER_W_Y		204
#define LOWER_X_X		64
#define LOWER_X_Y		204
#define LOWER_Y_X		72
#define LOWER_Y_Y		204
#define LOWER_Z_X		80
#define LOWER_Z_Y		204

// Uppercase.

#define UPPER_A_X		8
#define UPPER_A_Y		180
#define UPPER_B_X		16
#define UPPER_B_Y		180
#define UPPER_C_X		24
#define UPPER_C_Y		180
#define UPPER_D_X		32
#define UPPER_D_Y		180
#define UPPER_E_X		40
#define UPPER_E_Y		180
#define UPPER_F_X		48
#define UPPER_F_Y		180
#define UPPER_G_X		56
#define UPPER_G_Y		180
#define UPPER_H_X		64
#define UPPER_H_Y		180
#define UPPER_I_X		72
#define UPPER_I_Y		180
#define UPPER_J_X		80
#define UPPER_J_Y		180
#define UPPER_K_X		88
#define UPPER_K_Y		180
#define UPPER_L_X		96
#define UPPER_L_Y		180
#define UPPER_M_X		104
#define UPPER_M_Y		180
#define UPPER_N_X		112
#define UPPER_N_Y		180
#define UPPER_O_X		120
#define UPPER_O_Y		180
#define UPPER_P_X		0
#define UPPER_P_Y		188
#define UPPER_Q_X		8
#define UPPER_Q_Y		188
#define UPPER_R_X		16
#define UPPER_R_Y		188
#define UPPER_S_X		24
#define UPPER_S_Y		188
#define UPPER_T_X		32
#define UPPER_T_Y		188
#define UPPER_U_X		40
#define UPPER_U_Y		188
#define UPPER_V_X		48
#define UPPER_V_Y		188
#define UPPER_W_X		56
#define UPPER_W_Y		188
#define UPPER_X_X		64
#define UPPER_X_Y		188
#define UPPER_Y_X		72
#define UPPER_Y_Y		188
#define UPPER_Z_X		80
#define UPPER_Z_Y		188

// Numbers.

#define ZERO_X   0
#define ZERO_Y   164
#define ONE_X    8
#define ONE_Y    164
#define TWO_X    16
#define TWO_Y    164
#define THREE_X  24
#define THREE_Y  164
#define FOUR_X   32
#define FOUR_Y   164
#define FIVE_X   40
#define FIVE_Y   164
#define SIX_X    48
#define SIX_Y    164
#define SEVEN_X  56
#define SEVEN_Y  164
#define EIGHT_X  64
#define EIGHT_Y  164
#define NINE_X   72
#define NINE_Y   164

// Symbols.

#define DOT_X		80
#define DOT_Y  		164
#define COMMA_X		88
#define COMMA_Y  	164
#define SPACE_X  	120
#define SPACE_Y  	204
#define HEART_X		0
#define HEART_Y		180
#define COPY_X		0
#define COPY_Y		196
#define ASTERISK_X	48
#define ASTERISK_Y	172
#define EXCLA_X  	24
#define EXCLA_Y  	172
#define PLUS_X		104
#define PLUS_Y		172
#define MINUS_X		112
#define MINUS_Y		172
#define SLASH_X		120
#define SLASH_Y		172
#define COLON_X		88
#define COLON_Y		188

// Textbox.

#define TXTBOX_UP_L_X	88
#define TXTBOX_UP_L_Y	204
#define TXTBOX_UP_R_X	104
#define TXTBOX_UP_R_Y	204
#define TXTBOX_DWN_L_X	104
#define TXTBOX_DWN_L_Y	188
#define TXTBOX_DWN_R_X	112
#define TXTBOX_DWN_R_Y	188
#define TXTBOX_MID_X	96
#define TXTBOX_MID_Y	204
#define TXTBOX_LAT_X	112
#define TXTBOX_LAT_Y	204

// Cursor.

#define CURSOR_X 129
#define CURSOR_Y 0

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_draw_char_src_to_dst(uint src_x, uint src_y, uint dst_x, uint dst_y, uchar log_op)
{
	sr_page_copy_mode(FONT_OFFSET_X + src_x, FONT_OFFSET_Y + src_y, FONT_SIZE, FONT_SIZE, dst_x, dst_y, FONT_PAGE, sr_get_active_page(), log_op);
}

void sr_draw_char(uchar character, uint x, uint y, uchar log_op)
{
	switch (character)
	{
		case 'a': sr_draw_char_src_to_dst(LOWER_A_X, LOWER_A_Y, x, y, log_op); break;
		case 'b': sr_draw_char_src_to_dst(LOWER_B_X, LOWER_B_Y, x, y, log_op); break;
		case 'c': sr_draw_char_src_to_dst(LOWER_C_X, LOWER_C_Y, x, y, log_op); break;
		case 'd': sr_draw_char_src_to_dst(LOWER_D_X, LOWER_D_Y, x, y, log_op); break;
		case 'e': sr_draw_char_src_to_dst(LOWER_E_X, LOWER_E_Y, x, y, log_op); break;
		case 'f': sr_draw_char_src_to_dst(LOWER_F_X, LOWER_F_Y, x, y, log_op); break;
		case 'g': sr_draw_char_src_to_dst(LOWER_G_X, LOWER_G_Y, x, y, log_op); break;
		case 'h': sr_draw_char_src_to_dst(LOWER_H_X, LOWER_H_Y, x, y, log_op); break;
		case 'i': sr_draw_char_src_to_dst(LOWER_I_X, LOWER_I_Y, x, y, log_op); break;
		case 'j': sr_draw_char_src_to_dst(LOWER_J_X, LOWER_J_Y, x, y, log_op); break;
		case 'k': sr_draw_char_src_to_dst(LOWER_K_X, LOWER_K_Y, x, y, log_op); break;
		case 'l': sr_draw_char_src_to_dst(LOWER_L_X, LOWER_L_Y, x, y, log_op); break;
		case 'm': sr_draw_char_src_to_dst(LOWER_M_X, LOWER_M_Y, x, y, log_op); break;
		case 'n': sr_draw_char_src_to_dst(LOWER_N_X, LOWER_N_Y, x, y, log_op); break;
		case 'o': sr_draw_char_src_to_dst(LOWER_O_X, LOWER_O_Y, x, y, log_op); break;
		case 'p': sr_draw_char_src_to_dst(LOWER_P_X, LOWER_P_Y, x, y, log_op); break;
		case 'q': sr_draw_char_src_to_dst(LOWER_Q_X, LOWER_Q_Y, x, y, log_op); break;
		case 'r': sr_draw_char_src_to_dst(LOWER_R_X, LOWER_R_Y, x, y, log_op); break;
		case 's': sr_draw_char_src_to_dst(LOWER_S_X, LOWER_S_Y, x, y, log_op); break;
		case 't': sr_draw_char_src_to_dst(LOWER_T_X, LOWER_T_Y, x, y, log_op); break;
		case 'u': sr_draw_char_src_to_dst(LOWER_U_X, LOWER_U_Y, x, y, log_op); break;
		case 'v': sr_draw_char_src_to_dst(LOWER_V_X, LOWER_V_Y, x, y, log_op); break;
		case 'w': sr_draw_char_src_to_dst(LOWER_W_X, LOWER_W_Y, x, y, log_op); break;
		case 'x': sr_draw_char_src_to_dst(LOWER_X_X, LOWER_X_Y, x, y, log_op); break;
		case 'y': sr_draw_char_src_to_dst(LOWER_Y_X, LOWER_Y_Y, x, y, log_op); break;
		case 'z': sr_draw_char_src_to_dst(LOWER_Z_X, LOWER_Z_Y, x, y, log_op); break;

		case 'A': sr_draw_char_src_to_dst(UPPER_A_X, UPPER_A_Y, x, y, log_op); break;
		case 'B': sr_draw_char_src_to_dst(UPPER_B_X, UPPER_B_Y, x, y, log_op); break;
		case 'C': sr_draw_char_src_to_dst(UPPER_C_X, UPPER_C_Y, x, y, log_op); break;
		case 'D': sr_draw_char_src_to_dst(UPPER_D_X, UPPER_D_Y, x, y, log_op); break;
		case 'E': sr_draw_char_src_to_dst(UPPER_E_X, UPPER_E_Y, x, y, log_op); break;
		case 'F': sr_draw_char_src_to_dst(UPPER_F_X, UPPER_F_Y, x, y, log_op); break;
		case 'G': sr_draw_char_src_to_dst(UPPER_G_X, UPPER_G_Y, x, y, log_op); break;
		case 'H': sr_draw_char_src_to_dst(UPPER_H_X, UPPER_H_Y, x, y, log_op); break;
		case 'I': sr_draw_char_src_to_dst(UPPER_I_X, UPPER_I_Y, x, y, log_op); break;
		case 'J': sr_draw_char_src_to_dst(UPPER_J_X, UPPER_J_Y, x, y, log_op); break;
		case 'K': sr_draw_char_src_to_dst(UPPER_K_X, UPPER_K_Y, x, y, log_op); break;
		case 'L': sr_draw_char_src_to_dst(UPPER_L_X, UPPER_L_Y, x, y, log_op); break;
		case 'M': sr_draw_char_src_to_dst(UPPER_M_X, UPPER_M_Y, x, y, log_op); break;
		case 'N': sr_draw_char_src_to_dst(UPPER_N_X, UPPER_N_Y, x, y, log_op); break;
		case 'O': sr_draw_char_src_to_dst(UPPER_O_X, UPPER_O_Y, x, y, log_op); break;
		case 'P': sr_draw_char_src_to_dst(UPPER_P_X, UPPER_P_Y, x, y, log_op); break;
		case 'Q': sr_draw_char_src_to_dst(UPPER_Q_X, UPPER_Q_Y, x, y, log_op); break;
		case 'R': sr_draw_char_src_to_dst(UPPER_R_X, UPPER_R_Y, x, y, log_op); break;
		case 'S': sr_draw_char_src_to_dst(UPPER_S_X, UPPER_S_Y, x, y, log_op); break;
		case 'T': sr_draw_char_src_to_dst(UPPER_T_X, UPPER_T_Y, x, y, log_op); break;
		case 'U': sr_draw_char_src_to_dst(UPPER_U_X, UPPER_U_Y, x, y, log_op); break;
		case 'V': sr_draw_char_src_to_dst(UPPER_V_X, UPPER_V_Y, x, y, log_op); break;
		case 'W': sr_draw_char_src_to_dst(UPPER_W_X, UPPER_W_Y, x, y, log_op); break;
		case 'X': sr_draw_char_src_to_dst(UPPER_X_X, UPPER_X_Y, x, y, log_op); break;
		case 'Y': sr_draw_char_src_to_dst(UPPER_Y_X, UPPER_Y_Y, x, y, log_op); break;
		case 'Z': sr_draw_char_src_to_dst(UPPER_Z_X, UPPER_Z_Y, x, y, log_op); break;

		case '0': sr_draw_char_src_to_dst(ZERO_X,	ZERO_Y, 	x, y, log_op); break;
		case '1': sr_draw_char_src_to_dst(ONE_X,	ONE_Y, 		x, y, log_op); break;
		case '2': sr_draw_char_src_to_dst(TWO_X,	TWO_Y, 		x, y, log_op); break;
		case '3': sr_draw_char_src_to_dst(THREE_X,	THREE_Y, 	x, y, log_op); break;
		case '4': sr_draw_char_src_to_dst(FOUR_X,	FOUR_Y, 	x, y, log_op); break;
		case '5': sr_draw_char_src_to_dst(FIVE_X,	FIVE_Y, 	x, y, log_op); break;
		case '6': sr_draw_char_src_to_dst(SIX_X,	SIX_Y, 		x, y, log_op); break;
		case '7': sr_draw_char_src_to_dst(SEVEN_X,	SEVEN_Y, 	x, y, log_op); break;
		case '8': sr_draw_char_src_to_dst(EIGHT_X,	EIGHT_Y,	x, y, log_op); break;
		case '9': sr_draw_char_src_to_dst(NINE_X,	NINE_Y, 	x, y, log_op); break;

		case '.': sr_draw_char_src_to_dst(DOT_X,		DOT_Y, 		x, y, log_op); break;
		case ',': sr_draw_char_src_to_dst(COMMA_X,		COMMA_Y, 	x, y, log_op); break;
		case ' ': sr_draw_char_src_to_dst(SPACE_X, 		SPACE_Y, 	x, y, log_op); break;
		case '^': sr_draw_char_src_to_dst(HEART_X, 		HEART_Y, 	x, y, log_op); break;
		case '@': sr_draw_char_src_to_dst(COPY_X,		COPY_Y, 	x, y, log_op); break;
		case '*': sr_draw_char_src_to_dst(ASTERISK_X,	ASTERISK_Y,	x, y, log_op); break;
		case '!': sr_draw_char_src_to_dst(EXCLA_X,		EXCLA_Y,	x, y, log_op); break;
		case '+': sr_draw_char_src_to_dst(PLUS_X,		PLUS_Y, 	x, y, log_op); break;
		case '-': sr_draw_char_src_to_dst(MINUS_X,		MINUS_Y, 	x, y, log_op); break;
		case '/': sr_draw_char_src_to_dst(SLASH_X,		SLASH_Y, 	x, y, log_op); break;
		case ':': sr_draw_char_src_to_dst(COLON_X, 		COLON_Y, 	x, y, log_op); break;

		case '<': sr_draw_char_src_to_dst(TXTBOX_UP_L_X,	TXTBOX_UP_L_Y, 	x, y, log_op); break;
		case '[': sr_draw_char_src_to_dst(TXTBOX_DWN_L_X,	TXTBOX_DWN_L_Y,	x, y, log_op); break;
		case '_': sr_draw_char_src_to_dst(TXTBOX_MID_X,		TXTBOX_MID_Y, 	x, y, log_op); break;
		case '>': sr_draw_char_src_to_dst(TXTBOX_UP_R_X, 	TXTBOX_UP_R_Y, 	x, y, log_op); break;
		case ']': sr_draw_char_src_to_dst(TXTBOX_DWN_R_X,	TXTBOX_DWN_R_Y,	x, y, log_op); break;
		case '|': sr_draw_char_src_to_dst(TXTBOX_LAT_X,		TXTBOX_LAT_Y, 	x, y, log_op); break;

		case '~': sr_draw_char_src_to_dst(CURSOR_X, CURSOR_Y, x, y, log_op); break;
	}
}

void sr_draw_text(uchar *text, uint x, uint y, uchar text_color, uchar border_color)
{
	uchar log_op = LOGICAL_IMP;

	while (*text)
	{
		if (border_color != 0)
		{
			// Color border.
			LMMV(x, y + sr_get_active_page() * PAGE_HEIGHT, FONT_SIZE, FONT_SIZE, border_color, LOGICAL_IMP);
			sr_draw_char(*text, x, y, LOGICAL_TIMP);

			// Only for color text.
			if (text_color != 0)
			{
				LMMV(x, y + sr_get_active_page() * PAGE_HEIGHT, FONT_SIZE, FONT_SIZE, 15 - text_color, LOGICAL_IMP);
				sr_draw_char(*text, x, y, LOGICAL_XOR);
				sr_draw_char(*text, x, y, LOGICAL_AND);
			}
		}
		else
		{
			// Transparent border.
			sr_draw_char(*text, x, y, LOGICAL_IMP);

			// Only for color text.
			if (text_color != 0)
			{
				LMMV(x, y + sr_get_active_page() * PAGE_HEIGHT, FONT_SIZE, FONT_SIZE, 15 - text_color, LOGICAL_IMP);
				sr_draw_char(*text, x, y, LOGICAL_XOR);
				sr_draw_char(*text, x, y, LOGICAL_AND);
			}
		}

		text++;
		x += FONT_SIZE;
	}
}
