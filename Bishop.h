#ifndef FOU_H
#define FOU_H

#include "Piece.h"
#include <cmath>

class Bishop : public Piece
{
	public:

	    Bishop(int x, int y, bool white);

	    virtual ~Bishop();

	    Bishop *clone();

	    std::vector<Square> availableMovements(Chessboard *e);

	    virtual char typePiece();
};

#endif // FOU_H
