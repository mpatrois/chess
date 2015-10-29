#ifndef PION_H
#define PION_H

#include "Piece.h"

class Chessboard;

class Pawn : public Piece
{
private:
	bool premierMouvement;
	
public:
	Pawn(int x, int y, bool white);

	void move(int x, int y);
	void hasPassedTheFirstMove();
	virtual bool mouvementValide(Chessboard & e, int x, int y);
	virtual char getChar() const;
	virtual std::string toString() const;

};

#endif
