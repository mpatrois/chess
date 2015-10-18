#ifndef TOUR_H
#define TOUR_H

#include "Piece.h"
#include "Utils.h"

class Tour : virtual public Piece
{
public:
	Tour();
	Tour(int x, int y, bool white);
	virtual ~Tour(){};

  virtual bool mouvementValide(Echiquier & e, int x, int y);
	virtual char getChar() const;
	virtual std::string toString() const;
};

#endif
