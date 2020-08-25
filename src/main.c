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
#include "intro.h"
#include "font.h"
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

char active_page;

enum DrawingState drawing_state;

enum GameState game_state;

MMMtask t;

char load_buffer[BUFFER_SIZE];

char is_playing_song;

char update_frame_count = 0;

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
		LMMV(x, y + active_page * 256, 8, 8, i, 0);
		y += 9;
	}
}

void sf_wait(int cicles)
{
	for (int i = 0; i < cicles; i++)
	{
		__asm halt __endasm;
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

void sf_set_game_state(char new_state)
{
	game_state = new_state;

	switch(game_state)
	{
		case StartScreen:	sf_set_startscreen_state();	break;
		case Intro:			sf_set_intro_state();		break;
		case Dungeon:		sf_set_dungeon_state();		break;
	}
}

void sf_update_game_state()
{
	// Player input must wait until the next frame is ready.
	if (sf_get_drawing_state() == Finished)
	{
		switch (game_state)
		{
			case StartScreen:	sf_update_startscreen_state();	break;
			case Intro:			sf_update_intro_state();		break;
			case Dungeon:		sf_update_dungeon_state();		break;
		}
	}
}

static char sf_interrupt(void)
{
	// Update game logic and audio in separate frames to ease the CPU load.
	update_frame_count = !update_frame_count;
	if (update_frame_count == 1)
	{
		// Update game logic.
		sf_update_game_state();
	}
	else
	{
		// Update audio.
		if (is_playing_song == TRUE)
		{
			sf_play_song();
		}
	}

	// Checking "is ready to switch", VDP is not busy and vsync (https://www.msx.org/wiki/VDP_Status_Registers).
	if (sf_get_drawing_state() != WaitingForVDP || VDPstatusNi(2) & 0x1 || IsVsync() == 0)
	{
		return (FALSE);
	}

	// Update video.
	sf_switch_screen();

	return (TRUE);
}

void main(void)
{
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
	//sf_load_sf5_image("STRTSCR.SF5", 256 * 0, load_buffer);
	//sf_load_sf5_image("INTRO01.SF5", 256 * 0, load_buffer);

	// Init sound.
	sf_init_battle_song();
	is_playing_song = TRUE;

	// Set interrupt.
	InitInterruptHandler();
	SetInterruptHandler(sf_interrupt);

	// Set page configuration.
	sf_set_drawing_state(Finished);
	active_page = 0;
	SetDisplayPage(!active_page);
	SetActivePage(active_page);

	// Set initial game state.
	sf_set_game_state(Dungeon);

	for (;;)
	{
		// Do nothing.
	}
}
