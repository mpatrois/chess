#ifndef PION_H
#define PION_H

#include "Piece.h"

class Echiquier;

class Pion : public Piece
{
private:
	bool premierMouvement;
public:
	Pion(int x, int y, bool white);
	
	void move(int x, int y);
	void hasPassedTheFirstMove();
	virtual bool mouvementValide(Echiquier & e, int x, int y);
	virtual char getChar() const;
	virtual std::string toString() const;
	
};

#endif