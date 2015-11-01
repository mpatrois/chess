#ifndef PION_H
#define PION_H

#include "Piece.h"

class Pion : public Piece
{
    int nbMove;

	public:

    Pion(int x,int y,bool white);

    virtual ~Pion();

    virtual char typePiece();

    Pion *Clone();

    std::vector<Case> mouvementsPossible(Echiquier *e);

    int getNbMove();

     void move( int x, int y );
};

#endif // PION_H
