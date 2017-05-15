#include "Enemy.h"

Enemy::Enemy() : Animation() { }

Enemy::Enemy(const Enemy & other) { }

Enemy::~Enemy() { }

bool Enemy::Start(std::string modelName, const MaterialManager::Material* material, b2World* world)
{
	// Starting entity variables (including hitbox)
	Entity::Start(modelName, material, world, glm::vec2(0, -20), glm::vec2(ENEMY_SIZE_X, ENEMY_SIZE_Y), b2_dynamicBody, b2Shape::e_polygon, ENEMY_DENSITY, ENEMY_FRICTION);

	// Setting starting variables
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z);

	// Creating model
	model = new Model();
	if (model == nullptr) return false;
	if (!model->Start(modelName)) return false;

	this->material = material;
	model->BuildQuadTexture();

	hitbox->getBody()->SetUserData(this);

	return true;
}

void Enemy::Update(GLint deltaT, b2Vec2 playerPos)
{
	// Getting user input
	Movement(playerPos);

	// Updating animation texture
	updateAnimation(deltaT);

	// Correcting texture to hitbox
	Entity::Update(deltaT);
}

void Enemy::Movement(b2Vec2 playerPos)
{
	//// Positioning
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	//{
	//	hitbox->getBody()->ApplyForceToCenter(b2Vec2(ENEMY_VEL_X, 0), true);
	//	directionIsRight = false;
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	//{
	//	hitbox->getBody()->ApplyForceToCenter(b2Vec2(-ENEMY_VEL_X, 0), true);
	//	directionIsRight = true;
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	//{
	//	hitbox->getBody()->ApplyForceToCenter(b2Vec2(0, -ENEMY_VEL_Y), true);
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	//{
	//	hitbox->getBody()->ApplyForceToCenter(b2Vec2(0, ENEMY_VEL_Y), true);
	//}
	//
	//
	//// Move in Z axis
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) position.z += 0.15f;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) position.z -= 0.15f;
	//
	//// Scaling
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) scale += 0.025f;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G)) scale -= 0.025f;
	//
	//// Rotation in X
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) rotation.x += 2.f;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) rotation.x -= 2.f;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) rotation.y += 2.f;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) rotation.y -= 2.f;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Y)) rotation.z += 2.f;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) rotation.z -= 2.f;

	if (playerPos.x < hitbox->getBody()->GetPosition().x - 0.1f)
	{
		hitbox->getBody()->ApplyForceToCenter(b2Vec2( -ENEMY_VEL_X, hitbox->getBody()->GetLinearVelocity().y), true );
		directionIsRight = true;
	}
	else if (playerPos.x > hitbox->getBody()->GetPosition().x + 0.1f)
	{
		hitbox->getBody()->ApplyForceToCenter(b2Vec2( ENEMY_VEL_X, hitbox->getBody()->GetLinearVelocity().y), true );
		directionIsRight = false;
	}

	// Thresholds in velocity
	if (hitbox->getBody()->GetLinearVelocity().x > ENEMY_MAX_VEL_X) hitbox->getBody()->SetLinearVelocity(b2Vec2(ENEMY_MAX_VEL_X, hitbox->getBody()->GetLinearVelocity().y));
	if (hitbox->getBody()->GetLinearVelocity().x < -ENEMY_MAX_VEL_X) hitbox->getBody()->SetLinearVelocity(b2Vec2(-ENEMY_MAX_VEL_X, hitbox->getBody()->GetLinearVelocity().y));
	if (hitbox->getBody()->GetLinearVelocity().y > ENEMY_MAX_VEL_Y) hitbox->getBody()->SetLinearVelocity(b2Vec2(hitbox->getBody()->GetLinearVelocity().x, ENEMY_MAX_VEL_Y));
	if (hitbox->getBody()->GetLinearVelocity().y < -ENEMY_MAX_VEL_Y) hitbox->getBody()->SetLinearVelocity(b2Vec2(hitbox->getBody()->GetLinearVelocity().x, -ENEMY_MAX_VEL_Y));
}

b2Body* Enemy::getBody()
{
	return hitbox->getBody();
}