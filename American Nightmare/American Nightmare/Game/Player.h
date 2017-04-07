#ifndef PLAYER_H
#define PLAYER_H

#include "Object.h"

class Player : public Object
{
public:
	Player();
	Player(const Player& other);
	~Player();

	////////////////////////////////////////////////////////////
	// TEMPORARY, REMOVE THIS COMPLETLY AFTER LOAD MODEL IS IMPLEMENTED
	////////////////////////////////////////////////////////////
	bool Start(OpenGL* openGL, std::string modelName, std::string textureName);

	void Update();

	////////////////////////////////////////////////////////////
	// \brief Gets input from user and moves accordingly
	////////////////////////////////////////////////////////////
	void Movement();
};

#endif // !PLAYER_H
