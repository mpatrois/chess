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

        std::vector<Square> availableMovements(Chessboard *e);
        
        virtual char typePiece();
};

#endif // CAVALIER_H
