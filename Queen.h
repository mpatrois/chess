#ifndef REINE_H
#define REINE_H

#include "Piece.h"


class Queen : public Piece
{
    public:

        Queen(int x, int y, bool white);

        virtual ~Queen();

        Queen *clone();

        virtual char typePiece();;

        std::vector<Case> mouvementsPossible(Chessboard *e);

};

#endif // REINE_H
