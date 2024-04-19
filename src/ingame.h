//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef INGAME_H
#define INGAME_H

#include "main.h"
#include "fnt.h"

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define LEVEL_SIZE 24

#define BACKBUFFER_PAGE 1
#define IMAGES_PAGE 2
#define WALLS_PAGE 3

#define LEVEL_SCREEN_X 8
#define LEVEL_SCREEN_Y 8
#define LEVEL_SCREEN_SIZE_X 160
#define LEVEL_SCREEN_SIZE_Y 120

#define BG_SURFACE_CEILING_X 0
#define BG_SURFACE_CEILING_Y 0
#define BG_SURFACE_CEILING_SIZE_X LEVEL_SCREEN_SIZE_X
#define BG_SURFACE_CEILING_SIZE_Y 48

#define BG_UNDERGROUND_CEILING_X 0
#define BG_UNDERGROUND_CEILING_Y 77
#define BG_UNDERGROUND_CEILING_SIZE_X LEVEL_SCREEN_SIZE_X
#define BG_UNDERGROUND_CEILING_SIZE_Y 48

#define BG_FRONT_X LEVEL_SCREEN_X
#define BG_FRONT_Y 48 + BACKBUFFER_PAGE * PAGE_HEIGHT
#define BG_FRONT_SIZE_X LEVEL_SCREEN_SIZE_X
#define BG_FRONT_SIZE_Y 29
#define BG_FRONT_COLOR 14

#define BG_FLOOR_X 0
#define BG_FLOOR_Y 125
#define BG_FLOOR_SIZE_X LEVEL_SCREEN_SIZE_X
#define BG_FLOOR_SIZE_Y 43
#define BG_FLOOR_DST_X LEVEL_SCREEN_X
#define BG_FLOOR_DST_Y 77

#define BG_ALT_FLOOR_X 0
#define BG_ALT_FLOOR_Y 168
#define BG_ALT_FLOOR_SIZE_X LEVEL_SCREEN_SIZE_X

#define BG_ALT_FLOOR_SIZE_Y_1 21
#define BG_ALT_FLOOR_SIZE_Y_2 22

#define BG_ALT_FLOOR_DST_Y_1 BG_FLOOR_DST_Y
#define BG_ALT_FLOOR_DST_Y_2 98

#define LEVEL_VIEW_SIZE_X 5
#define LEVEL_VIEW_SIZE_Y 3

#define LEVEL_VIEW_DIST 2

#define COMPASS_COLOR 9
#define COMPASS_X LEVEL_SCREEN_X + (LEVEL_SCREEN_SIZE_X - LEVEL_SCREEN_X) / 2
#define COMPASS_Y 0

#define MENU_Y_SPACE 1
#define MENU_TEXT_DEFAULT_COLOR 0
#define MENU_TEXT_SELECT_COLOR 8
#define MENU_X LEVEL_SCREEN_X + 8
#define MENU_Y LEVEL_SCREEN_Y + LEVEL_SCREEN_SIZE_Y + FONT_SIZE
#define MENU_SIZE_X 160
#define MENU_SIZE_Y 45

#define PORTRAIT_SRC_X 160
#define PORTRAIT_SRC_Y 0
#define PORTRAIT_SIZE 32

#define PORTRAIT_NAME_COLOR 15
#define PORTRAIT_1_NAME_X 176
#define PORTRAIT_1_NAME_Y FONT_SIZE - 4
#define PORTRAIT_2_NAME_X 176
#define PORTRAIT_2_NAME_Y PORTRAIT_1_NAME_Y + PORTRAIT_SIZE + FONT_SIZE + 4
#define PORTRAIT_3_NAME_X 176
#define PORTRAIT_3_NAME_Y PORTRAIT_2_NAME_Y + PORTRAIT_SIZE + FONT_SIZE + 4
#define PORTRAIT_4_NAME_X 176
#define PORTRAIT_4_NAME_Y PORTRAIT_3_NAME_Y + PORTRAIT_SIZE + FONT_SIZE + 4

#define PORTRAIT_1_X PORTRAIT_1_NAME_X
#define PORTRAIT_1_Y PORTRAIT_1_NAME_Y + FONT_SIZE
#define PORTRAIT_2_X PORTRAIT_2_NAME_X
#define PORTRAIT_2_Y PORTRAIT_2_NAME_Y + FONT_SIZE
#define PORTRAIT_3_X PORTRAIT_3_NAME_X
#define PORTRAIT_3_Y PORTRAIT_3_NAME_Y + FONT_SIZE
#define PORTRAIT_4_X PORTRAIT_4_NAME_X
#define PORTRAIT_4_Y PORTRAIT_4_NAME_Y + FONT_SIZE

#define HP_BAR_SIZE_X 4
#define HP_BAR_SIZE_Y PORTRAIT_SIZE

#define HP_BAR_1_X PORTRAIT_1_X + PORTRAIT_SIZE + 2
#define HP_BAR_1_Y PORTRAIT_1_Y

#define HP_BAR_2_X PORTRAIT_2_X + PORTRAIT_SIZE + 2
#define HP_BAR_2_Y PORTRAIT_2_Y

#define HP_BAR_3_X PORTRAIT_3_X + PORTRAIT_SIZE + 2
#define HP_BAR_3_Y PORTRAIT_3_Y

#define FIRST_WALL_LEFT_X 13
#define FIRST_WALL_LEFT_Y 58
#define FIRST_WALL_RIGHT_X 55
#define FIRST_WALL_RIGHT_Y 58
#define FIRST_WALL_SIZE_X 42
#define FIRST_WALL_SIZE_Y 120

#define SECOND_WALL_FAR_LEFT_X 0
#define SECOND_WALL_FAR_LEFT_Y 58
#define SECOND_WALL_FAR_RIGHT_X 0
#define SECOND_WALL_FAR_RIGHT_Y 126
#define SECOND_WALL_FAR_SIZE_X 13
#define SECOND_WALL_FAR_SIZE_Y 68

#define SECOND_WALL_LEFT_X 97
#define SECOND_WALL_LEFT_Y 96
#define SECOND_WALL_RIGHT_X 155
#define SECOND_WALL_RIGHT_Y 96
#define SECOND_WALL_SIZE_X 58
#define SECOND_WALL_SIZE_Y 96

#define SECOND_FRONT_WALL_X 158
#define SECOND_FRONT_WALL_Y 0
#define SECOND_FRONT_WALL_SIZE_X 78
#define SECOND_FRONT_WALL_SIZE_Y 96

#define THIRD_WALL_FAR_LEFT_X 0
#define THIRD_WALL_FAR_LEFT_Y 0
#define THIRD_WALL_FAR_RIGHT_X 28
#define THIRD_WALL_FAR_RIGHT_Y 0
#define THIRD_WALL_FAR_SIZE_X 28
#define THIRD_WALL_FAR_SIZE_Y 58

#define THIRD_WALL_LEFT_X 56
#define THIRD_WALL_LEFT_Y 0
#define THIRD_WALL_RIGHT_X 107
#define THIRD_WALL_RIGHT_Y 0
#define THIRD_WALL_SIZE_X 51
#define THIRD_WALL_SIZE_Y 58
#define THIRD_WALL_OFFSET_X 12

#define THIRD_FRONT_WALL_X 112
#define THIRD_FRONT_WALL_Y 0
#define THIRD_FRONT_WALL_SIZE_X 46
#define THIRD_FRONT_WALL_SIZE_Y 58

#define TILE_WALL 0
#define TILE_ROOM 1
#define TILE_CORRIDOR 2
#define TILE_STAIRS 3
#define TILE_CHEST 4

//------------------------------------------------------------------
// Enums.
//------------------------------------------------------------------

enum Direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

extern uint player_pos_x;
extern uint player_pos_y;

extern uchar *level_map;

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sr_set_ingame_state(void);
void sr_update_ingame_state(void);
void sr_finished_ingame_drawing(void);

#endif
