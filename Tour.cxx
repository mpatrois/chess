#include "Tour.h"

Tour::Tour()
{}

Tour::Tour(int x, int y, bool white) : Piece(x, y, white)
{}

bool 
Tour::mouvementValide(Echiquier & e, int x, int y)
{
	if(outOfBoard(x , y) || (this->x() != x && this->y() != y))
		return false;

	if(e.getPiece(x, y) != 0 && e.getPiece(x, y)->isWhite() == isWhite())
		return false;

	int offset_x = ((this->x() == x) ? 0 : ((this->x() > x) ? -1 : 1));
	int offset_y = ((this->y() == y) ? 0 : ((this->y() > y) ? -1 : 1));
	int m_x = this->x();
	int m_y = this->y();

	do {
		m_x += offset_x;
		m_y += offset_y;
		if ((m_x != x || m_y != y) && e.getPiece(m_x , m_y) != 0)
			return false;
	} while(m_x != x || m_y != y);

	return true;
}

char
Tour::getChar() const
{
	return (isWhite() ? 'T' : 't');
}

std::string
Tour::toString() const
{
	return "Tour: " + Piece::toString();
}