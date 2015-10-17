#ifndef CAVALIER_H
#define CAVALIER_H

#include "Piece.h"


class Cavalier : public Piece
{
    public:

    Cavalier(int x, int y, bool white);

    Cavalier *Clone();

    virtual ~Cavalier();

    virtual char typePiece();

    std::vector<Case> mouvementsPossible(Echiquier *e);
};

#endif // CAVALIER_H
