#include "Entity.h"

bool Entity::Start(const MeshManager::Mesh* mesh, const MaterialManager::Material * material, b2World* world)
{
	Object::Start(mesh, material);

	hitbox = new Hitbox();
	if (hitbox == nullptr) return false;
	if (!hitbox->InitializeHitbox(world))
		return false;

	hitbox->getBody()->SetUserData(this);

	return true;
}

bool Entity::Start(const MeshManager::Mesh* mesh, const MaterialManager::Material * material, b2World* world, b2Body* player)
{
	Object::Start(mesh, material);
	hitbox = new Hitbox();

	//if (hitbox == nullptr) return false;
	//if (!hitbox->InitializeHitbox(world))
	//	return false;

	if (!hitbox->InitializeHitboxVacuum(world, player))

		hitbox->getBody()->SetUserData(this);

	return true;
}

bool Entity::Start(const MeshManager::Mesh* mesh, const MaterialManager::Material * material, b2World * world, glm::vec2 position, glm::vec3 size, b2BodyType type, b2Shape::Type shapeType, bool fixedRotate, float density, float friction)
{
	Object::Start(mesh, material);

	hitbox = new Hitbox();
	if (hitbox == nullptr) return false;
	if (!hitbox->InitializeHitbox(world, position, size, type, shapeType, fixedRotate, density, friction))
		return false;

	// Updating size
	this->scale = size;

	hitbox->getBody()->SetUserData(this);

	return false;

	return true;
}

void Entity::Stop()
{
	if (hitbox != nullptr)
	{
		hitbox->Stop();
		delete hitbox;
		hitbox = nullptr;
	}
}

void Entity::Update(GLint deltaT)
{
	// Update the texture position
	position.x = hitbox->getPosition().x;
	position.y = hitbox->getPosition().y;
	rotation.z = hitbox->getBody()->GetAngle();

	Object::Update(deltaT);
}

void Entity::setPosition(glm::vec3 position) { this->position = position; }
void Entity::setScale(glm::vec3 scale) { this->scale = scale; }
Hitbox * Entity::getHitbox() { return hitbox; }
