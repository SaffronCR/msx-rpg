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
#include "startscreen.h"

// Font.

#define FONT_PAGE 2
#define FONT_SIZE_X 8
#define FONT_SIZE_Y 8

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
#define spacex  16+8+8+8+8+8+8+8+8+8+8+8+8+8
#define spacey  204
#define heartx	0
#define hearty	180
#define copyx	0
#define copyy	196
#define exclax  0+8+8+8
#define exclay  172

void sf_draw_char(char character, int x, int y, char log_op)
{
    switch (character)
    {
        case 'a': sf_screen_copy(lax,lay, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'b': sf_screen_copy(lbx,lby, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'c': sf_screen_copy(lcx,lcy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'd': sf_screen_copy(ldx,ldy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'e': sf_screen_copy(lex,ley, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'f': sf_screen_copy(lfx,lfy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'g': sf_screen_copy(lgx,lgy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'h': sf_screen_copy(lhx,lhy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'i': sf_screen_copy(lix,liy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'j': sf_screen_copy(ljx,ljy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'k': sf_screen_copy(lkx,lky, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'l': sf_screen_copy(llx,lly, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'm': sf_screen_copy(lmx,lmy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'n': sf_screen_copy(lnx,lny, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'o': sf_screen_copy(lox,loy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'p': sf_screen_copy(lpx,lpy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'q': sf_screen_copy(lqx,lqy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'r': sf_screen_copy(lrx,lry, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 's': sf_screen_copy(lsx,lsy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 't': sf_screen_copy(ltx,lty, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'u': sf_screen_copy(lux,luy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'v': sf_screen_copy(lvx,lvy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'w': sf_screen_copy(lwx,lwy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'x': sf_screen_copy(lxx,lxy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'y': sf_screen_copy(lyx,lyy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'z': sf_screen_copy(lzx,lzy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;

        case 'A': sf_screen_copy(uax,uay, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'B': sf_screen_copy(ubx,uby, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'C': sf_screen_copy(ucx,ucy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'D': sf_screen_copy(udx,udy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'E': sf_screen_copy(uex,uey, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'F': sf_screen_copy(ufx,ufy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'G': sf_screen_copy(ugx,ugy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'H': sf_screen_copy(uhx,uhy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'I': sf_screen_copy(uix,uiy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'J': sf_screen_copy(ujx,ujy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'K': sf_screen_copy(ukx,uky, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'L': sf_screen_copy(ulx,uly, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'M': sf_screen_copy(umx,umy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'N': sf_screen_copy(unx,uny, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'O': sf_screen_copy(uox,uoy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'P': sf_screen_copy(upx,upy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'Q': sf_screen_copy(uqx,uqy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'R': sf_screen_copy(urx,ury, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'S': sf_screen_copy(usx,usy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'T': sf_screen_copy(utx,uty, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'U': sf_screen_copy(uux,uuy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'V': sf_screen_copy(uvx,uvy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'W': sf_screen_copy(uwx,uwy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'X': sf_screen_copy(uxx,uxy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'Y': sf_screen_copy(uyx,uyy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case 'Z': sf_screen_copy(uzx,uzy, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;

        case '0': sf_screen_copy(zerox,zeroy,   FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case '1': sf_screen_copy(onex,oney,     FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case '2': sf_screen_copy(twox,twoy,     FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case '3': sf_screen_copy(threex,threey, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case '4': sf_screen_copy(fourx,foury,   FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case '5': sf_screen_copy(fivex,fivey,   FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case '6': sf_screen_copy(sixx,sixy,     FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case '7': sf_screen_copy(sevenx,seveny, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case '8': sf_screen_copy(eightx,eighty, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case '9': sf_screen_copy(ninex,niney,   FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;

        case ' ': sf_screen_copy(spacex,spacey, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case '!': sf_screen_copy(exclax,exclay, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case '^': sf_screen_copy(heartx,hearty, FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
        case '@': sf_screen_copy(copyx,copyy,   FONT_SIZE_X,FONT_SIZE_Y, x,y, FONT_PAGE, back_page, log_op); break;
    }
}

void sf_draw_text(char *text, int x, int y, char border_color, char text_color)
{
    char log_op = LOGICAL_IMP;

    while (*text)
    {
        if (border_color != 0)
        {
            // Color border, original color (white) text.
            LMMV(x, y, FONT_SIZE_X, FONT_SIZE_Y, 16-border_color, LOGICAL_IMP);
            sf_draw_char(*text, x, y, LOGICAL_TIMP);
        }
        else if (text_color == 0)
        {
            // Transparent border, original color (white) text.
            sf_draw_char(*text, x, y, LOGICAL_IMP);
        }
        else
        {
            // Transparent border, color text.
            LMMV(x, y, FONT_SIZE_X, FONT_SIZE_Y, 15-text_color, LOGICAL_IMP);
            sf_draw_char(*text, x, y, LOGICAL_XOR);
            sf_draw_char(*text, x, y, LOGICAL_AND);
        }

        text++;
        x += FONT_SIZE_X;
    }
}

void sf_draw_startscreen_intro_text(void)
{
	// Intro text.
    // db_state = Updating;
    // Cls();
	// SetColors(15, 0, 0);
    // db_state = ReadyToSwitch;
    // PutText(8*7, 100, "SAFFRON SOFT  2020", LOGICAL_IMP);

    // PutText(0, 90, "********************************", LOGICAL_IMP);

    // sf_wait(200);

	// Main menu text.
    db_state = Updating;
    Cls();

    sf_draw_palette();

    SetColors(0, 0, 0);

	// SetColors(8, 0, 0);
    // PutText(8*7, 100,       " 0123456789ABCDE", LOGICAL_IMP);
    // PutText(8*7, 100+9,     "FGHIJKLMNOPQRSTU", LOGICAL_IMP);
    // PutText(8*7, 100+9+9,   "VWXYZabcdefghijk", LOGICAL_IMP);
    // PutText(8*7, 100+9+9+9, "lmnopqrstuvwxyz.", LOGICAL_IMP);

    sf_draw_text("@SAFFRON SOFT 2020", 8*2, 25, 0, 2);

    sf_draw_text("0123456789 ! ^", 8*2, 50, 0, 4);
    sf_draw_text("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 8*2, 50+8+1, 0, 4);
    sf_draw_text("abcdefghijklmnopqrstuvwxyz", 8*2, 50+8+1+8+1, 0, 5);

    sf_draw_text("Damage              ", 8*2, 100, 8, 0);
    sf_draw_text("Attack              ", 8*2, 100+8+1, 0, 8);
    sf_draw_text("Evade               ", 8*2, 100+8+1+8+1, 0, 8);

    db_state = ReadyToSwitch;
}

void sf_set_startscreen_mode(void)
{
    sf_draw_startscreen_intro_text();
}

void sf_update_startscreen_mode(void)
{
}

