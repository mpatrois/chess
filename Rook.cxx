#include "Rook.h"
#include "Chessboard.h"

Rook::Rook(int x, int y, bool white):Piece(x,y,white)
{
    if(m_white)
        rectPiece=sf::IntRect(60, 180, 60, 60);
    else
        rectPiece=sf::IntRect(0, 180, 60, 60);

    moved=false;
};

Rook::~Rook() {};

char Rook::typePiece()
{
    if(m_white)
        return 'T';
    else
        return 't';
};

Rook *Rook::clone()
{
    return new Rook(*this);
};

std::vector<Square> Rook::availableMovements(Chessboard *e)
{
    std::vector<Square> listeCase;
    for (int vx=-1; vx<2; vx++)
        for (int vy=-1; vy<2; vy++)
        {
            int dx=x()+vx;
            int dy=y()+vy;
            bool stop=false;

            if( (vx==0 && vy==1) || (vx==0 && vy==-1) || (vx==-1 && vy==0) ||(vx==1 && vy==0))
                while(dx < 8 && dy < 8 && dx > -1 && dy > -1 && !stop )
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
                        stop=true;
                    }
                    dx+=vx;
                    dy+=vy;
                }
        }
    return listeCase;
}

bool Rook::hadMove(){
    return moved;
}

void Rook::move( int x, int y,Chessboard *e)
{
    moved=true;
    Piece::move(x,y,e);
}
