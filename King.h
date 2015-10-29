#ifndef ROI_H
#define ROI_H

#include "Piece.h"
#include "Utils.h"

class King : public Piece 
{
public:
	King(bool white);

  	virtual bool mouvementValide(Chessboard & e, int x, int y);
  	bool isNotEchec(Chessboard & e, int x, int y);
	virtual char getChar() const;
  	virtual std::string toString() const;
};

#endif