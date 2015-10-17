#ifndef TOUR_H
#define TOUR_H

#include "Piece.h"


class Tour : public Piece
{
    public:

    Tour(int x, int y, bool white);

    virtual ~Tour();

    virtual char typePiece();

    Tour *Clone();

    std::vector<Case> mouvementsPossible(Echiquier *e);
};

#endif // TOUR_H
