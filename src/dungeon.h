//------------------------------------------------------------------
// Star Rangers - A Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#ifndef DUNGEON_H
#define DUNGEON_H

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define DUNGEON_SIZE 22

#define SPRITES_PAGE 2
#define WALLS_PAGE 3

#define DUNGEON_SCREEN_X 24
#define DUNGEON_SCREEN_Y 16
#define DUNGEON_SCREEN_DX 160
#define DUNGEON_SCREEN_DY 120

#define FIRST_WALL_LEFT_X 13
#define FIRST_WALL_LEFT_Y 58
#define FIRST_WALL_RIGHT_X 55
#define FIRST_WALL_RIGHT_Y 58
#define FIRST_WALL_DX 42
#define FIRST_WALL_DY 120

#define SECOND_WALL_FAR_LEFT_X 0
#define SECOND_WALL_FAR_LEFT_Y 58
#define SECOND_WALL_FAR_RIGHT_X 0
#define SECOND_WALL_FAR_RIGHT_Y 126
#define SECOND_WALL_FAR_DX 13
#define SECOND_WALL_FAR_DY 68

#define SECOND_WALL_LEFT_X 97
#define SECOND_WALL_LEFT_Y 96
#define SECOND_WALL_RIGHT_X 155
#define SECOND_WALL_RIGHT_Y 96
#define SECOND_WALL_DX 58
#define SECOND_WALL_DY 96

#define SECOND_FRONT_WALL_X 158
#define SECOND_FRONT_WALL_Y 0
#define SECOND_FRONT_WALL_DX 78
#define SECOND_FRONT_WALL_DY 96

#define THIRD_WALL_FAR_LEFT_X 0
#define THIRD_WALL_FAR_LEFT_Y 0
#define THIRD_WALL_FAR_RIGHT_X 28
#define THIRD_WALL_FAR_RIGHT_Y 0
#define THIRD_WALL_FAR_DX 28
#define THIRD_WALL_FAR_DY 58

#define THIRD_WALL_LEFT_X 56
#define THIRD_WALL_LEFT_Y 0
#define THIRD_WALL_RIGHT_X 107
#define THIRD_WALL_RIGHT_Y 0
#define THIRD_WALL_DX 51
#define THIRD_WALL_DY 58
#define THIRD_WALL_OFFSET_X 12

#define THIRD_FRONT_WALL_X 112
#define THIRD_FRONT_WALL_Y 0
#define THIRD_FRONT_WALL_DX 46
#define THIRD_FRONT_WALL_DY 58

#define TILE_WALL 0
#define TILE_ROOM 1
#define TILE_CORRIDOR 2
#define TILE_CHEST 3
#define TILE_STAIRS_UP 4
#define TILE_STAIRS_DOWN 5

//------------------------------------------------------------------
// Enums.
//------------------------------------------------------------------

enum Directions
{
	North,
	East,
	South,
	West,
};

//------------------------------------------------------------------
// Variables.
//------------------------------------------------------------------

extern int player_pos_x;
extern int player_pos_y;

extern char *dungeon_map;

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sf_set_dungeon_state(void);
void sf_update_dungeon_state(void);

#endif
