#ifndef PLAYER_H
#define PLAYER_H

#include "Animation.h"

#define PLAYER_SIZE_X 2.f
#define PLAYER_SIZE_Y 2.f
#define PLAYER_SIZE_Z 1.f
#define PLAYER_MASS 70.f
#define PLAYER_FRICTION 0.5f
#define PLAYER_VEL_X 50000.f
#define PLAYER_VEL_Y 100000.f

#define PLAYER_MAX_VEL_X 40.f
#define PLAYER_MAX_VEL_Y 40.f

class Player : public Animation
{
public:
	Player();
	Player(const Player& other);
	~Player();

	bool Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, b2World* world);
	void Update(GLint deltaT);

	//Test-variable


	////////////////////////////////////////////////////////////
	// \brief Gets input from user and moves accordingly
	////////////////////////////////////////////////////////////
	void Movement();
	
	b2Body* getBody();

	glm::vec2 getPlayerPosAsGLM();
};

#endif // !PLAYER_H
