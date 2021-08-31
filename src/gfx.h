//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef GFX_H
#define GFX_H

#include "types.h"

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define SCREEN_WIDTH 256
#define SCREEN_WIDTH_HALF 128

//------------------------------------------------------------------
// Enums.
//------------------------------------------------------------------

enum DrawingState
{
	Begin,
	WaitingForVDP,
	Finished
};

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

extern char active_page;

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sf_init_palette(void);
char sf_load_sf5_image(char *file_name, uint start_Y);
char sf_load_sc8_image(char *file_name, uint start_Y);
void sf_screen_copy(uint x1, uint y1, uint dx, uint dy, uint x2, uint y2, uint src_pg, uint dst_pg, char mode);
void sf_wait(int cicles);
void sf_set_drawing_state(char new_state);
char sf_get_drawing_state(void);
void sf_init_gfx(void);
char sf_update_gfx(void);

// Debug.

void sf_debug_draw_palette(void);

#endif
