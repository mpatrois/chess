#ifndef REINE_H
#define REINE_H

#include "Piece.h"
#include "Utils.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public  Bishop, public Rook
{
public:
	Queen(bool white);
	virtual ~Queen(){};

	virtual bool mouvementValide(Chessboard & e, int x, int y);
	virtual char getChar() const;
	virtual std::string toString() const;
};

#endif
