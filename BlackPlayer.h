#ifndef JOUEURNOIR_H
#define JOUEURNOIR_H

#include "Player.h"

class BlackPlayer : public Player
{
    public:

        BlackPlayer();

        BlackPlayer(std::vector<std::string> listPieces);

        virtual ~BlackPlayer();

        BlackPlayer *clone();

        bool isWhite() const;

};

#endif // JOUEURNOIR_H
