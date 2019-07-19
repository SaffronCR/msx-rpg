#include "fusion-c/header/msx_fusion.h"
#include "fusion-c/header/vdp_graph2.h"
#include <string.h>
 
static FCB file;
 
 
unsigned char LDbuffer[2200];
 
 void FT_SetName( FCB *p_fcb, const char *p_name ) 
{
  char i, j;
  memset( p_fcb, 0, sizeof(FCB) );
  for( i = 0; i < 11; i++ ) {
    p_fcb->name[i] = ' ';
  }
  for( i = 0; (i < 8) && (p_name[i] != 0) && (p_name[i] != '.'); i++ ) {
    p_fcb->name[i] =  p_name[i];
  }
  if( p_name[i] == '.' ) {
    i++;
    for( j = 0; (j < 3) && (p_name[i + j] != 0) && (p_name[i + j] != '.'); j++ ) {
      p_fcb->ext[j] =  p_name[i + j] ;
    }
  }
}
 
void FT_errorHandler(char n, char *name)
{
  InitPSG();
  Screen(0);
  SetColors(15,6,6);
  switch (n)
  {
      case 1:
          Print("\n\rFAILED: fcb_open(): ");
          Print(name);
      break;
 
      case 2:
          Print("\n\rFAILED: fcb_close():");
          Print(name);
      break;  
 
      case 3:
          Print("\n\rStop Kidding, run me on MSX2 !");
      break; 
  }
Exit(0);
}
 
void FT_SC5Data( char *buffer, int y, int nbl)
{
    int i,s;
 
        s=0;
        for ( i = 0; i < nbl*128; ++i)
        {
            Vpoke(y*128+s,buffer[i]);
            s=s+1;
 
        }
}
 
int FT_LoadSc5Image(char *file_name, unsigned int start_Y, char *buffer)
    {
        int rd=2304;
        int nbl=0;
        InitPSG();
        FT_SetName( &file, file_name );
        if(fcb_open( &file ) != FCB_SUCCESS) 
        {
          FT_errorHandler(1, file_name);
          return (0);
        }
        fcb_read( &file, buffer, 7 );  // Skip 7 first bytes of the file
        while(rd!=0)
        {
 
            rd = fcb_read( &file, buffer, 2176 );
                if (rd!=0)
                {
 
                  nbl=rd/128;
                  //HMMC(buffer, 0,start_Y,256,nbl ); // Move the buffer to VRAM. 17 lines x 256 pixels  from memory
                  FT_SC5Data( buffer, start_Y, nbl);
                  start_Y=start_Y+nbl; 
              }
        }
      if( fcb_close( &file ) != FCB_SUCCESS ) 
      {
         FT_errorHandler(2, file_name);
          return (0);
      }
 
return(1);
}
 
 
void main(void)
{ 
    char a,l,r;
    int i;
    char mypalette[] = {
    0, 0,0,0,
    1, 2,1,1,
    2, 6,5,4,
    3, 5,4,3,
    4, 5,5,3,
    5, 6,5,3,
    6, 7,6,4,
    7, 3,2,1,
    8, 7,5,2,
    9, 6,4,2,
    10, 4,3,2,
    11, 4,3,1,
    12, 5,3,2,
    13, 3,3,2,
    14, 3,1,0,
    15, 5,2,0
    };
 
    Screen(5);
    SetColors(15,0,0);    
 
    FT_LoadSc5Image("mona.sc5",0,LDbuffer);
 
    SetSC5Palette((Palette *)mypalette);
 
 
    WaitForKey();
    Screen(0);
    Exit(0);
 
}