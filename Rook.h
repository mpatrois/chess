#ifndef TOUR_H
#define TOUR_H

#include "Piece.h"


class Rook : public Piece
{
    private:
    bool moved;

    public:

    Rook(int x, int y, bool white);

    virtual ~Rook();

    virtual char typePiece();

    Rook *clone();

    std::vector<Case> mouvementsPossible(Chessboard *e);

    bool hadMove();

    void move( int x, int y,Chessboard *e );
};

#endif // TOUR_H
