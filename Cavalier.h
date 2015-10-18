#ifndef CAVALIER_H
#define CAVALIER_H

#include "Piece.h"
#include "Utils.h"

class Cavalier : public Piece
{
public:
	Cavalier(int x, int y, bool white);
	
  	virtual bool mouvementValide(Echiquier & e, int x, int y);
	virtual char getChar() const;
  	virtual std::string toString() const;
};

#endif