//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_sprites.h"
#include "fusion-c/header/vdp_graph2.h"

#include "types.h"
#include "main.h"
#include "system.h"
#include "dungeon.h"
#include "gfx.h"

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define BUFFER_SIZE 4608

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

const char palette[] =
{
	0, 0, 0, 0,
	1, 2, 1, 1,
	2, 1, 1, 3,
	3, 2, 2, 2,
	4, 4, 2, 1,
	5, 1, 3, 1,
	6, 6, 2, 2,
	7, 3, 3, 3,
	8, 2, 3, 6,
	9, 6, 3, 1,
	10, 4, 4, 4,
	11, 3, 5, 1,
	12, 6, 5, 4,
	13, 6, 6, 3,
	14, 1, 0, 1,
	15, 6, 7, 6,
};

static FCB file;

enum DrawingState drawing_state;

MMMtask t;

char active_page;

char load_buffer[BUFFER_SIZE];

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sf_init_palette(void)
{
	SetSC5Palette((Palette *)palette);
}

char sf_load_sf5_image(char *file_name, uint start_Y)
{
	uint rd = BUFFER_SIZE;
	uint nbl = 0;

	sf_set_name(&file, file_name);

	if (fcb_open(&file) != FCB_SUCCESS)
	{
		sf_error_handler(1, file_name);
		return (FALSE);
	}

	while (rd != 0)
	{
		SetColors(15, 0, load_buffer[69]);

		rd = fcb_read(&file, load_buffer, BUFFER_SIZE);

		if (rd != 0)
		{
			// screen 5 (4 bits x 256 x 212).
			nbl = rd / 128;

			SetColors(0, 0, 0);

			// Move the buffer to VRAM.
			HMMC(load_buffer, 0, start_Y, 256, nbl);

			start_Y = start_Y + nbl;
		}
	}

	if (fcb_close(&file) != FCB_SUCCESS)
	{
		sf_error_handler(2, file_name);
		return (FALSE);
	}

	return (TRUE);
}

char sf_load_sc8_image(char *file_name, uint start_Y)
{
	uint rd = 2304;
	uint nbl = 0;

	sf_set_name(&file, file_name);

	if (fcb_open(&file) != FCB_SUCCESS)
	{
		sf_error_handler(1, file_name);
		return (FALSE);
	}

	// Skip 7 first bytes of the file.
	fcb_read(&file, load_buffer, 7);

	while (rd != 0)
	{
		SetColors(15, 0, load_buffer[192]);
		rd = fcb_read(&file, load_buffer, 2304);

		if (rd != 0)
		{
			nbl = rd / 256;

			// Move the buffer to VRAM. 17 lines x 256 pixels from memory.
			HMMC(load_buffer, 0, start_Y, 256, nbl);

			start_Y = start_Y + nbl;
		}
	}

	if (fcb_close(&file) != FCB_SUCCESS)
	{
		sf_error_handler(2, file_name);
		return (FALSE);
	}

	return (TRUE);
}

//  Copy a screen zone to another place
//  x1 & y1 =Top left coordonate  pixel of the zone to copy
//  dx = Width Size in pixels, of the zone to copy
//  dy = Height Size in pixels, of the zone to copy
//  x2 & y2 = Destination coordonate where to copy the zone
//  src_pg = Source Page number of the Zone
//  dst_pg = Destination number of the zone
//  mode = OP mode of the copy
void sf_screen_copy(uint x1, uint y1, uint dx, uint dy, uint x2, uint y2, uint src_pg, uint dst_pg, char mode)
{
	uint src_y = 0;
	uint dst_y = 0;

	// Add page offset.
	src_y += src_pg * 256;

	// Add page offset.
	dst_y += dst_pg * 256;

	t.X = x1;
	t.Y = src_y + y1;

	t.X2 = x2;
	t.Y2 = dst_y + y2;

	t.DX = dx;
	t.DY = dy;

	t.s0 = 0;
	t.DI = 0;
	t.LOP = mode;

	fLMMM(&t);
}

void sf_draw_palette(void)
{
	int x = 0;
	int y = 0;

	for (int i = 0; i < 16; i++)
	{
		LMMV(x, y + active_page * 256, 8, 8, i, 0);
		y += 9;
	}
}

void sf_switch_screen(void)
{
	if (sf_get_drawing_state() == WaitingForVDP)
	{
		active_page = !active_page;

		SetDisplayPage(!active_page);
		SetActivePage(active_page);

		sf_set_drawing_state(Finished);
	}
}

void sf_set_drawing_state(char new_state)
{
	drawing_state = new_state;
}

char sf_get_drawing_state()
{
	return drawing_state;
}

void sf_init_gfx()
{
	// Disable sprites.
	SpriteOff();

	// Sets display to specified screen mode (from 0 to 8).
	Screen(5);

	// Switches the MSX2 VDP to 50 Hz Pal Mode.
	VDP50Hz();

	// Set loading text.
	Cls();
	SetColors(15, 0, 0);
	PutText(5, 5, "LOADING...", LOGICAL_TIMP);

	// Load screens.
	sf_init_palette();
	sf_load_sf5_image("BG.SF5", 256 * SPRITES_PAGE);
	sf_load_sf5_image("WALLS.SF5", 256 * WALLS_PAGE);
	//sf_load_sf5_image("STRTSCR.SF5", 256 * 0);
	//sf_load_sf5_image("INTRO01.SF5", 256 * 0);

	// Configure pages.
	sf_set_drawing_state(Finished);
	active_page = 0;
	SetDisplayPage(!active_page);
	SetActivePage(active_page);
}
