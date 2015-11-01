#ifndef JOUEURBLANC_H
#define JOUEURBLANC_H

#include "Player.h"

class WhitePlayer : public Player
{
    public:

    WhitePlayer();

    WhitePlayer(std::vector<std::string> listPieces);

    virtual ~WhitePlayer();

    WhitePlayer *clone();

    bool isWhite() const;
};

#endif // JOUEURBLANC_H
