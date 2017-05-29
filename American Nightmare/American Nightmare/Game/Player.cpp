#include "Player.h"

Player::Player(): Animation() 
{
}

Player::Player(const Player & other) { }

Player::~Player() { }

void Player::initiateCursor()
{
	SDL_ShowCursor(SDL_ENABLE);
	this->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	SDL_SetCursor(cursor);
}

void Player::initiateProjectile(MeshManager* meshManager, MaterialManager* materialManager)
{
	this->ammo = PLAYER_AMMO_CAP / 2;
	this->fireDirection = { 0.0f, 0.0f };

	for (int i = 0; i < this->ammo; i++)
	{
		if (i % 2 == 0)
			this->ammoList.push_back(ProjectileData(meshManager->getMesh("quad"), materialManager->getMaterial("boxmaterial"), false));
		else
			this->ammoList.push_back(ProjectileData(meshManager->getMesh("quad"), materialManager->getMaterial("garbagematerial"), true));
	}

}

//bool Player::Start(std::string modelName, const MaterialManager::Material* material, b2World* world)
bool Player::Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, const MaterialManager::Material* material2, b2World* world, ParticleManager* particleManager, SoundManager* soundManager, MeshManager* meshManager, MaterialManager* materialManager, Camera* camera, glm::vec2 screenPos, glm::vec2 screenSize)
{
	//Initiates screen properties
	this->screenPos = screenPos;
	this->screenSize = screenSize;

	//Sets the cursor for the player
	initiateCursor();

	//Sets variables for projectile/gun
	initiateProjectile(meshManager, materialManager);

	
	// Starting entity variables (including hitbox)
	Entity::Start(mesh, material, world, glm::vec2(0, 20), glm::vec3(PLAYER_SIZE_X * 0.45f, PLAYER_SIZE_Y * 0.9f, 1.f), b2_dynamicBody, b2Shape::e_polygon, true, PLAYER_MASS, PLAYER_FRICTION);

	// Set default keys
	RebindKeys(KEY_LEFT, KEY_RIGHT, KEY_JUMP, KEY_HOVER, KEY_DASH);

	// Setting starting variables
	hp = PLAYER_HP;
	isDead = false;
	position = glm::vec3(0, 20, 0);
	startPosition = position;
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z);
	power = PLAYER_POWER_MAX;
	hasJumped = false;
	hasDashed = false;
	isHovering = false;
	isDashing = false;
	invulTime = 0.f;
	shockwaveCooldown = 0.f;
	contactWithEnemy = nullptr;

	this->particleManager = particleManager;
	this->soundManager = soundManager;
	this->camera = camera;

	vac = new Vacuum();
	vac->startVac(world, getBody());

	// Setting a self-pointer for collision detection
	getBody()->SetUserData(this);

	//Sets screen properties
	UpdateScreenProperties(screenSize, screenPos);

	return true;
}

void Player::Update(GLint deltaT, b2World* world)
{
	//This will set the firedirection to the direction of the right-thumbstick
	if (sf::Joystick::isConnected(0))
	{
		this->fireDirection = glm::vec2(sf::Joystick::getAxisPosition(0, sf::Joystick::U), sf::Joystick::getAxisPosition(0, sf::Joystick::R));
		fireDirection = glm::normalize(fireDirection);
	}
	else //This is for the mouse
	{
		this->fireDirection = fromScreenToNDC(glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y - 150), screenSize, screenPos);
		this->fireDirection = glm::normalize(fireDirection);
	}

	// Getting the direction of the player from the aiming direction
	if (fireDirection.x < 0) directionIsRight = true;
	else directionIsRight = false;

	// Update player invulnerability time
	if (invulTime > 0.f)
	{
		invulTime -= deltaT * 0.001f;
	}
	// Quick fix enemy continuous collision
	else if (contactWithEnemy)
	{
		invulTime = PLAYER_INVULNERABILITY_TIME;
		camera->screenShake(600.f, 0.6f);
		particleManager->EffectBloodSplatter(position, getAngleFromTwoPoints(contactWithEnemy->getCenter(), this->getCenter()), 0.08f, 25, glm::vec4(0.4f, 0.05f, 0.025f, 1.f)); // temp blood effect
		soundManager->playSFX(SoundManager::SFX_HIT);
		soundManager->playSFXOverDrive(SoundManager::SFX_HURT, 50.f);
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

	shockwaveCooldown -= deltaT;

	// Getting user input
	if (!isDead)
	{
		InputKeyboard(deltaT);
		InputMouse();
	//	InputTesting(); 
		InputController(deltaT);
		//if (CONTROLLER_ON) InputController(deltaT);
	}

	// Recharging power meter
	if (!isHovering)
	{
		soundManager->stopSFX(SoundManager::SFX_HOVER);

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

	// Updating vac
	this->vac->Update(this->getBody()->GetPosition(), deltaT);

	// Correcting texture to hitbox
	Entity::Update(deltaT);
}

void Player::Reset()
{
	// Going to save point
	hitbox->getBody()->SetTransform(b2Vec2(startPosition.x, startPosition.y), 0);
	hitbox->getBody()->SetAwake(true);

	// Resetting variables
	hp = PLAYER_HP;
	isDead = false;
	power = PLAYER_POWER_MAX;
	hasJumped = false;
	hasDashed = false;
	isHovering = false;
	isDashing = false;
	invulTime = 0.f;
	contactWithEnemy = nullptr;
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

		if (contactWithEnemy != nullptr)
		{
			particleManager->EffectBloodSplatter(position, getAngleFromTwoPoints(contactWithEnemy->getCenter(), this->getCenter()), 0.08f, 25, glm::vec4(0.4f, 0.05f, 0.025f, 1.f));
			particleManager->EffectBloodSplatter(position, getAngleFromTwoPoints(this->getCenter(), contactWithEnemy->getCenter()), 0.08f, 25, glm::vec4(0.4f, 0.05f, 0.025f, 1.f));
		}

		this->getBody()->SetLinearVelocity({ 0, 0 });
		soundManager->playSFXOverDrive(SoundManager::SFX::SFX_DEATH, 50, 0.f);
		soundManager->playModifiedSFX(SoundManager::SFX_GAMEOVER, 50, 0.f);
		particleManager->EffectExplosionLights(position, 50, glm::vec4(0.4f, 0.05f, 0.025f, 1.f));
		particleManager->EffectBloodCloud(position, 10, glm::vec4(1.f), randBetweenF(1.f, 1.75f));
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
	if (abs(vel.x) <= PLAYER_MAX_VEL_X)
	{
		if (hasJumped)
		{
			soundManager->stopSFX(SoundManager::SFX_STEPS);
			switch (dir)
			{
			case LEFT:
				if (!directionIsRight) isReversed = true;
				else isReversed = false;
				hitbox->getBody()->SetLinearVelocity({ -PLAYER_MAX_VEL_X, vel.y });
				break;
			case RIGHT:
				if (directionIsRight) isReversed = true;
				else isReversed = false;
				hitbox->getBody()->SetLinearVelocity({ PLAYER_MAX_VEL_X, vel.y });
				break;
			}
			vel.x = hitbox->getBody()->GetLinearVelocity().x;
			hitbox->getBody()->SetLinearVelocity(b2Vec2(vel.x * 0.90f, vel.y));
		}
		else
		{
			switch (dir)
			{
			case LEFT:
				hitbox->getBody()->SetLinearVelocity({ -PLAYER_MAX_VEL_X, vel.y });
				if (!directionIsRight) isReversed = true;
				else isReversed = false;
				soundManager->playModifiedSFX(SoundManager::SFX_STEPS, 25, 0.15f);
				break;
			case RIGHT:
				hitbox->getBody()->SetLinearVelocity({ PLAYER_MAX_VEL_X, vel.y });
				if (directionIsRight) isReversed = true;
				else isReversed = false;
				soundManager->playModifiedSFX(SoundManager::SFX_STEPS, 25, 0.15f);
				break;
			case STOPPED:
				soundManager->stopSFX(SoundManager::SFX_STEPS);
				hitbox->getBody()->SetLinearVelocity(b2Vec2(0, vel.y));
				break;
			}
		}
	}
}

void Player::Jump()
{
	b2Vec2 vel = hitbox->getBody()->GetLinearVelocity();

	if (!hasJumped && vel.y > -0.5f)
	{
		hitbox->getBody()->GetFixtureList()->SetFriction(0.f);
		soundManager->stopSFX(SoundManager::SFX_STEPS);
		soundManager->playSFXOverDrive(SoundManager::SFX_JUMP, 80.f);
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
		camera->screenShake(250.f, 0.35f);
		SoundManager::SFX sfx = (inKey == key_left) ? SoundManager::SFX::SFX_LtoR : SoundManager::SFX::SFX_RtoL;
		if (inKey == key_jump) sfx = SoundManager::SFX::SFX_DASH;
		soundManager->playSFXOverDrive(sfx, 50.f);
		power -= PLAYER_POWER_COST_DASH;
		isDashing = true;
		hasDashed = true;
		dashCooldown = PLAYER_DASH_CD;
		//float angle = (directionIsRight) ? -glm::pi<float>() * 0.5f : glm::pi<float>() * 0.5f;

		float angle;
		if (sf::Joystick::isConnected(0))
		{
			b2Vec2 angle = b2Vec2(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
			angle.Normalize();
			hitbox->getBody()->ApplyLinearImpulseToCenter(b2Vec2((angle.x * PLAYER_DASH_VEL) * 0.5, (angle.y * PLAYER_DASH_VEL) * 0.25), true);
			//b2Vec2((sin(angle.x) * PLAYER_DASH_VEL) * 0.25, (cos(angle.y) * PLAYER_DASH_VEL) * 0.25), true)
		}
		else
		{
			if (sf::Keyboard::isKeyPressed(key_jump))
			{
				if (inKey == key_left)
					angle = -glm::pi<float>() * 0.75f;
				else if (inKey == key_right)
					angle = glm::pi<float>() * 0.75f;
				else
					angle = glm::pi<float>();

				hitbox->getBody()->ApplyLinearImpulseToCenter(b2Vec2((sin(angle) * PLAYER_DASH_VEL) * 0.25, (cos(angle) * PLAYER_DASH_VEL) * 0.25), true);
			}
			else
			{
				if (inKey == key_left)
					angle = -glm::pi<float>() * 0.5f;
				else if (inKey == key_right)
					angle = glm::pi<float>() * 0.5f;

				hitbox->getBody()->ApplyLinearImpulseToCenter(b2Vec2(sin(angle) * PLAYER_DASH_VEL, 0.f), true);
			}
		}
	}
}

void Player::Hover(GLint deltaT)
{
	static float yPos;

	soundManager->playModifiedSFX(SoundManager::SFX_HOVER, 30, 0.01);

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

void Player::Shockwave()
{
	if (shockwaveCooldown < NULL)
	{
		camera->screenShake(750.f, 0.75f);
		soundManager->playSFXOverDrive(SoundManager::SFX_SHOCKWAVE, 100);
		particleManager->EffectSmokeCloud(position, 0, 5, glm::vec4(0.85f), 3.f);
		particleManager->EffectSmokeCloud(position, 0, 5, glm::vec4(0.35f), 2.5f);
		particleManager->EffectExplosionLights(position, 12, glm::vec4(0.45), 1.5f);
		particleManager->EffectExplosionLights(position, 12, glm::vec4(0.25), 0.90f);
		b2Vec2 pos;
		float angle = 0.f;
		b2ContactEdge* contact = vac->getBody()->GetContactList();
		while (contact != nullptr)
		{
			if (contact->contact->GetFixtureA()->GetBody()->GetUserData() != this &&
				contact->contact->GetFixtureB()->GetBody()->GetUserData() != this)
			{
				if (contact->contact->GetFixtureA()->GetBody()->GetUserData() == vac)
				{
					pos = contact->contact->GetFixtureB()->GetBody()->GetPosition();
					angle = getAngleFromTwoPoints(glm::vec3(pos.x, pos.y, 0.f), position);
					contact->contact->GetFixtureB()->GetBody()->ApplyForceToCenter(b2Vec2(cos(angle) * PLAYER_SHOCKWAVE_POWER, sin(angle) * PLAYER_SHOCKWAVE_POWER), true);
				}
				else
				{
					pos = contact->contact->GetFixtureA()->GetBody()->GetPosition();
					angle = getAngleFromTwoPoints(glm::vec3(pos.x, pos.y, 0.f), position);
					contact->contact->GetFixtureA()->GetBody()->ApplyForceToCenter(b2Vec2(cos(angle) * PLAYER_SHOCKWAVE_POWER, sin(angle) * PLAYER_SHOCKWAVE_POWER), true);
				}
			}
			contact = contact->next;
		}
		power -= PLAYER_POWER_COST_SHOCKWAVE;
		shockwaveCooldown = PLAYER_SHOCKWAVE_CD;
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

void Player::InputMouse() 
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle) && power >= PLAYER_POWER_COST_SHOCKWAVE)
	{
		Shockwave();
	}
}

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

	if (sf::Keyboard::isKeyPressed(key_jump)) 
	{
		Jump();
		if (sf::Keyboard::isKeyPressed(key_dash) && power >= PLAYER_POWER_COST_DASH) Dash(key_jump);
	}

	if (sf::Keyboard::isKeyPressed(key_hover) && power >= deltaT * 0.001 * PLAYER_POWER_COST_HOVER) Hover(deltaT);
	else isHovering = false;
}

void Player::InputController(GLint deltaT)
{
	sf::Joystick::update();
	if (sf::Joystick::isConnected(0))
	{
		cout << "KLSAda" << endl;
		if (sf::Joystick::isButtonPressed(0, BTN_A)) Jump();

		if (sf::Joystick::isButtonPressed(0, BTN_X) && power >= deltaT * 0.001 * PLAYER_POWER_COST_HOVER) Hover(deltaT);
		else isHovering = false;

		if (sf::Joystick::isButtonPressed(0, BTN_Y) && power >= PLAYER_POWER_COST_SHOCKWAVE)
		{
			Shockwave();
			printf("Y.\n");
		}
		
		if (sf::Joystick::isButtonPressed(0, BTN_LB))
			printf("LB.\n");
		if (sf::Joystick::isButtonPressed(0, BTN_RB))
			printf("RB.\n");
		if (sf::Joystick::isButtonPressed(0, BTN_BACK))
			printf("Back.\n");
		if (sf::Joystick::isButtonPressed(0, BTN_START))
	
			printf("start.\n");
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

		float yAxis = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) / 100.f;
		if (yAxis < 0.1f && sf::Joystick::isButtonPressed(0, BTN_B)) // Controller offset
		{
			Dash(key_jump);	
		}

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

float& Player::getNrOfProjectiles()
{
	return (float&)ammo;
}

bool Player::getIsFacingRight()
{
	return directionIsRight;
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

Vacuum * Player::getVac()
{
	return vac;
}

void Player::setHasJumped(bool hasJumped)
{
	this->hasJumped = hasJumped;
}

bool Player::getHasJumped()
{
	return hasJumped;
}

bool Player::getAmmoFull()
{
	if (ammo >= ammoCap)
		return true;

	return false;
}

ProjectileData Player::popProjectile()
{
	ProjectileData temp = this->ammoList.back();
	this->ammoList.pop_back();
	
	return temp;
}

void Player::pushProjectile(ProjectileData projectileData)
{
	this->ammoList.push_back(projectileData);
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

void Player::setStartingPosition(glm::vec3 position)
{
	this->startPosition = position;
}

bool Player::addPlayerProjectiles()
{
	if (this->ammo >= this->ammoCap)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Player::getCanShoot()
{
	if (this->ammo > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::addNrOfProjectiles()
{
	this->ammo++;
}

void Player::decreaseNrOfProjectiles()
{
	this->ammo--;
}

glm::vec2 Player::getFireDirection()const
{
	return this->fireDirection;
}

void Player::UpdateScreenProperties(glm::vec2 screenSize, glm::vec2 screenPos)
{
	this->screenPos = screenPos;
	this->screenSize = screenSize;
}