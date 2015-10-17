#include "Tour.h"
#include "Echiquier.h"

Tour::Tour(int x, int y, bool white):Piece(x,y,white)
{
    if(m_white)
        spritePiece.setTextureRect(sf::IntRect(60, 180, 60, 60));
    else
        spritePiece.setTextureRect(sf::IntRect(0, 180, 60, 60));
};

Tour::~Tour() {};

char Tour::typePiece()
{
    if(m_white)
        return 'T';
    else
        return 't';
};

Tour *Tour::Clone()
{
    return new Tour(*this);
};

std::vector<Case> Tour::mouvementsPossible(Echiquier *e)
{
    std::vector<Case> listeCase;
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
    return listeCase;
}
