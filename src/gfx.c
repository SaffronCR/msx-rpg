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
#include "system.h"
#include "ingame.h"
#include "gfx.h"

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define BUFFER_SIZE 2048

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

// Palette
//  0 Black
//  1 Dark Brown
//  2 Dark Blue
//  3 Dark Gray
//  4 Light Brown
//  5 Dark Green
//  6 Salmon
//  7 Medium Gray
//  8 Light Blue
//  9 Dark Orange
// 10 Light Gray
// 11 Light Green
// 12 Light Orange
// 13 Yellow
// 14 Dark Purple
// 15 Broken White

const uchar palette[] =
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

uchar active_page;

uchar display_page;

uchar load_buffer[BUFFER_SIZE];

enum ScreenHeight current_screen_height;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

void sr_set_active_page(uchar page)
{
	active_page = page;

	SetActivePage(active_page);
}

uint sr_get_active_page(void)
{
	return active_page;
}

void sr_set_display_page(uchar page)
{
	display_page = page;

	SetDisplayPage(page);
}

uint sr_get_display_page(void)
{
	return display_page;
}

void sr_init_palette(void)
{
	SetSC5Palette((Palette *)palette);
}

bool sr_load_sf5_image(uchar *file_name, uint initial_y_pos)
{
	uint read = BUFFER_SIZE;
	uint read_y_length = 0;

	sr_set_name(&file, file_name);

	if (fcb_open(&file) != FCB_SUCCESS)
	{
		sr_error_handler(1, file_name);
		return (false);
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
			read_y_length = read / PAGE_WIDTH_HALF;

			SetColors(0, 0, 0);

			// Move buffer to VRAM.
			HMMC(load_buffer, 0, initial_y_pos, PAGE_WIDTH, read_y_length);

			initial_y_pos = initial_y_pos + read_y_length;
		}
	}

	// Check for errors.
	if (fcb_close(&file) != FCB_SUCCESS)
	{
		sr_error_handler(2, file_name);
		return (false);
	}

	return (true);
}

bool sr_load_sc8_image(uchar *file_name, uint initial_y_pos)
{
	uint read = BUFFER_SIZE;
	uint read_y_length = 0;

	sr_set_name(&file, file_name);

	if (fcb_open(&file) != FCB_SUCCESS)
	{
		sr_error_handler(1, file_name);
		return (false);
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
			read_y_length = read / PAGE_WIDTH;

			// Move buffer to VRAM.
			HMMC(load_buffer, 0, initial_y_pos, PAGE_WIDTH, read_y_length);

			// Update initial Y position.
			initial_y_pos = initial_y_pos + read_y_length;
		}
	}

	// Check for errors.
	if (fcb_close(&file) != FCB_SUCCESS)
	{
		sr_error_handler(2, file_name);
		return (false);
	}

	return (true);
}

// Helper: Copy a page zone to another page using YMMM (high-speed transfer between VRAM in Y direction).
void sr_page_copy_y_fast(uint src_x, uint src_y, uint dst_y, uint height, char dir)
{
	YMMM(src_x, src_y, dst_y, height, dir);
}

// Helper: Copy a page zone to another page using HMMM (High Speed Move VRAM to VRAM).
void sr_page_copy_fast(uint src_x, uint src_y, uint width, uint height, uint dst_x, uint dst_y, uint src_pg, uint dst_pg)
{
	sr_page_copy_mode(src_x, src_y, width, height, dst_x, dst_y, src_pg, dst_pg, opHMMM);
}

// Helper: Copy a page zone to another page.
void sr_page_copy(uint src_x, uint src_y, uint width, uint height, uint dst_x, uint dst_y, uint src_pg, uint dst_pg)
{
	sr_page_copy_mode(src_x, src_y, width, height, dst_x, dst_y, src_pg, dst_pg, 0);
}

// Helper: Copy a page zone to another page using transparency (if SC>0 then IMP).
void sr_page_copy_trans(uint src_x, uint src_y, uint width, uint height, uint dst_x, uint dst_y, uint src_pg, uint dst_pg)
{
	sr_page_copy_mode(src_x, src_y, width, height, dst_x, dst_y, src_pg, dst_pg, LOGICAL_TIMP);
}

// Copy a page zone to another page.
void sr_page_copy_mode(uint src_x, uint src_y, uint width, uint height, uint dst_x, uint dst_y, uint src_pg, uint dst_pg, uchar mode)
{
	t.X = src_x;
	t.Y = src_y + src_pg * PAGE_HEIGHT;

	t.X2 = dst_x;
	t.Y2 = dst_y + dst_pg * PAGE_HEIGHT;

	t.DX = width;
	t.DY = height;

	t.s0 = 0;
	t.DI = 0;
	t.LOP = mode;

	fLMMM(&t);
}

void sr_draw_rectangle(uint x, uint y, uint width, uint height, char color)
{
	LMMV(x, y, width, height, color, 0);
}

void sr_draw_pixel(uint x, uint y, char color)
{
	Pset(x, y, color, 0);
}

void sr_debug_draw_palette(void)
{
	uint x = 0;
	uint y = 0;

	for (uint i = 0; i < 16; i++)
	{
		LMMV(x, y + sr_get_active_page() * PAGE_WIDTH, 8, 8, i, 0);
		y += 9;
	}
}

void sr_set_drawing_state(uchar new_state)
{
	drawing_state = new_state;
}

uchar sr_get_drawing_state(void)
{
	return drawing_state;
}

void sr_set_screen_height(uchar height)
{
	if (height != current_screen_height)
	{
		VDPLinesSwitch();
		height = current_screen_height;
	}
}

bool sr_is_vdp_ready(void)
{
	return ((VDPstatusNi(2) & 0x1) == false);
}

void sr_init_gfx(void)
{
	// Set variables.
	current_screen_height = SH_212;

	// Sets display to SCREEN 5 mode resolution 256 pixels x 212 lines x 16 colors.
	Screen(5);
	sr_set_screen_height(current_screen_height);

	// Disable hardware sprites.
	SpriteOff();

	// Switches the MSX2 VDP to 60 Hz (it's best to develop/optimize for 60Hz than 50Hz).
	VDP60Hz();

	// Set loading text.
	sr_set_active_page(0);
	sr_set_display_page(0);
	SetColors(15, 0, 0);
	PutText(5, 5, "LOADING...", LOGICAL_TIMP);

	// Load images.
	sr_init_palette();
	sr_load_sf5_image("P1.SF5", PAGE_HEIGHT * BACKBUFFER_PAGE);
	sr_load_sf5_image("P2.SF5", PAGE_HEIGHT * SPRITES_PAGE);
	sr_load_sf5_image("P3.SF5", PAGE_HEIGHT * WALLS_PAGE);

	// Reset current screen.
	Cls();

	// Initialize drawing state and pages.
	sr_set_drawing_state(READY);
}

bool sr_update_gfx(void)
{
	// Checking game is not drawing and VDP is not busy and vsync.
	// https://www.msx.org/wiki/VDP_Status_Registers
	if (sr_get_drawing_state() != END || sr_is_vdp_ready() == false || IsVsync() == 0)
	{
		return (false);
	}

	return (true);
}
