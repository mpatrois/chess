#include "Fou.h"
#include "Echiquier.h"

Fou::Fou(int x, int y, bool white):Piece(x,y,white)
{
    if(m_white)
        spritePiece.setTextureRect(sf::IntRect(60, 120, 60, 60));
    else
        spritePiece.setTextureRect(sf::IntRect(0, 120, 60, 60));
};

Fou::~Fou() {};

char Fou::typePiece()
{
    if(m_white)
        return 'F';
    else
        return 'f';
};

Fou *Fou::Clone()
{
    return new Fou(*this) ;
};

std::vector<Case> Fou::mouvementsPossible(Echiquier *e)
{
    std::vector<Case> listeCase;
    for(int vx=-1; vx<2; vx++)
    {
        for(int vy=-1; vy<2; vy++)
        {
            if(vx!=0 && vy!=0)
            {
                int dx=x()+vx;
                int dy=y()+vy;
                bool stop=false;
                if(dx>-1 && dy>-1)
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
        }
    }
    return listeCase;
}
