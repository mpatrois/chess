#ifndef BLACK_PLAYER_H
#define BLACK_PLAYER_H

#include "Player.h"

class BlackPlayer : public Player
{
public:
	BlackPlayer();
	virtual ~BlackPlayer();

	virtual std::string toString() const;
};

#endif
