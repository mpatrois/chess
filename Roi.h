#ifndef ROI_H
#define ROI_H

#include "Piece.h"
#include "Utils.h"

class Roi : public Piece 
{
public:
	Roi(bool white);

  	virtual bool mouvementValide(Echiquier & e, int x, int y);
  	bool isNotEchec(Echiquier & e, int x, int y);
	virtual char getChar() const;
  	virtual std::string toString() const;
};

#endif