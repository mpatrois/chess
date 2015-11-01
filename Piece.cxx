/**
 * Mise en oeuvre de Piece.h
 *
 * @file Piece.cxx
 */

// A besoin de la declaration de la classe
#include "Player.h"

sf::Texture Piece::texturePiece=sf::Texture();

Piece::Piece()
{}

Piece::Piece(int x,int y,bool white)
{
    m_x=x;
    m_y=y;
    m_white=white;
    spritePiece= sf::Sprite(texturePiece);
}

Piece::Piece(const Piece &p)
{
    m_x = p.m_x;
    m_y = p.m_y;
    m_white = p.m_white;
    spritePiece= sf::Sprite(texturePiece);
}
Piece::~Piece()
{

}

void Piece::move( int x, int y ,Chessboard *e)
{
    Piece *pieceAdverse=e->getPiece(x,y);

    if(pieceAdverse!=NULL)
    {
        Player *opponent=e->getAdverse(m_white);
        opponent->loosePiece(pieceAdverse);
        e->removePiece(x,y);
    };

    e->removePiece(m_x,m_y);

    m_x = x;
    m_y = y;

    e->put(this);
}

int Piece::x()
{
    return m_x;
}

int Piece::y()
{
    return m_y;
}

bool Piece::isWhite()
{
    return m_white;
}

bool Piece::isBlack()
{
    return !m_white;
}

void Piece::display()
{
    std::cout << m_x << " " <<m_y << " ";

    if(isWhite())
    {
        std::cout << "B";
    }
    else
    {
        std::cout << "N";
    }

    std::cout << std::endl;
}
