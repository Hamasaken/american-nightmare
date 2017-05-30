#ifndef ENEMY_H
#define ENEMY_H

#include "Game\Animation.h"

#define ENEMY_SIZE_X 2.f
#define ENEMY_SIZE_Y 2.f
#define ENEMY_SIZE_Z 1.f
#define ENEMY_MASS 70.f
#define ENEMY_FRICTION 0.20f
#define ENEMY_VEL_X 1000.f  //20000.f
#define ENEMY_VEL_Y 500.f

#define ENEMY_UPDATE_DISTANCE 20

#define ENEMY_MAX_VEL_X 2.25f
#define ENEMY_MAX_VEL_Y 20.f

#define ROLLER_VEL_X 375.f  //20000.f
#define ROLLER_VEL_Y 100.f
#define ROLLER_MAX_VEL_X 9.f
#define ROLLER_MAX_VEL_Y 10.f

class Enemy: public Animation
{
public:
	Enemy();
	Enemy(const Enemy& other);
	~Enemy();

	virtual bool Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, b2World* world);
	void Update(GLint deltaT, b2Vec2 playerPos, bool playerAlive);

	Entity myEntity;
	////////////////////////////////////////////////////////////
	// \brief Gets input from user and moves accordingly
	////////////////////////////////////////////////////////////
	virtual void Movement(b2Vec2 playerPos);
	int hp;
	float getDamage();
	void TakeDamage(float dmg);
	bool isDead;
	bool getIsDead()const;

protected:
	float damage;
	b2Body* getBody();
};

class ZombieRoller : public Enemy
{
public:
	bool Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, b2World* world);
	void Movement(b2Vec2 playerPos);
};

#endif // !ENEMY_H
