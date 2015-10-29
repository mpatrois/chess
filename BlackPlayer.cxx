#include <sstream>
#include "BlackPlayer.h"

using namespace std;

BlackPlayer::BlackPlayer() : Player()
{
	m_white = false;
	int x;

	for (x = 0; x < 8; x++)
		m_pieces[x] = new Pawn(x+1, 7, false);

	m_pieces[x++] = new Rook(1, 8, false);
	m_pieces[x++] = new Rook(8, 8, false);
	m_pieces[x++] = new Knight(7, 8, false);
	m_pieces[x++] = new Knight(2, 8, false);
	m_pieces[x++] = new Bishop(6, 8, false);
	m_pieces[x++] = new Bishop(3, 8, false);
	m_pieces[x++] = new Queen(false);
	m_pieces[x] = new King(false);

}

BlackPlayer::~BlackPlayer()
{}

string
BlackPlayer::toString() const
{
	stringstream stream;
	stream << "========= Player Noir =========\n";
	stream << Player::toString();
	stream << "================================\n";

	return stream.str();
}
