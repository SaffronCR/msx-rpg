//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef FONT_H
#define FONT_H

#include "main.h"

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define FONT_PAGE 2
#define FONT_SIZE 8

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sf_draw_text(uchar *text, uint x, uint y, uchar text_color, uchar border_color);

#endif
