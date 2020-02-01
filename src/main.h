//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef MAIN_H
#define MAIN_H

//------------------------------------------------------------------
// Typedefs.
//------------------------------------------------------------------

typedef unsigned int uint;

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define FALSE 0
#define TRUE 1

#define BUFFER_SIZE 4608

#define FONT_BUFFER_SIZE 2048

//------------------------------------------------------------------
// Enums.
//------------------------------------------------------------------

enum DoubleBufferState
{
	Updating,
	ReadyToSwitch,
	Finished
};

enum GameState
{
	None,
	StartScreen,
	Dungeon
};

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

extern char back_page;

extern enum DoubleBufferState db_state;

extern enum GameState game_state;

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sf_screen_copy(uint x1, uint y1, uint dx, uint dy, uint x2, uint y2, uint src_pg, uint dst_pg, char mode);
void sf_wait(int cicles);
void sf_set_game_state(char new_state);

void sf_init_song(void);
void sf_play_song(void);

// Debug.

void sf_draw_palette(void);

#endif
