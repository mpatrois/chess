#ifndef WHITE_PLAYER_H
#define WHITE_PLAYER_H

#include "Player.h"

class WhitePlayer : public Player
{
public:
	WhitePlayer();
	virtual ~WhitePlayer();

	std::string toString() const;
};

#endif
