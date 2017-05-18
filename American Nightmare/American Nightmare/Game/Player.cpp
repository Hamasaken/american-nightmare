#include "Player.h"

Player::Player() : Animation() { }

Player::Player(const Player & other) { }

Player::~Player() { }

bool Player::Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, b2World* world)
{
	// Starting entity variables (including hitbox)
	Entity::Start(mesh, material, world, glm::vec2(0, 20), glm::vec3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 1.f), b2_dynamicBody, b2Shape::e_polygon, true, PLAYER_MASS, PLAYER_FRICTION);

	// Set default keys
	RebindKeys(KEY_LEFT, KEY_RIGHT, KEY_JUMP, KEY_HOVER, KEY_DASH);

	// Setting starting variables
	position = glm::vec3(0, 20, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z);
	hasJumped = false;
	hasDashed = false;
	isHovering = false;
	isDashing = false;

	// Setting a self-pointer for collision detection
	getBody()->SetUserData(this);

	return true;
}

void Player::Update(GLint deltaT)
{
	// Are we currently hovering?
	isHovering = false;
	isDashing = false;

	// Dash cooldown
	if (hasDashed) {
		isDashing = false;
		dashCooldown -= deltaT;
	}
	if (dashCooldown < NULL)
		hasDashed = false;

	// Did we hit a surface?
	if (hitbox->getBody()->GetLinearVelocity().y == 0.f && hasJumped) { hasJumped = false; isDashing = true; }

	// Getting user input
	InputKeyboard();
	InputMouse();
	InputTesting();
	if (CONTROLLER_ON) InputController();

	// Thresholds in velocity
	b2Vec2 vel = hitbox->getBody()->GetLinearVelocity();
	if (vel.x > PLAYER_MAX_VEL_X) hitbox->getBody()->SetLinearVelocity(b2Vec2(vel.x * 0.90f, vel.y));
	if (vel.x < -PLAYER_MAX_VEL_X) hitbox->getBody()->SetLinearVelocity(b2Vec2(vel.x * 0.90f, vel.y));
	if (vel.y > PLAYER_MAX_VEL_Y) hitbox->getBody()->SetLinearVelocity(b2Vec2(vel.x, PLAYER_MAX_VEL_Y));
	if (vel.y < -PLAYER_MAX_VEL_Y) hitbox->getBody()->SetLinearVelocity(b2Vec2(vel.x, -PLAYER_MAX_VEL_Y));
	
	// Updating animation texture
	updateAnimation(deltaT);

	// Correcting texture to hitbox
	Entity::Update(deltaT);
}

void Player::RebindKeys(sf::Keyboard::Key key_left, sf::Keyboard::Key key_right, sf::Keyboard::Key key_jump, sf::Keyboard::Key key_hover, sf::Keyboard::Key key_dash)
{
	this->key_left = key_left;
	this->key_right = key_right;
	this->key_jump = key_jump;
	this->key_hover = key_hover;
	this->key_dash = key_dash;
}

void Player::Walk(Direction dir)
{
	b2Vec2 vel = hitbox->getBody()->GetLinearVelocity();
	switch (dir)
	{
	case LEFT:
		if (vel.x > -PLAYER_MAX_VEL_X)
		{
			hitbox->getBody()->ApplyForceToCenter(b2Vec2(-PLAYER_VEL_X, 0), true);
			directionIsRight = true;
		}
		break;
	case RIGHT:
		if (vel.x < PLAYER_MAX_VEL_X)
		{
			hitbox->getBody()->ApplyForceToCenter(b2Vec2(PLAYER_VEL_X, 0), true);
			directionIsRight = false;
		}
		break;
	case STOPPED:
		hitbox->getBody()->SetLinearVelocity(b2Vec2(vel.x * 0.90f, vel.y));
		break;
	}
}

void Player::Jump()
{
	b2Vec2 vel = hitbox->getBody()->GetLinearVelocity();

	if (!hasJumped)
	{
		hitbox->getBody()->ApplyLinearImpulseToCenter(b2Vec2(0, -PLAYER_VEL_Y), true);
		vel.y = hitbox->getBody()->GetLinearVelocity().y;
		hasJumped = true;
		isDashing = true;
	}
}

void Player::Dash()
{
	if (!hasDashed)
	{
		isDashing = true;
		hasDashed = true;
		dashCooldown = PLAYER_DASH_CD;
		float angle = (directionIsRight) ? -glm::pi<float>() * 0.5f : glm::pi<float>() * 0.5f;
		hitbox->getBody()->ApplyLinearImpulseToCenter(b2Vec2(sin(angle) * PLAYER_DASH_VEL, cos(angle) * PLAYER_DASH_VEL), true);
	}
}

void Player::Hover()
{
	isHovering = true;
	hitbox->getBody()->ApplyForceToCenter(b2Vec2(0, -PLAYER_HOVER_POWER), true);
}

void Player::InputTesting()
{
	// Move in Z axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) position.z += 0.15f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) position.z -= 0.15f;

	// Scaling
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) scale += 0.025f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)) scale -= 0.025f;

	// Rotation in X
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) rotation.z += 0.1f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) rotation.z -= 0.1f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) rotation.y += 0.1f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) rotation.y -= 0.1f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) rotation.x += 0.1f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) rotation.x -= 0.1f;
}

void Player::InputMouse() { }

void Player::InputKeyboard()
{
	if		(sf::Keyboard::isKeyPressed(key_left)) Walk(LEFT);
	else if (sf::Keyboard::isKeyPressed(key_right)) Walk(RIGHT); 
	else	Walk(STOPPED);

	if (sf::Keyboard::isKeyPressed(key_jump)) Jump();
	if (sf::Keyboard::isKeyPressed(key_hover)) Hover();
	if (sf::Keyboard::isKeyPressed(key_dash)) Dash();
}

void Player::InputController()
{
	sf::Joystick::update();
	if (sf::Joystick::isConnected(0))
	{
		if (sf::Joystick::isButtonPressed(0, BTN_A)) Jump();

		if (sf::Joystick::isButtonPressed(0, BTN_X)) Hover();

		if (sf::Joystick::isButtonPressed(0, BTN_Y))
			printf("Y.\n");
		if (sf::Joystick::isButtonPressed(0, BTN_B)) Dash();

		if (sf::Joystick::isButtonPressed(0, BTN_LB))
			printf("LB.\n");
		if (sf::Joystick::isButtonPressed(0, BTN_RB))
			printf("RB.\n");
		if (sf::Joystick::isButtonPressed(0, BTN_BACK))
			printf("Back.\n");
		if (sf::Joystick::isButtonPressed(0, BTN_START))
			printf("Start.\n");
		if (sf::Joystick::isButtonPressed(0, BTN_LT))
			printf("LT.\n");
		if (sf::Joystick::isButtonPressed(0, BTN_RT))
			printf("RT.\n");

		float leftAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) / 100.f;
		if (leftAxis < -0.1f || leftAxis > 0.1f) // Controller offset
		{
			if (leftAxis > 0)	Walk(RIGHT);
			else				Walk(LEFT);
		}
		else Walk(STOPPED);
	}
}

b2Body* Player::getBody()
{
	return hitbox->getBody();
}

bool Player::getIsDashing()
{
	return isDashing;
}

bool Player::getIsHovering()
{
	return isHovering;
}

glm::vec2 Player::getPlayerPosAsGLM()
{
	glm::vec2 myVec;

	myVec.x = hitbox->getPosition().x;
	myVec.y = hitbox->getPosition().y;

	return myVec;
}
