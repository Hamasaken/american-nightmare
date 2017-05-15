#include "Player.h"

//Player::Player() : Animation()
//{
//	this->myProjectileHandler = ProjectileHandler();
//}
//

Player::Player(b2World *world, GLuint shader) : Animation()
{
	this->myProjectileHandler = ProjectileHandler(world, shader);
}

Player::Player() { }

Player::Player(const Player & other) { }

Player::~Player() { }

void Player::initiateCursor()
{
	SDL_ShowCursor(SDL_ENABLE);
	this->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	SDL_SetCursor(cursor);
}

bool Player::Start(std::string modelName, const MaterialManager::Material* material, b2World* world)
{
	//Sets the cursor for the player
	initiateCursor();

	// Starting entity variables (including hitbox)
	Entity::Start(modelName, material, world, glm::vec2(0, -20), glm::vec2(PLAYER_SIZE_X, PLAYER_SIZE_Y), b2_dynamicBody, b2Shape::e_polygon, PLAYER_DENSITY, PLAYER_FRICTION);

	// Setting starting variables
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z);

	// Creating model
	model = new Model();
	if (model == nullptr) return false;
	if (!model->Start(modelName)) return false;

	this->material = material;
	model->BuildQuadTexture();

	vac = new Vacuum();
	vac->startVac(modelName, material2, world, getBody());

	getBody()->SetUserData(this);

	return true;
}

//void Player::Update(GLint deltaT, b2World world, glm::vec2 pos)
//{
//	// Getting user input
//	Movement();
//
//	// Updating animation texture
//	updateAnimation(deltaT);
//
//	//Update ProjectileHandler
//	myProjectileHandler->Update(deltaT, world, this->getPlayerPosAsGLM());
//
//	// Correcting texture to hitbox
//	Entity::Update(deltaT);
//}

void Player::Update(GLint deltaT, b2World* world, glm::vec2 pos)
{
	// Getting user input
	Movement();
	
	// Updating animation texture
	updateAnimation(deltaT);

	//Update ProjectileHandler
	//myProjectileHandler->Update(deltaT, world, this->getPlayerPosAsGLM());

	// Correcting texture to hitbox
	Entity::Update(deltaT);

	vac->Update(getBody()->GetPosition(), deltaT);
}

void Player::Movement()
{
	// Temporary movement & rotation & scaling for testing :)
	
	// Temp gravity
	/*velocity.y -= 0.02f;
	position += glm::vec3(velocity, 0);*/

	if (position.y < 0.f)
		position.y = 0.f;

	// Jumping
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && position.y == 0) velocity.y = 0.35f;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !jumping) velocity.y = 0.35f;

	// Positioning
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		hitbox->getBody()->ApplyForceToCenter(b2Vec2(PLAYER_VEL_X, 0), true);
		directionIsRight = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		hitbox->getBody()->ApplyForceToCenter(b2Vec2(-PLAYER_VEL_X, 0), true);
		directionIsRight = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		hitbox->getBody()->ApplyForceToCenter(b2Vec2(0, -PLAYER_VEL_Y), true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		hitbox->getBody()->ApplyForceToCenter(b2Vec2(0, PLAYER_VEL_Y), true);
	}

	// Move in Z axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) position.z += 0.15f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) position.z -= 0.15f;

	// Scaling
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) scale += 0.025f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)) scale -= 0.025f;

	// Rotation in X
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) rotation.x += 2.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) rotation.x -= 2.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) rotation.y += 2.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) rotation.y -= 2.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) rotation.z += 2.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) rotation.z -= 2.f;

	// Thresholds in velocity
	if (hitbox->getBody()->GetLinearVelocity().x > PLAYER_MAX_VEL_X) hitbox->getBody()->SetLinearVelocity(b2Vec2(PLAYER_MAX_VEL_X, hitbox->getBody()->GetLinearVelocity().y));
	if (hitbox->getBody()->GetLinearVelocity().x < -PLAYER_MAX_VEL_X) hitbox->getBody()->SetLinearVelocity(b2Vec2(-PLAYER_MAX_VEL_X, hitbox->getBody()->GetLinearVelocity().y));
	if (hitbox->getBody()->GetLinearVelocity().y > PLAYER_MAX_VEL_Y) hitbox->getBody()->SetLinearVelocity(b2Vec2(hitbox->getBody()->GetLinearVelocity().x, PLAYER_MAX_VEL_Y));
	if (hitbox->getBody()->GetLinearVelocity().y < -PLAYER_MAX_VEL_Y) hitbox->getBody()->SetLinearVelocity(b2Vec2(hitbox->getBody()->GetLinearVelocity().x, -PLAYER_MAX_VEL_Y));
}

b2Body* Player::getBody()
{
	return hitbox->getBody();
}

Vacuum * Player::getVac()
{
	return vac;
}

glm::vec2 Player::getPlayerPosAsGLM()
{
	glm::vec2 myVec;

	myVec.x = hitbox->getPosition().x;
	myVec.y = hitbox->getPosition().y;

	return myVec;
}
