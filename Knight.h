#ifndef CAVALIER_H
#define CAVALIER_H

#include "Piece.h"
#include "Utils.h"

class Knight : public Piece
{
public:
	Knight(int x, int y, bool white);
	
  	virtual bool mouvementValide(Chessboard & e, int x, int y);
	virtual char getChar() const;
  	virtual std::string toString() const;
};

#endif