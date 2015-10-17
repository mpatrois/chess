#include "Reine.h"
#include "Echiquier.h"

Reine::Reine(int x, int y, bool white):Piece(x,y,white)
{
    if(m_white)
        spritePiece.setTextureRect(sf::IntRect(60, 240, 60, 60));
    else
        spritePiece.setTextureRect(sf::IntRect(0, 240, 60, 60));
};

Reine::~Reine() {};

char Reine::typePiece()
{
    if(m_white)
        return 'Q';
    else
        return 'q';
};

Reine *Reine::Clone()
{
    return new Reine(*this) ;
};

std::vector<Case> Reine::mouvementsPossible(Echiquier *e)
{
    std::vector<Case> listeCase;

    for (int vx=-1; vx<2; vx++)
        for (int vy=-1; vy<2; vy++)
        {
            int dx=x()+vx;
            int dy=y()+vy;

            bool stop=false;

            if(vx!=0 || vy!=0)
            {
                while(dx < 8 && dy < 8 && dx > -1 && dy > -1 && !stop )
                {
                    if(e->getPiece(dx,dy)==NULL)
                    {
                        Case c(dx,dy);

                        listeCase.push_back(c);
                    }
                    else
                    {
                        if(e->getPiece(dx,dy)->isWhite()!=m_white)
                        {
                            Case c(dx,dy);

                            listeCase.push_back(c);
                        }
                        stop=true;
                    }
                    dx+=vx;
                    dy+=vy;
                }
            }
        }
    return listeCase;
}
