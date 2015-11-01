#ifndef FOU_H
#define FOU_H

#include "Piece.h"
#include <cmath>
#include <iostream>

class Bishop : public Piece
{
	public:

    Bishop(int x, int y, bool white);

    virtual ~Bishop();

    virtual char typePiece();;

    Bishop *clone();

    std::vector<Case> mouvementsPossible(Chessboard *e);
};

#endif // FOU_H
