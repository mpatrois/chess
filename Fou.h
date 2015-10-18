#ifndef FOU_H
#define FOU_H

#include "Piece.h"

class Fou : virtual public Piece
{
public:
	Fou();
	Fou(int x, int y, bool white);
	virtual ~Fou(){};

	virtual bool mouvementValide(Echiquier & e, int x, int y);
	virtual char getChar() const;
  	virtual std::string toString() const;
};

#endif
