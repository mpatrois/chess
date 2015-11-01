#ifndef ROI_H
#define ROI_H

#include "Piece.h"


class Roi : public Piece
{
    private:
    bool moved;

    Piece *tourDroite;
    Piece *tourGauche;

    public:

        Roi(int x, int y, bool white);

        virtual ~Roi();

        virtual char typePiece();

        Roi *Clone();

        std::vector<Case> mouvementsPossible(Echiquier *e);

        bool hadMove();

        void move( int x, int y );

//        void setTour(Piece* trDrte,Piece* trGche);
};

#endif // ROI_H
