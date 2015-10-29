#ifndef FOU_H
#define FOU_H

#include "Piece.h"

class Bishop : virtual public Piece
{
public:
	Bishop();
	Bishop(int x, int y, bool white);
	virtual ~Bishop(){};

	virtual bool mouvementValide(Chessboard & e, int x, int y);
	virtual char getChar() const;
  	virtual std::string toString() const;
};

#endif
