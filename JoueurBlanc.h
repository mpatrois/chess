#ifndef JOUEURBLANC_H
#define JOUEURBLANC_H

#include "Joueur.h"
#include <sstream>
#include "util.h"



class JoueurBlanc : public Joueur
{
    public:

    JoueurBlanc();

    JoueurBlanc(std::vector<std::string> listPieces);

    virtual ~JoueurBlanc();

    bool isWhite();

    JoueurBlanc *Clone();
};

#endif // JOUEURBLANC_H
