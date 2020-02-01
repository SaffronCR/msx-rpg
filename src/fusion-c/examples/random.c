//
// Fusion-C
// Pseudo Random Number
//

#include <stdlib.h>
#include <stdio.h>
#include "fusion-c/header/msx_fusion.h"

TIME tm;

char FT_RandomNumber (char a, char b)
{
    char random;
    
    random = rand()%(b-a)+a;  // Random number between a and b-1
    return(random);
}

void main(void) 
{
  char n,i;

  GetTime(&tm);
  srand(tm.sec);

  for(i=0;i < 10; i++)
  {
    n=FT_RandomNumber(1,100);
      printf("%d,",n);
    }
    
    Exit(0);
}
 
