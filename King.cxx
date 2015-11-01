#include "Rook.h"
#include "King.h"
#include "Chessboard.h"

King::King(int x, int y, bool white):Piece(x,y,white)
{
    if(m_white)
        spritePiece.setTextureRect(sf::IntRect(60, 300, 60, 60));
    else
        spritePiece.setTextureRect(sf::IntRect(0, 300, 60, 60));

    moved=false;

};

King::~King() {};

char King::typePiece()
{
    if(m_white)
        return 'R';
    else
        return 'r';
};

King *King::clone()
{
    return new King(*this) ;
};

std::vector<Square> King::availableMovements(Chessboard *e)
{
    std::vector<Square> listeCase;
    for (int vx=-1; vx<2; vx++)
        for (int vy=-1; vy<2; vy++)
        {
            int dx=x()+vx;
            int dy=y()+vy;

            if(vx!=0 || vy!=0)
            {
                if(dx < 8 && dy < 8 && dx > -1 && dy > -1)
                {
                    if(e->getPiece(dx,dy)==NULL)
                    {
                        Square c(dx,dy);
                        listeCase.push_back(c);
                    }
                    else
                    {
                        if(e->getPiece(dx,dy)->isWhite()!=m_white)
                        {
                            Square c(dx,dy);
                            listeCase.push_back(c);
                        }
                    }
                    dx+=vx;
                    dy+=vy;
                }
            }
        }

//        if(!hadMove())
//        {
//            Player *opponent=e->getAdverse(isWhite());
////            std::cout << opponent->isWhite();
//            Rook *tGauche=dynamic_cast<Rook*>(e->getPiece(0,y()));
//
//            if(tGauche!=nullptr && !tGauche->hadMove())
//            {
//                if(e->getPiece(1,y())==NULL && e->getPiece(2,y())==NULL){
////
//                        if(!opponent->viseCase(0,y(),e) &&
//                           !opponent->viseCase(2,y(),e) &&
//                           !opponent->viseCase(3,y(),e) &&
//                           !opponent->viseCase(4,y(),e))
//                        {
////                            listeCase.push_back(Square(1,y()));
//                        }
//                }
//            }
//
//            Rook *tDkingte=dynamic_cast<Rook*>(e->getPiece(7,y()));
//
//            if(tDkingte!=nullptr && !tDkingte->hadMove())
//            {
//                if(e->getPiece(4,y())==NULL && e->getPiece(5,y())==NULL && e->getPiece(6,y())==NULL){
//
//
//                        if(!opponent->viseCase(7,y(),e) &&
//                           !opponent->viseCase(5,y(),e) &&
//                           !opponent->viseCase(4,y(),e) &&
//                           !opponent->viseCase(3,y(),e))
//                        {
//                            listeCase.push_back(Square(5,y()));
//                        }
//                    }
//
//            }
//        }
//    return listeCase;
    return listeCase;
}

bool King::hadMove(){
    return moved;
}

void King::move( int x, int y,Chessboard *e )
{
    moved=true;
    Piece::move(x,y,e);
}
