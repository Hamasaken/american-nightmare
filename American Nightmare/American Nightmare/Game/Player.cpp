#include "Player.h"

//Player::Player() : Animation()
//{
//	this->myProjectileHandler = ProjectileHandler();
//}
//

//Player::Player(const MeshManager::Mesh* mesh, const MaterialManager::Material * material, b2World *world) : Animation()
//{
//	
//}

Player::Player(): Animation() { }

Player::Player(const Player & other) { }

Player::~Player() { }

void Player::initiateCursor()
{
	SDL_ShowCursor(SDL_ENABLE);
	this->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	SDL_SetCursor(cursor);
}

//bool Player::Start(std::string modelName, const MaterialManager::Material* material, b2World* world)
bool Player::Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, const MaterialManager::Material* material2, b2World* world, ParticleManager* particleManager, SoundManager* soundManager, Camera* camera)
{
	//this->myProjectileHandler = ProjectileHandler(mesh, material, world, this->getPlayerPosAsGLM());

	//Sets the cursor for the player
	initiateCursor();

	// Starting entity variables (including hitbox)
	Entity::Start(mesh, material, world, glm::vec2(0, 20), glm::vec3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 1.f), b2_dynamicBody, b2Shape::e_polygon, true, PLAYER_MASS, PLAYER_FRICTION);

	// Set default keys
	RebindKeys(KEY_LEFT, KEY_RIGHT, KEY_JUMP, KEY_HOVER, KEY_DASH);

	// Setting starting variables
	hp = PLAYER_HP;
	isDead = false;
	position = glm::vec3(0, 20, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z);
	power = PLAYER_POWER_MAX;
	hasJumped = false;
	hasDashed = false;
	isHovering = false;
	isDashing = false;
	invulTime = 0.f;
	contactWithEnemy = nullptr;

	this->particleManager = particleManager;
	this->soundManager = soundManager;
	this->camera = camera;

	//vac = new Vacuum();
	//vac->startVac(nullptr, material2, world, getBody());

	// Setting a self-pointer for collision detection
	getBody()->SetUserData(this);

	return true;
}

void Player::Update(GLint deltaT, b2World* world)
{
	// Update player invulnerability time
	if (invulTime > 0.f)
	{
		invulTime -= deltaT * 0.001f;
	}
	// Quick fix enemy continuous collision
	else if (contactWithEnemy)
	{
		invulTime = PLAYER_INVULNERABILITY_TIME;
		camera->screenShake(500.f, 0.5f);
		particleManager->EffectBloodSplatter(position, getAngleFromTwoPoints(contactWithEnemy->getCenter(), this->getCenter()), 0.08f, 25, glm::vec4(0.4f, 0.05f, 0.025f, 1.f)); // temp blood effect
		soundManager->playSFX(SoundManager::SFX_HIT);	// temp hit sfx
		TakeDamage(contactWithEnemy->getDamage());
	}

	// Are we currently hovering?
	//isHovering = false;
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
	if (!isDead)
	{
		InputKeyboard(deltaT);
		InputMouse();
		InputTesting();
		if (CONTROLLER_ON) InputController(deltaT);
	}

	// Recharging power meter
	if (!isHovering)
	{
		power += deltaT * 0.001f * PLAYER_POWER_RECHARGE;

		if (power > PLAYER_POWER_MAX)
			power = PLAYER_POWER_MAX;
	}

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

void Player::TakeDamage(float dmg)
{
	hp -= dmg;
	if (hp <= NULL && !isDead)
	{
		isDead = true;
		particleManager->EffectBloodSplatter(position, getAngleFromTwoPoints(contactWithEnemy->getCenter(), this->getCenter()), 0.08f, 25, glm::vec4(0.4f, 0.05f, 0.025f, 1.f));
		particleManager->EffectBloodSplatter(position, getAngleFromTwoPoints(this->getCenter(), contactWithEnemy->getCenter()), 0.08f, 25, glm::vec4(0.4f, 0.05f, 0.025f, 1.f));
		particleManager->EffectExplosionLights(position, 50, glm::vec4(0.4f, 0.05f, 0.025f, 1.f));
		contactWithEnemy = nullptr;
	}
}

bool Player::getIsDead()
{
	return isDead;
}

void Player::Walk(Direction dir)
{
	b2Vec2 vel = hitbox->getBody()->GetLinearVelocity();
	if (!hasJumped)
	{
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
	else
	{
		switch (dir)
		{
		case LEFT:
			if (vel.x > -PLAYER_MAX_VEL_X)
			{
				hitbox->getBody()->ApplyForceToCenter(b2Vec2(-PLAYER_VEL_X * 0.35f, 0), true);
				directionIsRight = true;
			}
			break;
		case RIGHT:
			if (vel.x < PLAYER_MAX_VEL_X)
			{
				hitbox->getBody()->ApplyForceToCenter(b2Vec2(PLAYER_VEL_X * 0.35f, 0), true);
				directionIsRight = false;
			}
			break;
		case STOPPED:
			hitbox->getBody()->SetLinearVelocity(b2Vec2(vel.x * 0.90f, vel.y));
			break;
		}
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

void Player::Dash(sf::Keyboard::Key inKey)
{
	if (!hasDashed)
	{
		power -= PLAYER_POWER_COST_DASH;
		isDashing = true;
		hasDashed = true;
		dashCooldown = PLAYER_DASH_CD;
		//float angle = (directionIsRight) ? -glm::pi<float>() * 0.5f : glm::pi<float>() * 0.5f;

		float angle;
		if (inKey == key_left)
			angle = -glm::pi<float>() * 0.5f;
		else
			angle = glm::pi<float>() * 0.5f;

		hitbox->getBody()->ApplyLinearImpulseToCenter(b2Vec2(sin(angle) * PLAYER_DASH_VEL, cos(angle) * PLAYER_DASH_VEL), true);
	}
}

void Player::Hover(GLint deltaT)
{
	static float yPos;

	if (isHovering)
	{
		hitbox->getBody()->SetTransform(b2Vec2(hitbox->getBody()->GetPosition().x, yPos), 0.f);
		hitbox->getBody()->SetLinearVelocity(b2Vec2(hitbox->getBody()->GetLinearVelocity().x, 0.f));
		power -= deltaT * 0.001 * PLAYER_POWER_COST_HOVER;
	}
	else if (hasJumped)
	{
		isHovering = true;
		yPos = hitbox->getBody()->GetPosition().y;
		hitbox->getBody()->SetTransform(b2Vec2(hitbox->getBody()->GetPosition().x, yPos), 0.f);
		power -= deltaT * 0.001 * PLAYER_POWER_COST_HOVER;
	}
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

void Player::InputKeyboard(GLint deltaT)
{
	if (sf::Keyboard::isKeyPressed(key_left))
	{
		Walk(LEFT);
		if (sf::Keyboard::isKeyPressed(key_dash) && power >= PLAYER_POWER_COST_DASH) Dash(key_left);
	}
	else if (sf::Keyboard::isKeyPressed(key_right))
	{
		Walk(RIGHT);
		if (sf::Keyboard::isKeyPressed(key_dash) && power >= PLAYER_POWER_COST_DASH) Dash(key_right);
	}
	else	Walk(STOPPED);

	if (sf::Keyboard::isKeyPressed(key_jump)) Jump();
	if (sf::Keyboard::isKeyPressed(key_hover) && power >= deltaT * 0.001 * PLAYER_POWER_COST_HOVER) Hover(deltaT);
	else isHovering = false;
}

void Player::InputController(GLint deltaT)
{
	sf::Joystick::update();
	if (sf::Joystick::isConnected(0))
	{
		if (sf::Joystick::isButtonPressed(0, BTN_A)) Jump();

		if (sf::Joystick::isButtonPressed(0, BTN_X) && power >= deltaT * 0.001 * PLAYER_POWER_COST_HOVER) Hover(deltaT);

		if (sf::Joystick::isButtonPressed(0, BTN_Y))
			printf("Y.\n");
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
			if (leftAxis > 0)
			{
				Walk(RIGHT);
				if (sf::Joystick::isButtonPressed(0, BTN_B) && power >= PLAYER_POWER_COST_DASH) Dash(key_right);
			}
			else
			{
				Walk(LEFT);
				if (sf::Joystick::isButtonPressed(0, BTN_B) && power >= PLAYER_POWER_COST_DASH) Dash(key_left);
			}
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

float& Player::getHP()
{
	return hp;
}

float& Player::getPower()
{
	return power;
}

bool Player::getIsHovering()
{
	return isHovering;
}

void Player::setContactWithEnemy(Enemy* contact)
{
	this->contactWithEnemy = contact;
}

Enemy* Player::getContactWithEnemy()
{
	return contactWithEnemy;
}

void Player::setInvulTime(GLfloat invulTime)
{
	this->invulTime = invulTime;
}

GLfloat Player::getInvulTime()
{
	return invulTime;
}

glm::vec2 Player::getPlayerPosAsGLM()
{
	glm::vec2 myVec;

	myVec.x = hitbox->getPosition().x;
	myVec.y = hitbox->getPosition().y;
	//myVec.z = 0.5f;
	return myVec;
}

bool Player::addPlayerProjectiles()
{
	if (this->nrOfProjectiles >= this->CAP)
	{
		return false;
	}
	else
	{
		this->nrOfProjectiles++;
		return true;
	}
}