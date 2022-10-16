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
#include "font.h"

// Lowercase.
#define lax		8
#define lay		196
#define lbx		16
#define lby		196
#define lcx		16+8
#define lcy		196
#define ldx		16+8+8
#define ldy		196
#define lex		16+8+8+8
#define ley		196
#define lfx		16+8+8+8+8
#define lfy		196
#define lgx		16+8+8+8+8+8
#define lgy		196
#define lhx		16+8+8+8+8+8+8
#define lhy		196
#define lix		16+8+8+8+8+8+8+8
#define liy		196
#define ljx		16+8+8+8+8+8+8+8+8
#define ljy		196
#define lkx		16+8+8+8+8+8+8+8+8+8
#define lky		196
#define llx		16+8+8+8+8+8+8+8+8+8+8
#define lly		196
#define lmx		16+8+8+8+8+8+8+8+8+8+8+8
#define lmy		196
#define lnx		16+8+8+8+8+8+8+8+8+8+8+8+8
#define lny		196
#define lox		16+8+8+8+8+8+8+8+8+8+8+8+8+8
#define loy		196
#define lpx		0
#define lpy		204
#define lqx		8
#define lqy		204
#define lrx		16
#define lry		204
#define lsx		16+8
#define lsy		204
#define ltx		16+8+8
#define lty		204
#define lux		16+8+8+8
#define luy		204
#define lvx		16+8+8+8+8
#define lvy		204
#define lwx		16+8+8+8+8+8
#define lwy		204
#define lxx		16+8+8+8+8+8+8
#define lxy		204
#define lyx		16+8+8+8+8+8+8+8
#define lyy		204
#define lzx		16+8+8+8+8+8+8+8+8
#define lzy		204

// Uppercase.
#define uax		8
#define uay		180
#define ubx		16
#define uby		180
#define ucx		16+8
#define ucy		180
#define udx		16+8+8
#define udy		180
#define uex		16+8+8+8
#define uey		180
#define ufx		16+8+8+8+8
#define ufy		180
#define ugx		16+8+8+8+8+8
#define ugy		180
#define uhx		16+8+8+8+8+8+8
#define uhy		180
#define uix		16+8+8+8+8+8+8+8
#define uiy		180
#define ujx		16+8+8+8+8+8+8+8+8
#define ujy		180
#define ukx		16+8+8+8+8+8+8+8+8+8
#define uky		180
#define ulx		16+8+8+8+8+8+8+8+8+8+8
#define uly		180
#define umx		16+8+8+8+8+8+8+8+8+8+8+8
#define umy		180
#define unx		16+8+8+8+8+8+8+8+8+8+8+8+8
#define uny		180
#define uox		16+8+8+8+8+8+8+8+8+8+8+8+8+8
#define uoy		180
#define upx		0
#define upy		188
#define uqx		8
#define uqy		188
#define urx		16
#define ury		188
#define usx		16+8
#define usy		188
#define utx		16+8+8
#define uty		188
#define uux		16+8+8+8
#define uuy		188
#define uvx		16+8+8+8+8
#define uvy		188
#define uwx		16+8+8+8+8+8
#define uwy		188
#define uxx		16+8+8+8+8+8+8
#define uxy		188
#define uyx		16+8+8+8+8+8+8+8
#define uyy		188
#define uzx		16+8+8+8+8+8+8+8+8
#define uzy		188

// Numbers.
#define zerox   0
#define zeroy   164
#define onex    8
#define oney    164
#define twox    16
#define twoy    164
#define threex  16+8
#define threey  164
#define fourx   16+8+8
#define foury   164
#define fivex   16+8+8+8
#define fivey   164
#define sixx    16+8+8+8+8
#define sixy    164
#define sevenx  16+8+8+8+8+8
#define seveny  164
#define eightx  16+8+8+8+8+8+8
#define eighty  164
#define ninex   16+8+8+8+8+8+8+8
#define niney   164

// Symbols.
#define dotx		16+8+8+8+8+8+8+8+8
#define doty   		164
#define commax		16+8+8+8+8+8+8+8+8+8
#define commay  	164
#define spacex  	16+8+8+8+8+8+8+8+8+8+8+8+8+8
#define spacey  	204
#define heartx		0
#define hearty		180
#define copyx		0
#define copyy		196
#define asteriskx	0+8+8+8+8+8+8
#define asterisky	172
#define exclax  	0+8+8+8
#define exclay  	172
#define plusx		0+8+8+8+8+8+8+8+8+8+8+8+8+8
#define plusy		172
#define minusx		0+8+8+8+8+8+8+8+8+8+8+8+8+8+8
#define minusy		172
#define slashx		0+8+8+8+8+8+8+8+8+8+8+8+8+8+8+8
#define slashy		172

// &#032; 	20 	  	&sp; 		space
// &#033; 	21 	! 	&excl; 		exclamation mark
// &#034; 	22 	" 	&quot; 		double quotation mark
// &#035; 	23 	# 	&num; 		number sign, pound
// &#036; 	24 	$ 	&dollar; 	dollar sign
// &#037; 	25 	% 	&percnt; 	percent sign
// &#038; 	26 	& 	&amp; 		ampersand
// &#039; 	27 	' 	&apos; 		apostrophe, single quote mark
// &#040; 	28 	( 	&lpar; 		left parenthesis
// &#041; 	29 	) 	&rpar; 		right parenthesis
// &#042; 	2A 	* 	&ast; 		asterisk
// &#043; 	2B 	+ 	&plus; 		plus sign
// &#044; 	2C 	, 	&comma; 	comma
// &#045; 	2D 	- 	&minus;   &hyphen; 	minus sign, hyphen
// &#046; 	2E 	. 	&period; 	period, decimal point, full stop
// &#047; 	2F 	/ 	&sol; 		slash, virgule, solidus
// &#058; 	3A 	: 	&colon; 	colon
// &#059; 	3B 	; 	&semi; 		semicolon
// &#060; 	3C 	< 	&lt; 		less-than sign
// &#061; 	3D 	= 	&equals; 	equal sign
// &#062; 	3E 	> 	&gt; 		greater-than sign
// &#063; 	3F 	? 	&quest; 	question mark
// &#064; 	40 	@ 	&commat; 	commercial at sign
// &#091; 	5B 	[ 	&lsqb; 		left square bracket
// &#092; 	5C 	\ 	&bsol; 		backslash, reverse solidus
// &#093; 	5D 	] 	&rsqb; 		right square bracket
// &#094; 	5E 	^ 	&circ; 		spacing circumflex accent
// &#095; 	5F 	_ 	&lowbar;   &horbar; 	spacing underscore, low line, horizontal bar
// &#096; 	60 	` 	&grave; 	spacing grave accent, back apostrophe
// &#123; 	7B 	{ 	&lcub; 		left brace, left curly bracket
// &#124; 	7C 	| 	&verbar; 	vertical bar
// &#125; 	7D 	} 	&rcub; 		right brace, right curly bracket
// &#126; 	7E 	~ 	&tilde; 	tilde accent
// &#169; 	A9 	© 	&copy; 		copyright sign

// Textbox
#define uplbx 16+8+8+8+8+8+8+8+8+8
#define uplby 204
#define uprbx 16+8+8+8+8+8+8+8+8+8+8+8
#define uprby 204
#define dwnlbx 16+8+8+8+8+8+8+8+8+8+8+8
#define dwnlby 188
#define dwnrbx 16+8+8+8+8+8+8+8+8+8+8+8+8
#define dwnrby 188
#define midbx 16+8+8+8+8+8+8+8+8+8+8
#define midby 204
#define latbx 16+8+8+8+8+8+8+8+8+8+8+8+8
#define latby 204

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_draw_char(uchar character, uint x, uint y, uchar log_op)
{
	switch (character)
	{
		case 'a': sr_screen_copy(lax,lay, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'b': sr_screen_copy(lbx,lby, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'c': sr_screen_copy(lcx,lcy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'd': sr_screen_copy(ldx,ldy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'e': sr_screen_copy(lex,ley, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'f': sr_screen_copy(lfx,lfy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'g': sr_screen_copy(lgx,lgy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'h': sr_screen_copy(lhx,lhy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'i': sr_screen_copy(lix,liy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'j': sr_screen_copy(ljx,ljy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'k': sr_screen_copy(lkx,lky, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'l': sr_screen_copy(llx,lly, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'm': sr_screen_copy(lmx,lmy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'n': sr_screen_copy(lnx,lny, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'o': sr_screen_copy(lox,loy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'p': sr_screen_copy(lpx,lpy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'q': sr_screen_copy(lqx,lqy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'r': sr_screen_copy(lrx,lry, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 's': sr_screen_copy(lsx,lsy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 't': sr_screen_copy(ltx,lty, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'u': sr_screen_copy(lux,luy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'v': sr_screen_copy(lvx,lvy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'w': sr_screen_copy(lwx,lwy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'x': sr_screen_copy(lxx,lxy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'y': sr_screen_copy(lyx,lyy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'z': sr_screen_copy(lzx,lzy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;

		case 'A': sr_screen_copy(uax,uay, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'B': sr_screen_copy(ubx,uby, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'C': sr_screen_copy(ucx,ucy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'D': sr_screen_copy(udx,udy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'E': sr_screen_copy(uex,uey, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'F': sr_screen_copy(ufx,ufy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'G': sr_screen_copy(ugx,ugy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'H': sr_screen_copy(uhx,uhy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'I': sr_screen_copy(uix,uiy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'J': sr_screen_copy(ujx,ujy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'K': sr_screen_copy(ukx,uky, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'L': sr_screen_copy(ulx,uly, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'M': sr_screen_copy(umx,umy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'N': sr_screen_copy(unx,uny, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'O': sr_screen_copy(uox,uoy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'P': sr_screen_copy(upx,upy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'Q': sr_screen_copy(uqx,uqy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'R': sr_screen_copy(urx,ury, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'S': sr_screen_copy(usx,usy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'T': sr_screen_copy(utx,uty, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'U': sr_screen_copy(uux,uuy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'V': sr_screen_copy(uvx,uvy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'W': sr_screen_copy(uwx,uwy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'X': sr_screen_copy(uxx,uxy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'Y': sr_screen_copy(uyx,uyy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case 'Z': sr_screen_copy(uzx,uzy, FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;

		case '0': sr_screen_copy(zerox,zeroy,	FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '1': sr_screen_copy(onex,oney,		FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '2': sr_screen_copy(twox,twoy,		FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '3': sr_screen_copy(threex,threey,	FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '4': sr_screen_copy(fourx,foury,	FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '5': sr_screen_copy(fivex,fivey,	FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '6': sr_screen_copy(sixx,sixy,		FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '7': sr_screen_copy(sevenx,seveny,	FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '8': sr_screen_copy(eightx,eighty,	FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '9': sr_screen_copy(ninex,niney,	FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;

		case '.': sr_screen_copy(dotx,doty,				FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case ',': sr_screen_copy(commax,commay,			FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case ' ': sr_screen_copy(spacex,spacey,			FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '!': sr_screen_copy(exclax,exclay,			FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '^': sr_screen_copy(heartx,hearty,			FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '@': sr_screen_copy(copyx,copyy,			FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '*': sr_screen_copy(asteriskx,asterisky, 	FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '+': sr_screen_copy(plusx,plusy,			FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '-': sr_screen_copy(minusx,minusy,			FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '/': sr_screen_copy(slashx,slashy,			FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '<': sr_screen_copy(uplbx,uplby,			FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '[': sr_screen_copy(dwnlbx,dwnlby,			FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '_': sr_screen_copy(midbx,midby,			FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '>': sr_screen_copy(uprbx,uprby,			FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case ']': sr_screen_copy(dwnrbx,dwnrby,			FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
		case '|': sr_screen_copy(latbx,latby,			FONT_SIZE,FONT_SIZE, x,y, FONT_PAGE, active_page, log_op); break;
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
			LMMV(x, y + active_page * 256, FONT_SIZE, FONT_SIZE, border_color, LOGICAL_IMP);
			sr_draw_char(*text, x, y, LOGICAL_TIMP);

			// Only for color text.
			if (text_color != 0)
			{
				LMMV(x, y + active_page * 256, FONT_SIZE, FONT_SIZE, 15-text_color, LOGICAL_IMP);
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
				LMMV(x, y + active_page * 256, FONT_SIZE, FONT_SIZE, 15-text_color, LOGICAL_IMP);
				sr_draw_char(*text, x, y, LOGICAL_XOR);
				sr_draw_char(*text, x, y, LOGICAL_AND);
			}
		}

		text++;
		x += FONT_SIZE;
	}
}
