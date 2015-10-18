#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>
#include <vector>

#include "Cavalier.h"
#include "Reine.h"
#include "Tour.h"
#include "Pion.h"
#include "Roi.h"
#include "Fou.h"
#include "Echiquier.h"


class Joueur
{
protected:
	std::vector<Piece*> m_pieces;
	bool m_white;
public:
	Joueur();
	virtual ~Joueur();

	bool placeEveryPiecesOn(Echiquier *ec);
	bool alreadyHasAPiece(Piece *p) const;

	virtual std::string toString() const = 0;
};

#endif
