#include "Pion.h"

Pion::Pion(int x, int y, bool white) : Piece(x, y, white), premierMouvement(true)
{}

void 
Pion::move( int x, int y )
{
	hasPassedTheFirstMove();
	Piece::move(x, y);
}


void
Pion::hasPassedTheFirstMove()
{
	premierMouvement = false;
}

bool 
Pion::mouvementValide(Echiquier & e, int x, int y)
{
	if(outOfBoard(x, y) || (this->x() == x && this->y() == y))
		return false;

	int absolute_x = ((this->x() > x) ? this->x() - x : x - this->x());
	int absolute_y = ((this->y() > y) ? this->y() - y : y - this->y());
	int offset_y = ((this->y() > y) ? -1 : 1);
	int offset_x = ((this->x() > x) ? -1 : 1);

	if(offset_y != (isWhite() ? 1 : -1))
		return false;

	if(e.getPiece(x, y) == 0)
	{
		if(absolute_x == 0)
			if(absolute_y == 1 || (absolute_y == 2 && premierMouvement 
									&& e.getPiece(this->x(), this->y() + offset_y) == 0))
				return true;
	}
	else
	{ 
		if(offset_y == (isWhite() ? 1 : -1) && absolute_y == 1 && absolute_x == 1 && e.getPiece(x, y)->isWhite() != this->isWhite())
			return true;
	}

	return false;
}

char
Pion::getChar() const
{
	return (isWhite() ? 'P' : 'p');
}

std::string
Pion::toString() const
{
	return "Pion: " + Piece::toString();
}