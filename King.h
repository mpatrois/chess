#ifndef ROI_H
#define ROI_H

#include "Piece.h"


class King : public Piece
{
    private:
    bool moved;

    Piece *tourDkingte;
    Piece *tourGauche;

    public:

        King(int x, int y, bool white);

        virtual ~King();

        virtual char typePiece();

        King *clone();

        std::vector<Case> mouvementsPossible(Chessboard *e);

        bool hadMove();

        void move( int x, int y,Chessboard *e);

//        void setRook(Piece* trDrte,Piece* trGche);
};

#endif // ROI_H