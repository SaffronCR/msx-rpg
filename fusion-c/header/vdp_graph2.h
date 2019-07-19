/*
 ___________________________________________________________
/               __           _                              \
|              / _|         (_)                             |
|             | |_ _   _ ___ _  ___  _ __                   |
|             |  _| | | / __| |/ _ \| '_ \                  |
|             | | | |_| \__ \ | (_) | | | |                 |
|             |_|  \__,_|___/_|\___/|_| |_| *               |
|                                                           |
|               The MSX C Library for SDCC                  |
|                   V1.0 - 09-10-11 2018                    |
|                                                           |
|                Eric Boez &  Fernando Garcia               |
|                                                           |
|   vdp_graph2.h : Drawing and graphic functions for MSX2   |
|                                                           |
|    Using BIOS only. Very basis, small code.               |
|                                                           |
\___________________________________________________________/
*                         (°□°)
*	Most original code from SOLID MSX C - (c) 1997
*	SDCC port 2015  by ?	
*	
*	----------------------------------------------------------------------------
*	| SCREEN 5	256 (horizontal) x 212 (vertical) dots  	       |
*	|			16 colours can be displayed at the same time	   |
*	|			each of 16 colours can be selected from 512 colours|
*	| Command:		high speed graphic by VDP command available	   |
*	| Memory requirements:	32kB for screen - 6A00H bytes		   |
*	|			  (4 bits x 256 x 212)				               |
*	---------------------------------------------------------------------------- 
*
*	----------------------------------------------------------------------------
*	| SCREEN 8	256 (horizontal) x 256 (vertical) dots             |
*   |            (Only 212 high are displayes) 	                   |
*	|			256 colours can be displayed at the same time	   |
*	|			each color is unique and can't be changed (0 to 255|
*	| Command:		high speed graphic by VDP command available	   |
*	| Memory requirements: 64K from 0H to FFFFH for                |
*   |                      each of the 2 available pages       	   |
*	|			    (8 bits x 256 x 256)				           |
*	---------------------------------------------------------------------------- 
*	
*/

#ifndef __VDP_GRAPH2__
#define __VDP_GRAPH2__


/* Palette */
typedef struct {
	unsigned char colour;	// colour number 0..15
	unsigned char R;	// 0..7	red brightness
	unsigned char G;	// 0..7	green brightness
	unsigned char B;	// 0..7	blue brightness
} ColRGB;

typedef struct { 
	ColRGB rgb[16]; 
} Palette;


int					vMSX( void );												// 1-MSX1 , 2-MSX2  */
void				WriteScr( unsigned int addr_from );							// Whole SC5 RAM <=> VRAM dumb copy (0x6A00 bytes)  Writes screen from RAM memory address to VRAM, very dumb one time way, use HMMM! */
void				ReadScr( unsigned int addr_to ); 							// Reads SC5 from VRAM to memory address, very dumb one time way, use HMMM! */
void				SetSC5Palette (Palette *palette); 							// Set colors defined in given table
void				RestoreSC5Palette ( void );									// Sets default MSX palette
/* PAGE 0 operations for X=0..255,Y=0..211	do not use for outside regions (16-bit AHL), then use smart fLMMM */
		
extern	void	Pset( int X,  int Y,  int colour, int OP );	/* puts pixel in (X,Y), logical OP=0 (just copy)  sends data to VDP chip directly */
extern	void	PsetXY( int X,  int Y,  int colour );		/* method 2 by rst 30h, writes in VRAM */
extern	int		Point( int X,  int Y ); 					/* gets colour 0..15 of pixel at (X,Y)  */
extern	int		pgetXY( int X,  int Y );					/* method 2 by rst 30h */
extern	void	Line( int X1,  int Y1, int X2,  int Y2, int colour, int OP ); 	/* draws line (X,Y)-(X2,Y2), with logical operation*/
extern	void	Rect( int X1, int Y1, int X2, int Y2, int colour, int OP ); 	/* draws rectangle (X,Y)-(X2,Y2), with logical operation, fills if OP is FILL_ALL */
extern	void	Paint( int X, int Y, int colour, int border_colour );  			/* Paint for small regions. Split them if large. It is not the BASIC-subROM paint! Kind of bugPaint. Requires large stack of memory, slower than any image processing. */
extern	void	Draw( char *drawcommands );										/* Remake of BASICs "draw" with original commands (except A,X) syntax. */

/* Fast RAM <=> VRAM operations */
//updated by (BTV) Bitvision Software 2018
// Now Y & height could be greater than 255
extern	void 	HMMC( void *pixeldatas, int X, int Y, int DX, int DY ); 		/* High speed copy from RAM buffer to VRAM (size = DX*DY), X=0..255,Y=0..211 */
extern	void 	HMCM( int X1, int Y1, int X2, int Y2, void *tobuffer );			/* High speed rectangle (X1,Y1)-(X2,Y2) copying from VRAM  to RAM buffer, no logical feature */
extern	void 	HMCM_SC8( int X1, int Y1, int X2, int Y2, void *tobuffer );		/* High speed rectangle (X1,Y1)-(X2,Y2) copying from VRAM  to RAM buffer, no logical feature */
extern	void 	LMMM( int X, int Y, int DX, int DY, int Xt, int Yt, int OP );	/* High speed copy with logical OP from VRAM to VRAM at (Xt,Yt) position */

/*
	High speed far copy with logical OP from VRAM to VRAM

	To use all 128Kb VRAM, use (0,0)-(255,1023) coordinates and function fLMMM
	Visible is memory block of active page. Hide image parts outside.
	
; Coordinate system of VRAM 
; pages and memory blocks (32kb)
;	(SCREEN 5)
; ------------------------------	  00000H
; | (0,0) 	     (255,0) |	    |
; |	    Page 0	     |	    |
; | (0,255)	   (255,255) |	    |    Sprites reside 7400 - 7FFF
; ------------------------------	  08000H
; | (0,256)	   (255,256) |	    |
; |	    Page 1	     |	    |
; | (0,511)	   (255,511) |	    |
; ------------------------------	  10000H
; | (0,512)	   (255,512) |	    |
; |	    Page 2	     |	    |
; | (0,767)	   (255,767) |	    |
; ------------------------------	  18000H
; | (0,768)	   (255,768) |	    |
; |	    Page 3	     |	    |
; | (0,1023)	  (255,1023) |	    |
; ------------------------------	  1FFFFH 

When using fLMMM then we work on coordinates level, not addressing.
fHMMM copies VRAM rectangle(X,Y)-(X+DX,X+DY) TO VRAM (X2,Y2)

----------------------------------------------------------
| Command name 	| Destination | Source | Units | Mnemonic |
----------------------------------------------------------
|	       		|    VRAM     |	CPU   | bytes |   HMMC	 |
| High speed	|    VRAM     |	VRAM  | bytes |   YMMM	 |
| move	       	|    VRAM     |	VRAM  | bytes |   HMMM	 |
|	       		|    VRAM     |	VDP   | bytes |   HMMV	 |
----------------------------------------------------------
|	       		|    VRAM     |	CPU   | dots  |   LMMC	 |
| Logical      	|    CPU      |	VRAM  | dots  |   LMCM	 |
| move	       	|    VRAM     |	VRAM  | dots  |   LMMM	 | default
|	       		|    VRAM     |	VDP   | dots  |   LMMV	 |
---------------------------------------------------------- 
*/
// (a) LOP to "or"|: operations by code.
#define opHMMC 0xF0
#define opYMMM 0xE0
#define opHMMM 0xD0
#define opHMMV 0xC0
#define opLMMC 0xB0
#define opLMCM 0xA0
#define opLMMM 0x90
#define opLMMV 0x80

#define DIX_RIGHT 0
#define DIY_DOWN 0

// (b) DI to "or"|: scrolling backwards case only, X,Y,X2,Y2 should +DX,+DY
#define DIX_LEFT 4
#define DIY_UP 8

// (b) DI to "or"|: Expanded RAM , default is 0 for VRAM
#define MSX_source_ExpRAM 16
#define MXD_dest_ExpRAM 32
// (b) DI to "or"|: Stop when colour found
#define MSX_EQ_stop 2

typedef struct {
	unsigned int X;		// source X (0 to 511)
	unsigned int Y;		// source Y (0 to 1023)
	unsigned int X2;	// destination X (0 to 511)
	unsigned int Y2;	// destination Y (0 to 1023)
	unsigned int DX; 	// width (0 to 511)
	unsigned int DY; 	// height (0 to 511)
	unsigned char s0;	// set to 0, dummy 1st empty byte sent to chip
	unsigned char DI;	// set to 0 (b), works well from left to right
	unsigned char LOP;	// 0 to copy (a), Logical+Operation ("or"| definitions)	
} MMMtask;

extern	void fLMMM( MMMtask *VDPtask );		// fast copy by structure


#endif
