#include "Echiquier.h"
#include "Cavalier.h"
#include "util.h"

Cavalier::Cavalier(int x, int y, bool white):Piece(x,y,white)
{
    if(m_white)
        spritePiece.setTextureRect(sf::IntRect(60, 60, 60, 60));
    else
        spritePiece.setTextureRect(sf::IntRect(0, 60, 60, 60));
};

Cavalier::~Cavalier() {};

Cavalier *Cavalier::Clone()
{
    return new Cavalier(*this);
};

char Cavalier::typePiece()
{
    if(m_white)
        return 'C';
    else
        return 'c';
};

std::vector<Case> Cavalier::mouvementsPossible(Echiquier *e)
{
    std::vector<Case> allMoves;
    std::vector<Case> listeCase;

    allMoves.push_back(Case(x() + 1 ,y() + 2));
    allMoves.push_back(Case(x() - 1 ,y() + 2));
    allMoves.push_back(Case(x() + 2 ,y() - 1));
    allMoves.push_back(Case(x() + 2 ,y() + 1));
    allMoves.push_back(Case(x() + 1 ,y() - 2));
    allMoves.push_back(Case(x() - 1 ,y() - 2));
    allMoves.push_back(Case(x() - 2 ,y() + 1));
    allMoves.push_back(Case(x() - 2 ,y() - 1));

    for (unsigned int i=0; i<allMoves.size(); i++)
    {
        int dx=allMoves[i].x;
        int dy=allMoves[i].y;

        if(utility::inPlateau(dx,dy))
        {
            if(e->getPiece(dx,dy)==NULL)
            {
                listeCase.push_back(allMoves[i]);
            }
            else
            {
                if(e->getPiece(dx,dy)->isWhite()!=m_white)
                {
                    listeCase.push_back(allMoves[i]);
                }
            }
        }
    }
    return listeCase;
}
