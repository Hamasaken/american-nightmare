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
	
	// Temp gravity
	velocity.y -= 0.02f;
	position += glm::vec3(velocity, 0);
	if (position.y < 0.f)
		position.y = 0.f;

	// Jumping
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && position.y == 0) velocity.y = 0.35f;

	// Positioning
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		body->SetLinearVelocity(b2Vec2(10.f, 0.f));
		//position.x += 0.15f;
		directionIsRight = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		body->SetLinearVelocity(b2Vec2(-10.f, 0.f));
		//position.x -= 0.15f;
		directionIsRight = true;
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

	position.x = body->GetPosition().x;
	position.y = -body->GetPosition().y;
}
