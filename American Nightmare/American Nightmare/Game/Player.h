#ifndef PLAYER_H
#define PLAYER_H

#include "Animation.h"

class Player : public Animation
{
public:
	Player();
	Player(const Player& other);
	~Player();

	bool Start(std::string modelName, const MaterialManager::Material* material, b2World& world, float x = 0.f, float y = 0.f, bool isDynamic = false);
	void Update(GLint deltaT);

	//Test-variable


	////////////////////////////////////////////////////////////
	// \brief Gets input from user and moves accordingly
	////////////////////////////////////////////////////////////
	void Movement();

private:
	glm::vec2 velocity;
};

#endif // !PLAYER_H
