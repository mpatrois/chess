#ifndef CAVALIER_H
#define CAVALIER_H

#include "Piece.h"
#include "Chessboard.h"

class Knight : public Piece
{
    public:

    Knight(int x, int y, bool white);

    Knight *clone();

    virtual ~Knight();

    virtual char typePiece();

    std::vector<Case> mouvementsPossible(Chessboard *e);
};

#endif // CAVALIER_H
