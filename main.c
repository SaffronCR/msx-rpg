//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_sprites.h"
#include "fusion-c/header/vdp_graph2.h"
#include "fusion-c/header/ayfx_player.h"
#include "fusion-c/header/pt3replayer.h"

#include "combat.h"
#include "dungeon.h"
#include "menu.h"
#include "procgen.h"
#include "startscreen.h"
#include "main.h"

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

static FCB file;

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

char back_page;

enum DoubleBufferState db_state;

MMMtask t;

char load_buffer[BUFFER_SIZE];

// Random seed, for debug purposes.
uint rand_seed = 666;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

// In case of Error.
void sf_error_handler(char n, char *name)
{
	InitPSG();
	Screen(0);
	SetColors(15, 6, 6);

	switch (n)
	{
	case 1:
		printf("\n\rFAILED: fcb_open(): %s ", name);
		break;

	case 2:
		printf("\n\rFAILED: fcb_close(): %s", name);
		break;

	case 3:
		printf("\n\rSORRY: this game does not work on %s", name);
		break;
	}

	Exit(0);
}

// Set the name of a file to load (MSX DOS).
void sf_set_name(FCB *p_fcb, const char *p_name)
{
	char i, j;
	memset(p_fcb, 0, sizeof(FCB));

	for (i = 0; i < 11; i++)
	{
		p_fcb->name[i] = ' ';
	}

	for (i = 0; (i < 8) && (p_name[i] != 0) && (p_name[i] != '.'); i++)
	{
		p_fcb->name[i] = p_name[i];
	}

	if (p_name[i] == '.')
	{
		i++;
		for (j = 0; (j < 3) && (p_name[i + j] != 0) && (p_name[i + j] != '.'); j++)
		{
			p_fcb->ext[j] = p_name[i + j];
		}
	}
}

char sf_load_sf5_image(char *file_name, uint start_Y, char *buffer)
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
		SetColors(15, 0, buffer[69]);

		rd = fcb_read(&file, buffer, BUFFER_SIZE);

		if (rd != 0)
		{
			// screen 5 (4 bits x 256 x 212).
			nbl = rd / 128;

			SetColors(0, 0, 0);

			// Move the buffer to VRAM.
			HMMC(buffer, 0, start_Y, 256, nbl);

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

// Loads a SC8 Picture and put data on screen, begining at start_Y line.
char sf_load_sc8_image(char *file_name, uint start_Y, char *buffer)
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
	fcb_read(&file, buffer, 7);

	while (rd != 0)
	{
		SetColors(15, 0, buffer[192]);
		rd = fcb_read(&file, buffer, 2304);

		if (rd != 0)
		{
			nbl = rd / 256;

			// Move the buffer to VRAM. 17 lines x 256 pixels from memory.
			HMMC(buffer, 0, start_Y, 256, nbl);

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
		Rect(x, y + back_page * 256, x + 7, y + 7 + back_page * 256, i, FILL_ALL);
		y += 9;
	}
}

void sf_wait(int cicles)
{
	for (int i=0; i <cicles; i++)
	{
		__asm halt; __endasm;
	}
}

void sf_blit_screen(void)
{
	if (db_state == ReadyToSwitch)
	{
		back_page = !back_page;

		SetDisplayPage(!back_page);
  		SetActivePage(back_page);

		db_state = Finished;
	}
}

static char sf_video_interrupt(void)
{
	// Checking is ready to switch, VDP is not busy and vsync (https://www.msx.org/wiki/VDP_Status_Registers).
	if (db_state != ReadyToSwitch || VDPstatusNi(2) & 0x1 || IsVsync() == 0)
	{
		return (FALSE);
	}

	sf_blit_screen();

	return (TRUE);
}

// Main.
void main(void)
{
	//unsigned int font_addr;

	// If MSX is Turbo-R Switch CPU to Z80 Mode.
	if(ReadMSXtype() == 3)
    {
		ChangeCPU(0);
    }

	// Init random.
	srand(rand_seed);

	// Disable key sound.
	KeySound(0);

	// Clears the key buffer.
	KillKeyBuffer();

	// Initialization of the PSG (Use this function before sending data to PSG).
	// All registers will be set to 0, and stops all noises and sounds.
	InitPSG();

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
	SetSC5Palette((Palette *)palette);
	sf_load_sf5_image("BG.SF5", 256 * SPRITES_PAGE, load_buffer);
	sf_load_sf5_image("WALLS.SF5", 256 * WALLS_PAGE, load_buffer);

	// Set interrupt.
	InitInterruptHandler();
	SetInterruptHandler(sf_video_interrupt);

	// Set page configuration.
	db_state = Finished;
	back_page = 0;
	SetDisplayPage(!back_page);
	SetActivePage(back_page);

	//#TODO check_game_mode
	//sf_set_startscreen_mode();
	sf_set_dungeon_mode();

	for (;;)
	{
		// Player input must wait until the next frame is ready.
		if (db_state == Finished)
		{
			//#TODO check_game_mode
			{
				// Dungeon mode.
				{
					sf_update_dungeon_mode();
				}
			}
		}
	}
}
