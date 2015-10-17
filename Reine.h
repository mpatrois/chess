#ifndef REINE_H
#define REINE_H

#include "Piece.h"


class Reine : public Piece
{
    public:

        Reine(int x, int y, bool white);

        virtual ~Reine();

        Reine *Clone();

        virtual char typePiece();;

        std::vector<Case> mouvementsPossible(Echiquier *e);

};

#endif // REINE_H
