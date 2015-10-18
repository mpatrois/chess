#ifndef JOUEUR_NOIR_H
#define JOUEUR_NOIR_H

#include "Joueur.h"

class JoueurNoir : public Joueur 
{
public:
	JoueurNoir();
	virtual ~JoueurNoir();

	std::string toString() const; 
};

#endif