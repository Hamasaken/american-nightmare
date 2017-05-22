#ifndef ENEMY_H
#define ENEMY_H

#include "Game\Animation.h"

#define ENEMY_SIZE_X 2.f
#define ENEMY_SIZE_Y 2.f
#define ENEMY_SIZE_Z 1.f
#define ENEMY_MASS 20.f
#define ENEMY_FRICTION 0.25f
#define ENEMY_VEL_X 2500.f  //20000.f
#define ENEMY_VEL_Y 50000.f

#define ENEMY_UPDATE_DISTANCE 18

#define ENEMY_MAX_VEL_X 4.25f
#define ENEMY_MAX_VEL_Y 20.f

class Enemy: public Animation
{
public:
	Enemy();
	Enemy(const Enemy& other);
	~Enemy();

	bool Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, b2World* world);
	void Update(GLint deltaT, b2Vec2 playerPos, bool playerAlive);

	Entity myEntity;
	////////////////////////////////////////////////////////////
	// \brief Gets input from user and moves accordingly
	////////////////////////////////////////////////////////////
	void Movement(b2Vec2 playerPos);

	float getDamage();

private:
	float damage;
	b2Body* getBody();
};

#endif // !ENEMY_H
