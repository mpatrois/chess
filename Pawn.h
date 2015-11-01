#ifndef PION_H
#define PION_H

#include "Piece.h"
#include "Chessboard.h"

class Pawn : public Piece
{
    int nbMove;

	public:

    Pawn(int x,int y,bool white);

    virtual ~Pawn();

    virtual char typePiece();

    Pawn *clone();

    std::vector<Case> mouvementsPossible(Chessboard *e);

    int getNbMove();

     void move( int x, int y,Chessboard *e );
};

#endif // PION_H
