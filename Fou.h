#ifndef FOU_H
#define FOU_H

#include "Piece.h"
#include <cmath>
#include <iostream>

class Fou : public Piece
{
	public:

    Fou(int x, int y, bool white);

    virtual ~Fou();

    virtual char typePiece();;

    Fou *Clone();

    std::vector<Case> mouvementsPossible(Echiquier *e);
};

#endif // FOU_H
