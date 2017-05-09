#ifndef ENEMY_H
#define ENEMY_H

#include "Game\Animation.h"

#define ENEMY_SIZE_X 2.f
#define ENEMY_SIZE_Y 2.f
#define ENEMY_SIZE_Z 1.f
#define ENEMY_DENSITY 60.f
#define ENEMY_FRICTION 0.0f
#define ENEMY_VEL_X 2500.f  //20000.f
#define ENEMY_VEL_Y 50000.f

#define ENEMY_MAX_VEL_X 2.5f
#define ENEMY_MAX_VEL_Y 20.f

class Enemy: public Animation
{
public:
	Enemy();
	Enemy(const Enemy& other);
	~Enemy();

	bool Start(std::string modelName, const MaterialManager::Material* material, b2World* world);
	void Update(GLint deltaT, b2Vec2 playerPos);

	////////////////////////////////////////////////////////////
	// \brief Gets input from user and moves accordingly
	////////////////////////////////////////////////////////////
	void Movement(b2Vec2 playerPos);
};

#endif // !ENEMY_H