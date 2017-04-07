#include "Player.h"

Player::Player() : Object() { }

Player::Player(const Player & other) { }

Player::~Player() { }

bool Player::Start(OpenGL* openGL, std::string modelName, std::string textureName)
{
	if (!Object::Start(openGL, modelName, textureName))
		return false;

	// Temp function
	model->BuildTriangle(openGL);

	return true;
}

void Player::Update()
{
	// Updating movement
	Movement();
}

void Player::Movement()
{
	// Horizontal
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) position.y += 0.25f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) position.y -= 0.25f;

	// Vertical
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) position.x += 0.25f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) position.x -= 0.25f;
}
