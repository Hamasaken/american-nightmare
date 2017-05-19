#include "Enemy.h"

Enemy::Enemy() : Animation() { }

Enemy::Enemy(const Enemy & other) { }

Enemy::~Enemy() { }

bool Enemy::Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, b2World* world)
{
	// Starting entity variables (including hitbox)
	Entity::Start(mesh, material, world, glm::vec2(0, 20), glm::vec3(ENEMY_SIZE_X, ENEMY_SIZE_Y, 1.f), b2_dynamicBody, b2Shape::e_polygon, true, ENEMY_MASS, ENEMY_FRICTION);

	// Setting starting variables
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(ENEMY_SIZE_X, ENEMY_SIZE_Y, ENEMY_SIZE_Z);
	damage = 1.f;

	// Setting a self-pointer for collision detection
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
	if (playerPos.x < hitbox->getBody()->GetPosition().x - 0.3f)
	{
		hitbox->getBody()->ApplyForceToCenter(b2Vec2( -ENEMY_VEL_X, hitbox->getBody()->GetLinearVelocity().y), true );
		directionIsRight = true;
	}
	else if (playerPos.x > hitbox->getBody()->GetPosition().x + 0.3f)
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

float Enemy::getDamage()
{
	return damage;
}
