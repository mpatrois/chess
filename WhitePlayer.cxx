#include <sstream>
#include "WhitePlayer.h"

using namespace std;

WhitePlayer::WhitePlayer() : Player()
{
	m_white = true;
	int x;

	for (x = 0; x < 8; x++)
		m_pieces[x] = new Pawn(x+1, 2, true);

	m_pieces[x++] = new Rook(1, 1, true);
	m_pieces[x++] = new Knight(2, 1, true);
	m_pieces[x++] = new Bishop(3, 1, true);
	m_pieces[x++] = new Bishop(6, 1, true);
	m_pieces[x++] = new Knight(7, 1, true);
	m_pieces[x++] = new Rook(8, 1, true);
	m_pieces[x++] = new Queen(true);
	m_pieces[x] = new King(true);
}

WhitePlayer::~WhitePlayer()
{}

string
WhitePlayer::toString() const
{
	stringstream stream;
	stream << "========= Player Blanc =========\n";
	stream << Player::toString();
	stream << "================================\n";

	return stream.str();
}
