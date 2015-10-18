#ifndef JOUEUR_BLANC_H
#define JOUEUR_BLANC_H

#include "Joueur.h"

class JoueurBlanc : public Joueur 
{
public:
	JoueurBlanc();
	virtual ~JoueurBlanc();

	std::string toString() const; 
};

#endif