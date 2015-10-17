#ifndef PION_H
#define PION_H

#include "Piece.h"

class Pion : public Piece
{
	public:

    Pion(int x,int y,bool white);

    virtual ~Pion();

    virtual char typePiece();

    Pion *Clone();

    std::vector<Case> mouvementsPossible(Echiquier *e);
};

#endif // PION_H
