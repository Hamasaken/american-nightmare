#ifndef PLAYER_H
#define PLAYER_H

#include "Animation.h"

#define PLAYER_SIZE_X 2.f
#define PLAYER_SIZE_Y 2.f
#define PLAYER_SIZE_Z 1.f
#define PLAYER_DENSITY 60.f
#define PLAYER_FRICTION 0.0f
#define PLAYER_VEL_X 20000.f
#define PLAYER_VEL_Y 50000.f

#define PLAYER_MAX_VEL_X 20.f
#define PLAYER_MAX_VEL_Y 20.f

class Player : public Animation
{
public:
	Player();
	Player(const Player& other);
	~Player();

	bool Start(std::string modelName, const MaterialManager::Material* material, b2World* world);
	void Update(GLint deltaT);

	Entity myEntity;
	////////////////////////////////////////////////////////////
	// \brief Gets input from user and moves accordingly
	////////////////////////////////////////////////////////////
	void Movement();
};

#endif // !PLAYER_H
