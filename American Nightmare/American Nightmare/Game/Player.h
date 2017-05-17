#ifndef PLAYER_H
#define PLAYER_H

#include "Animation.h"
#include <SDL.h>
#include "../ProjectileHandler.h"
#include "../Enemy.h"

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
	
private:
	//The ProjectileHandler for the player
	ProjectileHandler myProjectileHandler;
	//variable & function for cursor
	SDL_Cursor* cursor;
	void initiateCursor();

	bool checkValue;
public:
	Player();
	Player(b2World *world, GLuint shader, glm::vec2 getPlayerPosAsGLM());
	Player(const Player& other);
	~Player();

	bool Start(std::string modelName, const MaterialManager::Material* material, b2World* world);
	//void Update(GLint deltaT);
	void Update(GLint deltaT, b2World* world, glm::vec2 pos);

	////////////////////////////////////////////////////////////
	// \brief Gets input from user and moves accordingly
	////////////////////////////////////////////////////////////
	void Movement();
	
	b2Body* getBody();

	glm::vec2 getPlayerPosAsGLM();
	bool addPlayerProjectiles();
	void setCheckForProjectilePickUp(bool checkValue);
	bool getCheckValue()const;
};

#endif // !PLAYER_H
