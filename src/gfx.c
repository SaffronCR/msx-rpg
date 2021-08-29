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

char sf_load_sf5_image(char *file_name, uint initial_y_pos)
{
	uint read = BUFFER_SIZE;
	uint read_y_length = 0;

	sf_set_name(&file, file_name);

	if (fcb_open(&file) != FCB_SUCCESS)
	{
		sf_error_handler(1, file_name);
		return (FALSE);
	}

	while (read != 0)
	{
		// Set border color based on a 'random' position from the load buffer.
		SetColors(15, 0, load_buffer[69]);

		// Read file and write to load buffer.
		read = fcb_read(&file, load_buffer, BUFFER_SIZE);

		if (read != 0)
		{
			// Why half? Screen 5 uses 4 bits per pixel, so 8 bits can store two pixels.
			read_y_length = read / SCREEN_WIDTH_HALF;

			SetColors(0, 0, 0);

			// Move buffer to VRAM.
			HMMC(load_buffer, 0, initial_y_pos, SCREEN_WIDTH, read_y_length);

			initial_y_pos = initial_y_pos + read_y_length;
		}
	}

	// Check for errors.
	if (fcb_close(&file) != FCB_SUCCESS)
	{
		sf_error_handler(2, file_name);
		return (FALSE);
	}

	return (TRUE);
}

char sf_load_sc8_image(char *file_name, uint initial_y_pos)
{
	uint read = BUFFER_SIZE;
	uint read_y_length = 0;

	sf_set_name(&file, file_name);

	if (fcb_open(&file) != FCB_SUCCESS)
	{
		sf_error_handler(1, file_name);
		return (FALSE);
	}

	// Skip 7 first bytes of the file.
	fcb_read(&file, load_buffer, 7);

	while (read != 0)
	{
		// Set border color based on a 'random' position from the load buffer.
		SetColors(15, 0, load_buffer[69]);

		// Read file and write to load buffer.
		read = fcb_read(&file, load_buffer, BUFFER_SIZE);

		if (read != 0)
		{
			// Get Y length.
			read_y_length = read / SCREEN_WIDTH;

			// Move buffer to VRAM.
			HMMC(load_buffer, 0, initial_y_pos, SCREEN_WIDTH, read_y_length);

			// Update initial Y position.
			initial_y_pos = initial_y_pos + read_y_length;
		}
	}

	// Check for errors.
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
	src_y += src_pg * SCREEN_WIDTH;

	// Add page offset.
	dst_y += dst_pg * SCREEN_WIDTH;

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
		LMMV(x, y + active_page * SCREEN_WIDTH, 8, 8, i, 0);
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

char sf_get_drawing_state(void)
{
	return drawing_state;
}

void sf_init_gfx(void)
{
	// Disable sprites (speed gain).
	SpriteOff();

	// Sets display to SCREEN 5 mode resolution 256 pixels x 212 lines x 16 colors.
	Screen(5);

	// Switch from 212 to 192 vertical lines (for speed gain).
	VDPLinesSwitch();

	// Switches the MSX2 VDP to 60 Hz (it's best to develop/optimize for 60Hz than 50Hz).
	VDP60Hz();

	// Set loading text.
	Cls();
	SetColors(15, 0, 0);
	PutText(5, 5, "LOADING...", LOGICAL_TIMP);

	// Load screens.
	sf_init_palette();
	sf_load_sf5_image("BG.SF5", SCREEN_WIDTH * SPRITES_PAGE);
	sf_load_sf5_image("WALLS.SF5", SCREEN_WIDTH * WALLS_PAGE);
	//sf_load_sf5_image("STRTSCR.SF5", SCREEN_WIDTH * 0);
	//sf_load_sf5_image("INTRO01.SF5", SCREEN_WIDTH * 0);

	// Configure pages.
	sf_set_drawing_state(Finished);
	active_page = 0;
	SetDisplayPage(!active_page);
	SetActivePage(active_page);
}

char sf_update_gfx(void)
{
	// Checking "is ready to switch", VDP is not busy and vsync (https://www.msx.org/wiki/VDP_Status_Registers).
	if (sf_get_drawing_state() != WaitingForVDP || VDPstatusNi(2) & 0x1 || IsVsync() == 0)
	{
		return (FALSE);
	}

	sf_switch_screen();

	return (TRUE);
}
