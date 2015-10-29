#include "Queen.h"


Queen::Queen(bool white) : Piece(4, (white  ? 1 : 8), white), Bishop(), Rook()
{}

bool
Queen::mouvementValide(Chessboard & e, int x, int y)
{
	return Bishop::mouvementValide(e,x,y) || Rook::mouvementValide(e,x,y);
}

char
Queen::getChar() const
{
	return (isWhite() ? 'Q' : 'q');
}

std::string
Queen::toString() const
{
	return "Queen: " + Piece::toString();
}
