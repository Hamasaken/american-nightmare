#include "Player.h"

Player::Player() : Object() { }

Player::Player(const Player & other) { }

Player::~Player() { }

void Player::Update()
{
	// Updating movement
	Movement();
}

void Player::Movement()
{
	// Temporary movement & rotation & scaling for testing :)

	// Positioning
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) position.y += 0.15f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) position.y -= 0.15f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) position.x += 0.15f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) position.x -= 0.15f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) position.z += 0.15f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) position.z -= 0.15f;

	// Scaling
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) scale += 0.025f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)) scale -= 0.025f;

	// Rotation in X
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) rotation.x += 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) rotation.x -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) rotation.y += 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) rotation.y -= 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) rotation.z += 1.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) rotation.z -= 1.f;

}
