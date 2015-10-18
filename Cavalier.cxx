#include "Cavalier.h"

Cavalier::Cavalier(int x, int y, bool white) : Piece(x, y, white)
{}

bool 
Cavalier::mouvementValide(Echiquier & e, int x, int y)
{
	if(outOfBoard(x, y) || (this->x() == x && this->y() == y))
		return false;
	
	if(e.getPiece(x, y) != 0 && e.getPiece(x, y)->isWhite() == isWhite())
		return false;

	if (( std::abs(this->x() - x) == 2 && std::abs(this->y() - y) == 1 ) 
		|| ( std::abs(this->x() - x) == 1 && std::abs(this->y() - y) == 2 ))
		return true;

	return false;
}

char
Cavalier::getChar() const
{
	return (isWhite() ? 'C' : 'c');
}

std::string
Cavalier::toString() const
{
	return "Cavalier: " + Piece::toString();
}