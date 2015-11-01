#include "Knight.h"

Knight::Knight(int x, int y, bool white):Piece(x,y,white)
{
    if(m_white)
        spritePiece.setTextureRect(sf::IntRect(60, 60, 60, 60));
    else
        spritePiece.setTextureRect(sf::IntRect(0, 60, 60, 60));
};

Knight::~Knight() {};

Knight *Knight::clone()
{
    return new Knight(*this);
};

char Knight::typePiece()
{
    if(m_white)
        return 'C';
    else
        return 'c';
};

std::vector<Square> Knight::availableMovements(Chessboard *e)
{
    std::vector<Square> allMoves;
    std::vector<Square> listeCase;

    allMoves.push_back(Square(x() + 1 ,y() + 2));
    allMoves.push_back(Square(x() - 1 ,y() + 2));
    allMoves.push_back(Square(x() + 2 ,y() - 1));
    allMoves.push_back(Square(x() + 2 ,y() + 1));
    allMoves.push_back(Square(x() + 1 ,y() - 2));
    allMoves.push_back(Square(x() - 1 ,y() - 2));
    allMoves.push_back(Square(x() - 2 ,y() + 1));
    allMoves.push_back(Square(x() - 2 ,y() - 1));

    for (unsigned int i=0; i<allMoves.size(); i++)
    {
        int dx=allMoves[i].x;
        int dy=allMoves[i].y;

        if(Utility::inChessboard(dx,dy))
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
