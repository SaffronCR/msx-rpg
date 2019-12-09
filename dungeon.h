#ifndef DUNGEON_H
#define DUNGEON_H

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define SPRITES_PAGE 2
#define WALLS_PAGE 3

#define DUNGEON_SIZE 16

#define DUNGEON_SCREEN_X 2 * 8
#define DUNGEON_SCREEN_Y 4 * 8
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

//------------------------------------------------------------------
// Prototypes.
//------------------------------------------------------------------

void sf_set_dungeon_mode(void);
void sf_update_dungeon_mode(void);

#endif