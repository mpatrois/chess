#include "Reine.h"


Reine::Reine(bool white) : Piece(4, (white  ? 1 : 8), white), Fou(), Tour()
{
	std::cout << "Creation reine \n"; 
}

bool 
Reine::mouvementValide(Echiquier & e, int x, int y)
{

	return Fou::mouvementValide(e,x,y) || Tour::mouvementValide(e,x,y);
}

char
Reine::getChar() const
{
	return (isWhite() ? 'Q' : 'q');
}

std::string
Reine::toString() const
{
	return "Reine: " + Piece::toString();
}
