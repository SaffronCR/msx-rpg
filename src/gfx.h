//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef GFX_H
#define GFX_H

#include "main.h"

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define PAGE_HEIGHT 256
#define PAGE_WIDTH 256

#define PAGE_WIDTH_HALF 128

#define HARDWARE_SPRITE_SIZE 8

#define PALETTE_SIZE 16

//------------------------------------------------------------------
// Enums.
//------------------------------------------------------------------

enum DrawingState
{
	DS_READY,
	DS_BEGIN,
	DS_END
};

enum ScreenHeight
{
	SH_192,
	SH_212
};

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sr_init_gfx(void);
bool sr_update_gfx(void);

void sr_set_active_page(uchar page);
uint sr_get_active_page(void);
void sr_set_display_page(uchar page);
uint sr_get_display_page(void);
void sr_init_palette(void);
bool sr_load_sf5_image(uchar *file_name, uint start_Y);
bool sr_load_sc8_image(uchar *file_name, uint start_Y);
void sr_page_copy_fast(uint x1, uint y1, uint dx, uint dy, uint x2, uint y2, uint src_pg, uint dst_pg);
void sr_page_copy_y_fast(uint src_x, uint src_y, uint dst_y, uint height, char dir);
void sr_page_copy(uint src_x, uint src_y, uint width, uint height, uint dst_x, uint dst_y, uint src_pg, uint dst_pg);
void sr_page_copy_trans(uint src_x, uint src_y, uint width, uint height, uint dst_x, uint dst_y, uint src_pg, uint dst_pg);
void sr_page_copy_mode(uint src_x, uint src_y, uint width, uint height, uint dst_x, uint dst_y, uint src_pg, uint dst_pg, uchar mode);
void sr_draw_rectangle(uint x, uint y, uint width, uint height, char color);
void sr_draw_pixel(uint x, uint y, char color);
void sr_wait(uint cicles);
void sr_set_drawing_state(uchar new_state);
uchar sr_get_drawing_state(void);
void sr_set_screen_height(uchar height);
bool sr_is_vdp_ready(void);

// Debug.

void sr_debug_draw_palette(void);

#endif
