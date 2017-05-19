#ifndef PLAYER_H
#define PLAYER_H

#include "Animation.h"

// KEYS DEFAULTS
#define KEY_LEFT sf::Keyboard::Key::A
#define KEY_RIGHT sf::Keyboard::Key::D
#define KEY_JUMP sf::Keyboard::Key::W
#define KEY_DASH sf::Keyboard::Key::LControl
#define KEY_HOVER sf::Keyboard::Key::Space

// DEFAULT VALUES
#define PLAYER_SIZE_X 2.f
#define PLAYER_SIZE_Y 2.f
#define PLAYER_SIZE_Z 1.f
#define PLAYER_MASS 70.f
#define PLAYER_FRICTION 0.01f
#define PLAYER_VEL_X 8000.f
#define PLAYER_VEL_Y 3250.f
#define PLAYER_MAX_VEL_X 15.0f
#define PLAYER_MAX_VEL_Y 20.f
#define PLAYER_DASH_VEL 22500.f
#define PLAYER_DASH_CD 1000.f
#define PLAYER_HOVER_POWER 3500.f
#define PLAYER_HP 6

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
	enum Direction { LEFT, RIGHT, STOPPED };
public:
	Player();
	Player(const Player& other);
	~Player();

	bool Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, b2World* world);
	void Update(GLint deltaT);

	void RebindKeys(sf::Keyboard::Key key_left, sf::Keyboard::Key key_right, sf::Keyboard::Key key_jump, sf::Keyboard::Key key_hover, sf::Keyboard::Key key_dash);

	float& getHP();
	bool getIsHovering();
	bool getIsDashing();
	b2Body* getBody();
	glm::vec2 getPlayerPosAsGLM();
private:

	// Interactions with player
	void Walk(Direction dir);	//< Walking in a direction
	void Jump();				//< Jumping
	void Dash();				//< Dash ability
	void Hover();				//< Hover ability

	// Input from user
	void InputTesting();		//< Rotation & Scale on Player model
	void InputMouse();			//< Mouse input
	void InputKeyboard();		//< Key input
	void InputController();		//< Xbox One controller input

	float hp;
	GLfloat dashCooldown;		//< Dash ability cooldown
	bool hasJumped;				//< If the player have jumped or not
	bool hasDashed;				//< If the player have dashed or not
	bool isDashing;				//< If the player is currently dashing
	bool isHovering;			//< If the player is currently hovering

	// Rebindable keys
	sf::Keyboard::Key key_left;
	sf::Keyboard::Key key_right;
	sf::Keyboard::Key key_jump;
	sf::Keyboard::Key key_hover;
	sf::Keyboard::Key key_dash;
};

#endif // !PLAYER_H
