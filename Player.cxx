#include <sstream>
#include "Player.h"

using namespace std;

Player::Player(): m_pieces(18)
{}

Player::~Player()
{
	for (int i = 0; i < m_pieces.size(); ++i)
		if(m_pieces[i] != NULL)
			delete m_pieces[i];
}

bool
Player::placeEveryPiecesOn(Chessboard *ec)
{
	for (int i = 0; i < m_pieces.size(); ++i)
		if(ec->placer(m_pieces[i]) != true)
			return false;
}

bool
Player::alreadyHasAPiece(Piece *p) const
{
	for (int i = 0; i < m_pieces.size(); ++i)
		if(m_pieces[i]->isAtTheSamePlace(*p))
			return true;

	return false;
}

string
Player::toString() const
{
	stringstream stream;

	for(int i = 0; i < m_pieces.size(); i++)
		stream << m_pieces[i]->toString();

	return stream.str();
}
