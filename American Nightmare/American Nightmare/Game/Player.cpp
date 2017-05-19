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

Player::Player() { }

Player::Player(const Player & other) { }

Player::~Player() { }

void Player::initiateCursor()
{
	SDL_ShowCursor(SDL_ENABLE);
	this->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	SDL_SetCursor(cursor);
}

//bool Player::Start(std::string modelName, const MaterialManager::Material* material, b2World* world)
bool Player::Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, const MaterialManager::Material* material2, b2World* world)
{
	this->checkValue = false;

	//this->myProjectileHandler = ProjectileHandler(mesh, material, world, this->getPlayerPosAsGLM());

	//Sets the cursor for the player
	initiateCursor();

	// Starting entity variables (including hitbox)
	Entity::Start(mesh, material, world, glm::vec2(0, 20), glm::vec3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 1.f), b2_dynamicBody, b2Shape::e_polygon, true, PLAYER_MASS, PLAYER_FRICTION);

	// Setting starting variables
	position = glm::vec3(0, 20, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z);
	hasJumped = false;

	// Creating model
	model = new Model();
	if (model == nullptr) return false;
	/*if (!model->Start(modelName)) return false;*/

	this->material = material;
	model->BuildQuadTexture();

	//vac = new Vacuum();
	//vac->startVac(nullptr, material2, world, getBody());

	// Setting a self-pointer for collision detection
	getBody()->SetUserData(this);

	return true;
}

void Player::Update(GLint deltaT, b2World* world, glm::vec2 pos)
{
	/*if (getCheckValue() == true)
		myProjectileHandler.addProjectile(world);*/

	//	//Update ProjectileHandler
	//	myProjectileHandler->Update(deltaT, world, this->getPlayerPosAsGLM());


	// Getting user input
	InputKeyboard();
	InputTesting();
	if (CONTROLLER_ON) InputController();
	
	// Updating animation texture
	updateAnimation(deltaT);

	//Update ProjectileHandler
	myProjectileHandler.Update(deltaT, world, glm::vec3(pos.x,pos.y, 0.5f));

	// Correcting texture to hitbox
	Entity::Update(deltaT);
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

void Player::InputKeyboard()
{
	b2Vec2 vel = hitbox->getBody()->GetLinearVelocity();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		hitbox->getBody()->ApplyForceToCenter(b2Vec2(PLAYER_VEL_X, 0), true);
		directionIsRight = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		hitbox->getBody()->ApplyForceToCenter(b2Vec2(-PLAYER_VEL_X, 0), true);
		directionIsRight = true;
	}
	else
	{
		hitbox->getBody()->SetLinearVelocity(b2Vec2(vel.x * 0.90f, vel.y));
	}

	// Did we hit a surface?
	if (vel.y == 0.f) hasJumped = false;
	// Jumping
	if (!hasJumped && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		hitbox->getBody()->ApplyLinearImpulseToCenter(b2Vec2(0, -PLAYER_VEL_Y), true);
		vel.y = hitbox->getBody()->GetLinearVelocity().y;
		hasJumped = true;
	}

	// Thresholds in velocity
	if (vel.x > PLAYER_MAX_VEL_X) hitbox->getBody()->SetLinearVelocity(b2Vec2(PLAYER_MAX_VEL_X, vel.y));
	if (vel.x < -PLAYER_MAX_VEL_X) hitbox->getBody()->SetLinearVelocity(b2Vec2(-PLAYER_MAX_VEL_X, vel.y));
	if (vel.y > PLAYER_MAX_VEL_Y) hitbox->getBody()->SetLinearVelocity(b2Vec2(vel.x, PLAYER_MAX_VEL_Y));
	if (vel.y < -PLAYER_MAX_VEL_Y) hitbox->getBody()->SetLinearVelocity(b2Vec2(vel.x, -PLAYER_MAX_VEL_Y));
}

void Player::InputController()
{
	sf::Joystick::update();
	if (sf::Joystick::isConnected(0))
	{
		b2Vec2 vel = hitbox->getBody()->GetLinearVelocity();

		if (!hasJumped && sf::Joystick::isButtonPressed(0, BTN_A))
		{
			if (vel.y >= 0.f) 
			{
				hitbox->getBody()->ApplyLinearImpulseToCenter(b2Vec2(0, -PLAYER_VEL_Y), true);
				hasJumped = true;
			}
		}
		else if (vel.y == 0.f) hasJumped = false;

		if (sf::Joystick::isButtonPressed(0, BTN_X))
			printf("X.\n");
		if (sf::Joystick::isButtonPressed(0, BTN_Y))
			printf("Y.\n");
		if (sf::Joystick::isButtonPressed(0, BTN_B))
			printf("B.\n");
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
			hitbox->getBody()->ApplyForceToCenter(b2Vec2(PLAYER_VEL_X * leftAxis, 0), true);
			if (leftAxis > 0) directionIsRight = false;
			else if (leftAxis < 0) directionIsRight = true;
		}
		else hitbox->getBody()->SetLinearVelocity(b2Vec2(vel.x * 0.90f, vel.y));

		// Thresholds in velocity
		if (vel.x > PLAYER_MAX_VEL_X) hitbox->getBody()->SetLinearVelocity(b2Vec2(PLAYER_MAX_VEL_X, vel.y));
		if (vel.x < -PLAYER_MAX_VEL_X) hitbox->getBody()->SetLinearVelocity(b2Vec2(-PLAYER_MAX_VEL_X, vel.y));
		if (vel.y > PLAYER_MAX_VEL_Y) hitbox->getBody()->SetLinearVelocity(b2Vec2(vel.x, PLAYER_MAX_VEL_Y));
		if (vel.y < -PLAYER_MAX_VEL_Y) hitbox->getBody()->SetLinearVelocity(b2Vec2(vel.x, -PLAYER_MAX_VEL_Y));
	}
}

b2Body* Player::getBody()
{
	return hitbox->getBody();
}

//Vacuum * Player::getVac()
//{
//	return vac;
//}

glm::vec2 Player::getPlayerPosAsGLM()
{
	glm::vec2 myVec;

	myVec.x = hitbox->getPosition().x;
	myVec.y = hitbox->getPosition().y;
	//myVec.z = 0.5f;
	return myVec;
}

/*bool Player::addPlayerProjectiles()
{
	if (myProjectileHandler.getNrOffProjectiles() >= myProjectileHandler.getCAP())
		return false;
	else
		return true;
}

void Player::setCheckForProjectilePickUp(bool checkValue)
{ 
		this->checkValue = checkValue;
}

bool Player::getCheckValue()const
{
	return this->checkValue;
}*/