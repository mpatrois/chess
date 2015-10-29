#ifndef TOUR_H
#define TOUR_H

#include "Piece.h"
#include "Utils.h"

class Rook : virtual public Piece
{
public:
	Rook();
	Rook(int x, int y, bool white);
	virtual ~Rook(){};

  virtual bool mouvementValide(Chessboard & e, int x, int y);
	virtual char getChar() const;
	virtual std::string toString() const;
};

#endif
