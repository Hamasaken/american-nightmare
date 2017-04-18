#include "Player.h"

Player::Player() : Animation() { }

Player::Player(const Player & other) { }

Player::~Player() { }

void Player::Update(GLint deltaT)
{
	// Updating movement
	Movement();

	updateAnimation(deltaT);
}

void Player::Movement()
{
	// Temporary movement & rotation & scaling for testing :)
	velocity.y -= 0.05f;

	position += glm::vec3(velocity, 0);

	if (position.y < 0.f)
		position.y = 0.f;

	// Jumping

	// Positioning
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) velocity.y = 0.5f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) position.y -= 0.15f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		position.x += 0.15f;
		directionIsRight = true;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		position.x -= 0.15f;
		directionIsRight = false;
	}
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
}
