#ifndef ROI_H
#define ROI_H

#include "Piece.h"


class Roi : public Piece
{
    public:

        Roi(int x, int y, bool white);

        virtual ~Roi();

        virtual char typePiece();

        Roi *Clone();

        std::vector<Case> mouvementsPossible(Echiquier *e);
};

#endif // ROI_H
