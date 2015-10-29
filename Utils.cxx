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
	if(x>10 && x<windowSize-10 && y>10 && y<windowSize-10)
		return ((x-10)/60)*8 + ((y-10)/60);
}


int
mouseToCoordinate(int mouseXorY)
{
	return (mouseXorY-30)/60 + 1;
}
