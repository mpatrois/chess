#include "Roi.h"
#include "Echiquier.h"

Roi::Roi(int x, int y, bool white):Piece(x,y,white)
{
    if(m_white)
        spritePiece.setTextureRect(sf::IntRect(60, 300, 60, 60));
    else
        spritePiece.setTextureRect(sf::IntRect(0, 300, 60, 60));

};

Roi::~Roi() {};

char Roi::typePiece()
{
    if(m_white)
        return 'R';
    else
        return 'r';
};

Roi *Roi::Clone()
{
    return new Roi(*this) ;
};

std::vector<Case> Roi::mouvementsPossible(Echiquier *e)
{
    std::vector<Case> listeCase;
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
                    }
                    dx+=vx;
                    dy+=vy;
                }
            }
        }
    return listeCase;
}
