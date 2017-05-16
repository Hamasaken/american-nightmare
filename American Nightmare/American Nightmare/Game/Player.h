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
public:
	Player();
	Player(const Player& other);
	~Player();

	bool Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, b2World* world);
	void Update(GLint deltaT);

	void InputTesting();
	void InputKeyboard();
	void InputController();
	
	b2Body* getBody();

	glm::vec2 getPlayerPosAsGLM();
};

#endif // !PLAYER_H
