//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef GFX_H
#define GFX_H

#include "main.h"

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define SCREEN_HEIGHT 256
#define SCREEN_WIDTH 256
#define SCREEN_WIDTH_HALF 128

#define HARDWARE_SPRITE_SIZE 8

//------------------------------------------------------------------
// Enums.
//------------------------------------------------------------------

enum DrawingState
{
	READY,
	BEGIN,
	END
};

enum ScreenHeight
{
	SH_192,
	SH_212
};

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sr_set_active_page(uchar page);
uint sr_get_active_page(void);
void sr_set_display_page(uchar page);
uint sr_get_display_page(void);
void sr_init_palette(void);
bool sr_load_sf5_image(uchar *file_name, uint start_Y);
bool sr_load_sc8_image(uchar *file_name, uint start_Y);
void sr_page_copy_fast(uint x1, uint y1, uint dx, uint dy, uint x2, uint y2, uint src_pg, uint dst_pg);
void sr_page_copy_y_fast( int XS, int YS, int DY, int NY, char DiRX);
void sr_page_copy(uint x1, uint y1, uint dx, uint dy, uint x2, uint y2, uint src_pg, uint dst_pg);
void sr_page_copy_trans(uint x1, uint y1, uint dx, uint dy, uint x2, uint y2, uint src_pg, uint dst_pg);
void sr_page_copy_mode(uint x1, uint y1, uint dx, uint dy, uint x2, uint y2, uint src_pg, uint dst_pg, uchar mode);
void sr_draw_rectangle(int x, int y, int width, int height, char color);
void sr_draw_pixel(int x, int y, char color);
void sr_wait(uint cicles);
void sr_set_drawing_state(uchar new_state);
uchar sr_get_drawing_state(void);
void sr_set_screen_height(uchar height);
bool sr_is_vdp_ready(void);
void sr_init_gfx(void);
bool sr_update_gfx(void);

// Debug.

void sr_debug_draw_palette(void);

#endif
