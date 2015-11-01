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

        std::vector<Square> availableMovements(Chessboard *e);

};

#endif // REINE_H
