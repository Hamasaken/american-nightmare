#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player : public Object
{
public:
	Player();
	Player(const Player& other);
	~Player();

	void Update();

	////////////////////////////////////////////////////////////
	// \brief Gets input from user and moves accordingly
	////////////////////////////////////////////////////////////
	void Movement();
};

#endif // !PLAYER_H
