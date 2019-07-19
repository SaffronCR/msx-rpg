//------------------------------------------------------------------
// Dungeon Crawler for MSX2 using Fusion-C
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_sprites.h"
#include "fusion-c/header/vdp_graph2.h"
#include "fusion-c/header/ayfx_player.h"
#include "fusion-c/header/pt3replayer.h"

//------------------------------------------------------------------
// Defines.
//------------------------------------------------------------------

#define BUFFER_SIZE 4608

#define JOY_UP 1
#define JOY_DOWN 5
#define JOY_LEFT 7
#define JOY_RIGHT 3

#define DUNGEON_SIZE 16

#define BF_PG 1
#define BG_PG 2
#define WL_PG 3

#define DUNGEON_SCREEN_X 48
#define DUNGEON_SCREEN_Y 36
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

enum DoubleBufferState
{
  Updating,
  ReadyToTransfer,
  Transfering,
  Finished
};

enum Directions
{
  North,
  East,
  South,
  West,
};

//------------------------------------------------------------------
// Global variables.
//------------------------------------------------------------------

static FCB file; 
MMMtask  t;

char joy;
char trig;

enum DoubleBufferState db_state = Finished;

unsigned char load_buffer[BUFFER_SIZE];  

unsigned char dungeon_palette[] =
{
  0,0,0,0,
  1,0,0,0,
  2,0,0,0,
  3,0,0,0,
  4,0,0,0,
  5,0,0,0,
  6,0,0,0,
  7,0,0,0,
  8,0,0,0,
  9,2,1,1,
  10,1,1,3,
  11,4,2,1,
  12,6,2,2,
  13,6,3,1,
  14,4,4,5,
  15,6,6,2
};

unsigned char dungeon_01[DUNGEON_SIZE*DUNGEON_SIZE] =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1,
  1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1,
  1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1,
  1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1,
  1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1,
  1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1,
  1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1,
  1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1,
  1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1,
  1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

int dir_translate_x[] = { 0, 1, 0, -1 };
int dir_translate_y[] = { -1, 0, 1, 0 };

char player_moves = FALSE;

int player_pos_x = 1;
int player_pos_y = 4;

enum Direction player_dir = North;

//------------------------------------------------------------------
// Functions.
//------------------------------------------------------------------

// In case of Error.
void sf_error_handler (char n, char *name)
{
  InitPSG ();
  Screen (0);
  SetColors (15,6,6);
  
  switch (n)
  {
      case 1:
          printf ("\n\rFAILED: fcb_open(): %s ", name);
      break;

      case 2:
          printf ("\n\rFAILED: fcb_close(): %s", name);
      break;  

      case 3:
          printf ("\n\rSORRY: this game does not work on %s", name);
      break; 
  }

  Exit (0);
}

// Set the name of a file to load (MSX DOS).
void sf_set_name (FCB *p_fcb, const char *p_name)
{
  char i, j;
  memset (p_fcb, 0, sizeof(FCB));

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
      p_fcb->ext[j] =  p_name[i + j] ;
    }
  }
}

void sf_sc5_data (char *buffer, int y, int nbl)
{
  int i,s;

  s = 0;
  for (i = 0; i < nbl*128; ++i)
  {
      Vpoke(y*128+s,buffer[i]);
      s=s+1;
  }
}

// #TODO Check if the values are correct.
int sf_load_sc5_image (char *file_name, unsigned int start_Y, char *buffer)
{
  int rd = BUFFER_SIZE;
  int nbl = 0;

  InitPSG ();
  sf_set_name (&file, file_name);

  if (fcb_open (&file) != FCB_SUCCESS) 
  {
    sf_error_handler (1, file_name);
    return (0);
  }

  // Skip 7 first bytes of the file.
  fcb_read (&file, buffer, 7);

  while (rd != 0)
  {
    SetColors (0, 0, buffer[192]);

    rd = fcb_read (&file, buffer, BUFFER_SIZE);
    if (rd!=0)
    {
      // screen 5 (4 bits x 256 x 212).
      nbl = rd / 128;

      SetColors (0, 0, 0);

      //sf_sc5_data( buffer, start_Y, nbl);

      // Move the buffer to VRAM.
      HMMC (buffer, 0, start_Y, 256, nbl);

      start_Y = start_Y + nbl; 
    }
  }

  if (fcb_close (&file) != FCB_SUCCESS) 
  {
      sf_error_handler (2, file_name);
      return (0);
  }
 
  return (1);
}

// Loads a SC8 Picture and put data on screen, begining at start_Y line.
// #TODO Check if the values are correct.
int sf_load_sc8_image (char *file_name, unsigned int start_Y, char *buffer)
{
	int rd = 2304;
	int nbl = 0;
	InitPSG ();
	sf_set_name (&file, file_name);

	if (fcb_open(&file) != FCB_SUCCESS) 
	{
	  sf_error_handler (1, file_name);
	  return (0);
	}
	
  fcb_read (&file, buffer, 7);  // Skip 7 first bytes of the file.
	
  while (rd != 0)
	{
    SetColors (15,0,buffer[192]);
    rd = fcb_read (&file, buffer, 2304);
    if (rd != 0)
    {
      nbl = rd/256;
      HMMC (buffer, 0, start_Y, 256, nbl); // Move the buffer to VRAM. 17 lines x 256 pixels from memory.
      start_Y = start_Y + nbl; 
    }
	}

	if (fcb_close(&file) != FCB_SUCCESS) 
	{
		sf_error_handler (2, file_name);
		return (0);
	}

	return (1);
}

//  Copy a screen zone to another place
//  x1 & y1 =Top left coordonate  pixel of the zone to copy
//  dx = Width Size in pixels, of the zone to copy
//  dy = Height Size in pixels, of the zone to copy
//  x2 & y2 = Destination coordonate where to copy the zone
//  src_pg = Source Page number of the Zone
//  dst_pg = Destination number of the zone
//  mode = OP mode of the copy
void sf_screen_copy (int x1, int y1, int dx, int dy, int x2, int y2, int src_pg, int dst_pg, int mode)  
{
  int src_y = 0;
  int dst_y = 0;

  // Add page offset.
  src_y += src_pg * 256;

  // Add page offset.    
  dst_y += dst_pg * 256;

  t.X = x1; 
  t.Y = src_y+y1; 

  t.X2 = x2; 
  t.Y2 = dst_y+y2;           

  t.DX = dx;  
  t.DY = dy;

  t.s0 = 0;
  t.DI = 0;
  t.LOP = mode;

  fLMMM (&t);
}

void sf_draw_third_wall_far_left (int x, int y)
{
  if (x >= 0 && x < DUNGEON_SIZE &&
      y >= 0 && y < DUNGEON_SIZE &&
      dungeon_01[x + y*DUNGEON_SIZE] == 1)
  {
    sf_screen_copy (THIRD_WALL_FAR_LEFT_X, THIRD_WALL_FAR_LEFT_Y, 
                    THIRD_WALL_FAR_DX, THIRD_WALL_FAR_DY, 
                    DUNGEON_SCREEN_X, DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - THIRD_WALL_FAR_DY) * 0.5),
                    WL_PG, BF_PG, LOGICAL_TIMP);
  }
}

void sf_draw_third_wall_far_right (int x, int y)
{
  if (x >= 0 && x < DUNGEON_SIZE &&
      y >= 0 && y < DUNGEON_SIZE &&
      dungeon_01[x + y*DUNGEON_SIZE] == 1)
  {
    sf_screen_copy (THIRD_WALL_FAR_RIGHT_X, THIRD_WALL_FAR_RIGHT_Y, 
                    THIRD_WALL_FAR_DX, THIRD_WALL_FAR_DY, 
                    DUNGEON_SCREEN_X + DUNGEON_SCREEN_DX - THIRD_WALL_FAR_DX, DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - THIRD_WALL_FAR_DY) * 0.5),
                    WL_PG, BF_PG, LOGICAL_TIMP);
  }
}

void sf_draw_third_wall_left (int x, int y)
{
  if (x >= 0 && x < DUNGEON_SIZE &&
      y >= 0 && y < DUNGEON_SIZE &&
      dungeon_01[x + y*DUNGEON_SIZE] == 1)
  {
    sf_screen_copy (THIRD_WALL_LEFT_X, THIRD_WALL_LEFT_Y, 
                    THIRD_WALL_DX, THIRD_WALL_DY, 
                    DUNGEON_SCREEN_X + THIRD_WALL_OFFSET_X, DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - THIRD_WALL_DY) * 0.5),
                    WL_PG, BF_PG, LOGICAL_TIMP);
  }
}

void sf_draw_third_wall_right (int x, int y)
{
  if (x >= 0 && x < DUNGEON_SIZE &&
      y >= 0 && y < DUNGEON_SIZE &&
      dungeon_01[x + y*DUNGEON_SIZE] == 1)
  {
    sf_screen_copy (THIRD_WALL_RIGHT_X, THIRD_WALL_RIGHT_Y, 
                    THIRD_WALL_DX, THIRD_WALL_DY, 
                    DUNGEON_SCREEN_X + DUNGEON_SCREEN_DX - THIRD_WALL_DX - THIRD_WALL_OFFSET_X, DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - THIRD_WALL_DY) * 0.5),
                    WL_PG, BF_PG, LOGICAL_TIMP);
  }
}

void sf_draw_second_wall_far_left (int x, int y)
{
  if (x >= 0 && x < DUNGEON_SIZE &&
      y >= 0 && y < DUNGEON_SIZE &&
      dungeon_01[x + y*DUNGEON_SIZE] == 1)
  {
    sf_screen_copy (SECOND_WALL_FAR_LEFT_X, SECOND_WALL_FAR_LEFT_Y, 
                    SECOND_WALL_FAR_DX, SECOND_WALL_FAR_DY, 
                    DUNGEON_SCREEN_X, DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - SECOND_WALL_FAR_DY) * 0.5),
                    WL_PG, BF_PG, LOGICAL_TIMP);
  }
}

void sf_draw_second_wall_far_right (int x, int y)
{
  if (x >= 0 && x < DUNGEON_SIZE &&
      y >= 0 && y < DUNGEON_SIZE &&
      dungeon_01[x + y*DUNGEON_SIZE] == 1)
  {
    sf_screen_copy (SECOND_WALL_FAR_RIGHT_X, SECOND_WALL_FAR_RIGHT_Y, 
                    SECOND_WALL_FAR_DX, SECOND_WALL_FAR_DY, 
                    DUNGEON_SCREEN_X + DUNGEON_SCREEN_DX - SECOND_WALL_FAR_DX, DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - SECOND_WALL_FAR_DY) * 0.5),
                    WL_PG, BF_PG, LOGICAL_TIMP);
  }
}

void sf_draw_second_wall_left (int x, int y)
{
  if (x >= 0 && x < DUNGEON_SIZE &&
      y >= 0 && y < DUNGEON_SIZE &&
      dungeon_01[x + y*DUNGEON_SIZE] == 1)
  {
    sf_screen_copy (SECOND_WALL_LEFT_X, SECOND_WALL_LEFT_Y, 
                    SECOND_WALL_DX, SECOND_WALL_DY, 
                    DUNGEON_SCREEN_X, DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - SECOND_WALL_DY) * 0.5),
                    WL_PG, BF_PG, LOGICAL_TIMP);
  }
}

void sf_draw_second_wall_right (int x, int y)
{
  if (x >= 0 && x < DUNGEON_SIZE &&
      y >= 0 && y < DUNGEON_SIZE &&
      dungeon_01[x + y*DUNGEON_SIZE] == 1)
  {
    sf_screen_copy (SECOND_WALL_RIGHT_X, SECOND_WALL_RIGHT_Y, 
                    SECOND_WALL_DX, SECOND_WALL_DY, 
                    DUNGEON_SCREEN_X + DUNGEON_SCREEN_DX - SECOND_WALL_DX, DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - SECOND_WALL_DY) * 0.5),
                    WL_PG, BF_PG, LOGICAL_TIMP);
  }
}

void sf_draw_first_wall_left (int x, int y)
{
  if (x >= 0 && x < DUNGEON_SIZE &&
      y >= 0 && y < DUNGEON_SIZE &&
      dungeon_01[x + y*DUNGEON_SIZE] == 1)
  {
    sf_screen_copy (FIRST_WALL_LEFT_X, FIRST_WALL_LEFT_Y, 
                    FIRST_WALL_DX, FIRST_WALL_DY, 
                    DUNGEON_SCREEN_X, DUNGEON_SCREEN_Y,
                    WL_PG, BF_PG, LOGICAL_TIMP);
  }
}

void sf_draw_first_wall_right (int x, int y)
{
  if (x >= 0 && x < DUNGEON_SIZE &&
      y >= 0 && y < DUNGEON_SIZE &&
      dungeon_01[x + y*DUNGEON_SIZE] == 1)
  {
    sf_screen_copy (FIRST_WALL_RIGHT_X, FIRST_WALL_RIGHT_Y, 
                    FIRST_WALL_DX, FIRST_WALL_DY, 
                    DUNGEON_SCREEN_X + DUNGEON_SCREEN_DX - FIRST_WALL_DX, DUNGEON_SCREEN_Y,
                    WL_PG, BF_PG, LOGICAL_TIMP);
  }
}

void sf_draw_third_wall_front (int x, int y)
{
  if (x >= 0 && x < DUNGEON_SIZE &&
      y >= 0 && y < DUNGEON_SIZE &&
      dungeon_01[x + y*DUNGEON_SIZE] == 1)
  {
    sf_screen_copy (THIRD_FRONT_WALL_X, THIRD_FRONT_WALL_Y, 
                    THIRD_FRONT_WALL_DX, THIRD_FRONT_WALL_DY, 
                    DUNGEON_SCREEN_X + ((DUNGEON_SCREEN_DX - THIRD_FRONT_WALL_DX) * 0.5), DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - THIRD_FRONT_WALL_DY) * 0.5),
                    WL_PG, BF_PG, LOGICAL_TIMP);
  }
}

void sf_draw_second_wall_front (int x, int y)
{
  if (x >= 0 && x < DUNGEON_SIZE &&
      y >= 0 && y < DUNGEON_SIZE &&
      dungeon_01[x + y*DUNGEON_SIZE] == 1)
  {
    sf_screen_copy (SECOND_FRONT_WALL_X, SECOND_FRONT_WALL_Y, 
                    SECOND_FRONT_WALL_DX, SECOND_FRONT_WALL_DY, 
                    DUNGEON_SCREEN_X + ((DUNGEON_SCREEN_DX - SECOND_FRONT_WALL_DX) * 0.5), DUNGEON_SCREEN_Y + ((DUNGEON_SCREEN_DY - SECOND_FRONT_WALL_DY) * 0.5),
                    WL_PG, BF_PG, LOGICAL_TIMP);
  }
}

/*
 * This is the area to draw:
 * 
 *  x x x x x
 *  x x x x x
 *    x o x  
 *
 * horizontal order: far left, left, front, right, far right.
 * vertical order: third, second, first.
 */
void sf_update_dungeon ()
{
  int x, y, xd, yd;

  int mult = 1;
  if (player_dir == North || player_dir == South)
  {
    mult = -1;
  }

  // Draw by distance.
  for (int dist = 2; dist > -1; dist--)
  {
    x = player_pos_x + (dist*dir_translate_x[player_dir]);
    y = player_pos_y + (dist*dir_translate_y[player_dir]);

    // Far left walls.
    xd = x - (2*mult*dir_translate_y[player_dir]);
    yd = y - (2*mult*dir_translate_x[player_dir]);
    if      (dist == 2) sf_draw_third_wall_far_left   (xd, yd);
    else if (dist == 1) sf_draw_second_wall_far_left  (xd, yd);

    // Left walls.
    xd = x - (mult*dir_translate_y[player_dir]);
    yd = y - (mult*dir_translate_x[player_dir]);
    if      (dist == 2) sf_draw_third_wall_left   (xd, yd);
    else if (dist == 1) sf_draw_second_wall_left  (xd, yd);
    else                sf_draw_first_wall_left   (xd, yd);

    // Far right walls.
    xd = x + (2*mult*dir_translate_y[player_dir]);
    yd = y + (2*mult*dir_translate_x[player_dir]);
    if      (dist == 2) sf_draw_third_wall_far_right  (xd, yd);
    else if (dist == 1) sf_draw_second_wall_far_right (xd, yd);

    // Right walls.
    xd = x + (mult*dir_translate_y[player_dir]);
    yd = y + (mult*dir_translate_x[player_dir]);
    if      (dist == 2) sf_draw_third_wall_right  (xd, yd);
    else if (dist == 1) sf_draw_second_wall_right (xd, yd);
    else                sf_draw_first_wall_right  (xd, yd);

    // Front walls.
    if      (dist == 2) sf_draw_third_wall_front  (x, y);
    else if (dist == 1) sf_draw_second_wall_front (x, y);
  }
}

// Draw the current dungeon room.
void sf_update_dungeon_screen ()
{
  db_state = Updating;

  // Background.
  sf_screen_copy (0,0, 
                  DUNGEON_SCREEN_DX, DUNGEON_SCREEN_DY, 
                  DUNGEON_SCREEN_X, DUNGEON_SCREEN_Y, 
                  BG_PG, BF_PG, opHMMM);

  // Dungeon walls.
  sf_update_dungeon();    

  // Enemies.
  // #TODO
  // sf_screen_copy (215,0, 41,64, 100,90, 3, 0, LOGICAL_TIMP);

  db_state = ReadyToTransfer;
}

void sf_draw_minimap ()
{
  for (int x = 0; x < DUNGEON_SIZE; x++)
  {
    for (int y = 0; y < DUNGEON_SIZE; y++)
    {
      if (dungeon_01[x+y*DUNGEON_SIZE] == 1)
      {
        Pset (x, y, 10, LOGICAL_IMP);
      }
      else if (player_pos_x == x && player_pos_y == y)
      {
        Pset (x, y, 11, LOGICAL_IMP);
      }
    }
  }
}

void sf_update_screen ()
{
  if (db_state == ReadyToTransfer)
  {
    db_state = Transfering;

    // Copy to actual screen.
    sf_screen_copy (0,0, 
                    256, 212, 
                    0, 0, 
                    BF_PG, 0, opYMMM);

    // Using this to check screen redrawing. Actual game text will be handled differently.
    SetColors (15, 0, 0);

    if      (player_dir == North) PutText (100, 20, "North", LOGICAL_IMP);
    else if (player_dir == East)  PutText (100, 20, "East",  LOGICAL_IMP);
    else if (player_dir == South) PutText (100, 20, "South", LOGICAL_IMP);
    else                          PutText (100, 20, "West",  LOGICAL_IMP);

    // Minimap.
    sf_draw_minimap ();

    db_state = Finished;
  }
}

void sf_move (int newPosX, int newPosY)
{
  if (newPosX > 0 && newPosX < DUNGEON_SIZE-1 &&
      newPosY > 0 && newPosY < DUNGEON_SIZE-1 &&
      dungeon_01[newPosX + newPosY*DUNGEON_SIZE] == 0)
  {
    player_pos_x = newPosX;
    player_pos_y = newPosY;

    player_moves = TRUE;
  }
}

void sf_rotate_left ()
{
  if (--player_dir < North)
  {
    player_dir = West;
  }

  player_moves = TRUE;
}

void sf_rotate_right ()
{
  if (++player_dir > West)
  {
    player_dir = North;
  }

  player_moves = TRUE;
}

// Reads joystick input, from keyboard's arrow keys and joystick port 1.
void sf_update_joy ()
{
  for (int i = 0; i < 1; i++)
  {
    joy = JoystickRead (i);
    trig = TriggerRead (i);

    // #TODO
    switch (joy) 
    {
      case JOY_UP:
        sf_move (player_pos_x + dir_translate_x[player_dir], 
                  player_pos_y + dir_translate_y[player_dir]);
        break;

      case JOY_DOWN:
        sf_move (player_pos_x - dir_translate_x[player_dir], 
                  player_pos_y - dir_translate_y[player_dir]);
        break;

      case JOY_LEFT:
        sf_rotate_left ();
        break;

      case JOY_RIGHT:
        sf_rotate_right ();
        break;
    }
  }
}

static char sf_video_interrupt (void)
{
  if (IsVsync () == 0 || db_state != ReadyToTransfer)
  {
    return (0);
  }

  sf_update_screen ();

  return (1);
}

// Main.
void main (void) 
{
	// Initialization of the PSG (Use this function before sending data to PSG).
	// All registers will be set to 0, and stops all noises and sounds.
	InitPSG ();

	// Enables Sprites.
	SpriteOn ();

	// Sets display to specified screen mode (from 0 to 8).
	Screen (5);

	// Clears console or any screen mode
	Cls ();

	// Disable key sound.
	KeySound (0);

	// Switches the MSX2 VDP to 50 Hz Pal Mode.
	VDP50Hz ();

	// Clears the key buffer.
	KillKeyBuffer ();

	PutText (5, 5, "LOADING...", LOGICAL_TIMP);

	// Load screens.
  SetSC5Palette ((Palette *)dungeon_palette);

  sf_load_sc5_image ("BG.SC5",     256 * BG_PG, load_buffer);
  sf_load_sc5_image ("WALLS.SC5",  256 * WL_PG, load_buffer);

	// Clears console or any screen mode.
	Cls ();
  SetColors (0, 0, 0);

  // Set interrupt.
  InitInterruptHandler ();
  SetInterruptHandler (sf_video_interrupt);

  // Initial screen update.
	sf_update_dungeon_screen ();

	for (;;)
	{
    // Player input must wait until the next frame is ready.
    if (db_state == Finished)
    {
      sf_update_joy ();

      // Update screen if needed.
      if (player_moves)
      {
        sf_update_dungeon_screen ();

        player_moves = FALSE;      
      }
    }
  }
}
