#ifndef PLAYER_H
#define PLAYER_H

#include "Animation.h"
#include <SDL.h>
#include "../ProjectileHandler.h"
#include "../Enemy.h"

#define PLAYER_SIZE_X 2.f
#define PLAYER_SIZE_Y 2.f
#define PLAYER_SIZE_Z 1.f
#define PLAYER_MASS 70.f
#define PLAYER_FRICTION 0.01f
#define PLAYER_VEL_X 8000.f
#define PLAYER_VEL_Y 3250.f

#define PLAYER_MAX_VEL_X 4.5f
#define PLAYER_MAX_VEL_Y 20.f

// XBOX CONTROLLER
#define CONTROLLER_ON true
#define BTN_A 0
#define BTN_B 1
#define BTN_X 2
#define BTN_Y 3
#define BTN_LB 4
#define BTN_RB 5
#define BTN_BACK 6
#define BTN_START 7
#define BTN_LT 8
#define BTN_RT 9
#define BTN_10 10
#define BTN_11 11

class Player : public Animation
{
	
private:
	//The ProjectileHandler for the player
	ProjectileHandler myProjectileHandler;
	//variable & function for cursor
	SDL_Cursor* cursor;
	void initiateCursor();
private:
	//Vacuum* vac;


	bool checkValue;
public:
	Player();
	Player(b2World *world, GLuint shader, glm::vec2 getPlayerPosAsGLM());
	Player(const Player& other);
	~Player();

	bool Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, b2World* world);
	//void Update(GLint deltaT);
	bool Start(std::string modelName, const MaterialManager::Material* material, b2World* world);
	//void Update(GLint deltaT);
	void Update(GLint deltaT, b2World* world, glm::vec2 pos);
	//bool Start(std::string modelName, const MaterialManager::Material* material, const MaterialManager::Material* material2, b2World* world);
	//void Update(GLint deltaT);

	void InputTesting();
	void InputKeyboard();
	void InputController();
	
	b2Body* getBody();
	//Vacuum* getVac();

	//glm::vec2 getPlayerPosAsGLM();
	glm::vec2 getPlayerPosAsGLM();
	/*bool addPlayerProjectiles();
	void setCheckForProjectilePickUp(bool checkValue);
	bool getCheckValue()const;*/
private:
	bool hasJumped;
};
#endif // !PLAYER_H
