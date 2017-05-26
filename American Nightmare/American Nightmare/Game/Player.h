#ifndef PLAYER_H
#define PLAYER_H

#include "Animation.h"
#include <SDL.h>
#include "../ProjectileHandler.h"
#include "Particle\ParticleManager.h"
#include "../SoundManager.h"
#include "Camera.h"
#include "../Enemy.h"
#include "../vacuum.h"

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
#define PLAYER_FRICTION 1.f
#define PLAYER_VEL_X 100000.f
#define PLAYER_VEL_Y 3000.f
#define PLAYER_MAX_VEL_X 7.0f
#define PLAYER_MAX_VEL_Y 18.f
#define PLAYER_HP 6
#define PLAYER_INVULNERABILITY_TIME 2.f

// Power 
#define PLAYER_POWER_MAX 100.f
#define PLAYER_POWER_RECHARGE 25.f

// Hover
#define PLAYER_POWER_COST_HOVER 25.f
#define PLAYER_HOVER_POWER 3500.f

// Dash
#define PLAYER_POWER_COST_DASH 25.f
#define PLAYER_DASH_VEL 12500.f
#define PLAYER_DASH_CD 1000.f

// Shockwave
#define PLAYER_SHOCKWAVE_CD 1500.f
#define PLAYER_POWER_COST_SHOCKWAVE 80.f
#define PLAYER_SHOCKWAVE_POWER 12500.f

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
	
	//Variables for handling projectile/Weapon
	int nrOfProjectiles;
	const int CAP = 10;

	//variable & function for cursor
	SDL_Cursor* cursor;
	void initiateCursor();

	Vacuum* vac;

	// Interactions with player
	void Walk(Direction dir);			//< Walking in a direction
	void Jump();						//< Jumping
	void Dash(sf::Keyboard::Key inKey);	//< Dash ability
	void Hover(GLint deltaT);			//< Hover ability
	void Shockwave();

	//< Input from user
	void InputTesting();					//< Rotation & Scale on Player model
	void InputMouse();						//< Mouse input
	void InputKeyboard(GLint deltaT);		//< Key input
	void InputController(GLint deltaT);		//< Xbox One controller input

	bool isDead;				//< If the player is dead or not
	float hp;					//< The amount of hp the player have
	GLfloat power;				//< Players resource for dashing and hovering etc
	GLfloat dashCooldown;		//< Dash ability cooldown
	GLfloat shockwaveCooldown;	//< Dash ability cooldown
	bool hasJumped;				//< If the player have jumped or not
	bool hasDashed;				//< If the player have dashed or not
	bool isDashing;				//< If the player is currently dashing
	bool isHovering;			//< If the player is currently hovering
	GLfloat invulTime;			//< Player invulnerability timer after being hit
	Enemy* contactWithEnemy;	//< If player is in contact with an enemy;
	glm::vec3 startPosition;	//< The save station or the starting point on level

	ParticleManager* particleManager;
	SoundManager* soundManager;
	Camera* camera;

	//< Rebindable keys 
	sf::Keyboard::Key key_left;
	sf::Keyboard::Key key_right;
	sf::Keyboard::Key key_jump;
	sf::Keyboard::Key key_hover;
	sf::Keyboard::Key key_dash;
	
public:
	Player();
	//Player(const MeshManager::Mesh* mesh, const MaterialManager::Material * material, b2World *world);
	Player(const Player& other);
	~Player();
	 
	bool Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, const MaterialManager::Material* material2, b2World* world, ParticleManager* particleManager, SoundManager* soundManager, Camera* camera);
	//bool Start(std::string modelName, const MaterialManager::Material* material, b2World* world);
	void Update(GLint deltaT, b2World* world);
	//bool Start(std::string modelName, const MaterialManager::Material* material, const MaterialManager::Material* material2, b2World* world);

	void Reset();
	void RebindKeys(sf::Keyboard::Key key_left, sf::Keyboard::Key key_right, sf::Keyboard::Key key_jump, sf::Keyboard::Key key_hover, sf::Keyboard::Key key_dash);
	void TakeDamage(float dmg);
	bool getIsDead();

	float& getHP();
	float& getPower();
	float& getNrOfProjectiles();

	bool getIsHovering();
	bool getIsDashing();
	b2Body* getBody();
	glm::vec2 getPlayerPosAsGLM();
	void setStartingPosition(glm::vec3 position);
	void setInvulTime(GLfloat invulTime);
	GLfloat getInvulTime();
	void setContactWithEnemy(Enemy* contact);
	Enemy* getContactWithEnemy();
	Vacuum* getVac();
	void setHasJumped(bool hasJumped);
	bool getHasJumped();
	bool getAmmoFull();
	
	bool addPlayerProjectiles();
	bool getCanShoot();

	void addNrOfProjectiles();
	void decreaseNrOfProjectiles();
};
#endif // !PLAYER_H
