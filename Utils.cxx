#include <iostream>
#include "Utils.h"

bool 
outOfBoard(int x, int y)
{
  return !( x > 0 && x < 9  && y > 0  && y < 9);
}


int
matrixToArrayPosition(int x, int y)
{
	if( x>0 && x<9 && y>0 && y<9 )
		return x-1 + (y - 1) * 8; 
}

int 
mouseCoordinatesToPosition(int x, int y, int windowSize)
{
	if(x>30 && x<windowSize-30 && y>30 && y<windowSize-30)
		return ((x-30)/80)*8 + ((y-30)/80);
}


int 
mouseToCoordinate(int mouseXorY)
{
	return (mouseXorY-30)/80 + 1;
}

