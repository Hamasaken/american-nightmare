#ifndef PLAYER_H
#define PLAYER_H

#include "Animation.h"

class Player : public Animation
{
public:
	Player();
	Player(const Player& other);
	~Player();

	void Update(GLint deltaT);

	////////////////////////////////////////////////////////////
	// \brief Gets input from user and moves accordingly
	////////////////////////////////////////////////////////////
	void Movement();

private:
	glm::vec2 velocity;
};

#endif // !PLAYER_H
