#include "Pion.h"
#include "Echiquier.h"
#include "util.h"

Pion::Pion(int x,int y,bool white):Piece(x,y,white)
{
    if(m_white)
        spritePiece.setTextureRect(sf::IntRect(60, 0, 60, 60));
    else
        spritePiece.setTextureRect(sf::IntRect(0, 0, 60, 60));

    nbMove=0;
};

Pion::~Pion() {};

char Pion::typePiece()
{
    if(m_white)
        return 'P';
    else
        return 'p';
};

Pion *Pion::Clone()
{
    return new Pion(*this);
};

std::vector<Case> Pion::mouvementsPossible(Echiquier *e)
{
    std::vector<Case> listeCase;

    int sens=-1;

    if(!m_white)
        sens=1;

    if(e->getPiece(x(),y()+1*sens)==NULL)
    {
        Case c(x(),y()+1*sens);

        listeCase.push_back(c);

        if(((y()==6 && sens==-1) || (y()==1 && sens==1)) && e->getPiece(x(),y()+2*sens)==NULL )
        {
            Case c(x(),y()+2*sens);
            listeCase.push_back(c);
        }
    }

    if(e->getPiece(x()+1,y()+1*sens)!=NULL)
    {
        if(e->getPiece(x()+1,y()+1*sens)->isWhite()!=m_white)
        {
            Case c(x()+1,y()+1*sens);
            listeCase.push_back(c);
        }
    }
    if(e->getPiece(x()-1,y()+1*sens)!=NULL)
    {
        if(e->getPiece(x()-1,y()+1*sens)->isWhite()!=m_white)
        {
            Case c(x()-1,y()+1*sens);
            listeCase.push_back(c);
        }
    }
    return listeCase;
};

int Pion::getNbMove(){
    return nbMove;
}

void Pion::move( int x, int y ){
    nbMove++;
    Piece::move(x,y);
}
