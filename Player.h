#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include "Knight.h"
#include "Queen.h"
#include "Rook.h"
#include "Pawn.h"
#include "King.h"
#include "Bishop.h"
#include "Chessboard.h"


class Player
{
protected:
	std::vector<Piece*> m_pieces;
	bool m_white;

public:
	Player();
	virtual ~Player();

	bool placeEveryPiecesOn(Chessboard *ec);
	bool alreadyHasAPiece(Piece *p) const;

	virtual std::string toString() const = 0;
};

#endif
