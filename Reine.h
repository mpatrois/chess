#ifndef REINE_H
#define REINE_H

#include "Piece.h"
#include "Utils.h"
#include "Fou.h"
#include "Tour.h"

class Reine : public  Fou, public Tour
{
public:
	Reine(bool white);
	virtual ~Reine(){};

	virtual bool mouvementValide(Echiquier & e, int x, int y);
	virtual char getChar() const;
	virtual std::string toString() const;
};

#endif
