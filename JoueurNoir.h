#ifndef JOUEURNOIR_H
#define JOUEURNOIR_H

#include "Joueur.h"

class JoueurNoir : public Joueur
{
    public:

    JoueurNoir();

    JoueurNoir(std::vector<std::string> listPieces);

    virtual ~JoueurNoir() {};

    JoueurNoir *Clone();

    bool isWhite();

};

#endif // JOUEURNOIR_H
