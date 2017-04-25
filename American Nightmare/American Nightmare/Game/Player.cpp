#include "Player.h"

Player::Player() : Animation() { }

Player::Player(const Player & other) { }

Player::~Player() { }

bool Player::Start(std::string modelName, const MaterialManager::Material* material, b2World& world, float x, float y, bool isDynamic)
{
	// Setting starting variables
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);

	// Creating model
	model = new Model();
	if (model == nullptr) return false;
	if (!model->Start(modelName)) return false;

	this->material = material;
	model->BuildQuadTexture();

	//Physics
	bodyDef.fixedRotation = true;
	bodyDef.position = b2Vec2(x, -y);
	bodyDef.type = b2_dynamicBody;
	body = world.CreateBody(&bodyDef);
	shape.SetAsBox(1.f, 1.f); // Creates a box shape. Divide your desired width and height by 2.

	fixtureDef.density = 0.f;  // Sets the density of the body
	fixtureDef.friction = 10.0f;
	fixtureDef.shape = &shape; // Sets the shape
	body->CreateFixture(&fixtureDef); // Apply the fixture definition

	return true;
}

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
