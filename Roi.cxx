#include "Roi.h"
#include <assert.h>

Roi::Roi(bool white) : Piece(5, (white ? 1 : 8), white)
{
	std::cout << "Creation roi \n";
}

bool 
Roi::mouvementValide(Echiquier & e, int x, int y)
{
	if(outOfBoard(x, y) 
		|| (this->x() == x && this->y() == y)
		|| (e.getPiece(x, y) != 0 && e.getPiece(x, y)->isWhite() == isWhite()))
		return false;

	int absolute_x = ((this->x() > x) ? this->x() - x : x - this->x());
	int absolute_y = ((this->y() > y) ? this->y() - y : y - this->y());

	if(absolute_x > 1 || absolute_y > 1 )
		return false;

	if(e.getPiece(x, y) != 0 && e.getPiece(x, y)->isWhite() != isWhite() && isNotEchec(e, x, y))
		return true;

	return isNotEchec(e, x, y);
}

bool Roi::isNotEchec(Echiquier &e, int x, int y)
{
	int old_x = this->x();
	int old_y = this->y();

	Piece * removedPiece = 0;

	if(e.getPiece(x, y) != 0)
		removedPiece = e.enleverPiece(x, y);

	assert(e.deplacer(this, x, y) != false );

	for(int numCase = 0; numCase < e.m_size; numCase++)
	{
		if(e.getPiece(numCase) != 0 && e.getPiece(numCase) != this && e.getPiece(numCase)->isWhite() != this->isWhite())
		{
			if(e.getPiece(numCase)->mouvementValide(e, x, y))
			{
				e.deplacer(this, old_x, old_y);
				if(removedPiece != 0)
					e.placer(removedPiece);
				return false;
			}
		}
	}

	e.deplacer(this, old_x, old_y);

	if(removedPiece != 0)
		e.placer(removedPiece);

	return true;
}

char
Roi::getChar() const
{
	return (isWhite() ? 'R' : 'r');
}

std::string
Roi::toString() const
{
	return "Roi: " + Piece::toString();
}
