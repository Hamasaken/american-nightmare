#include "Entity.h"

bool Entity::Start(const MeshManager::Mesh* mesh, const MaterialManager::Material * material, b2World* world)
{
	Object::Start(mesh, material);
	this->world = world;

	hitbox = new Hitbox();
	if (hitbox == nullptr) return false;
	if (!hitbox->InitializeHitbox(world))
		return false;

	hitbox->getBody()->SetUserData(this);

	return true;
}

bool Entity::Start(b2World* world, b2Body* player)
{
	//Object::Start(mesh, material);
	this->world = world;

	hitbox = new Hitbox();
	if (hitbox == nullptr) return false;
	if (!hitbox->InitializeHitboxVacuum(world, player))
		return false;

	hitbox->getBody()->SetUserData(this);

	return true;
}

bool Entity::Start(const MeshManager::Mesh* mesh, const MaterialManager::Material * material, b2World * world, glm::vec2 position, glm::vec3 size, b2BodyType type, b2Shape::Type shapeType, bool fixedRotate, float mass, float friction)
{
	Object::Start(mesh, material);
	this->world = world;

	hitbox = new Hitbox();
	if (hitbox == nullptr) return false;
	if (!hitbox->InitializeHitbox(world, position, size, type, shapeType, fixedRotate, mass, friction))
		return false;

	// Updating size
	this->scale = size;

	hitbox->getBody()->SetUserData(this);

	return true;
}

void Entity::Stop()
{
	if (hitbox != nullptr)
	{
		hitbox->Stop(world);
		delete hitbox;
		hitbox = nullptr;
	}
}

void Entity::Update(GLint deltaT)
{
	// Update the texture position
	position.x = hitbox->getPosition().x;
	position.y = hitbox->getPosition().y;
	rotation.z = -hitbox->getBody()->GetAngle();

	Object::Update(deltaT);
}

void Entity::setPosition(glm::vec3 position) { this->position = position; hitbox->getBody()->SetTransform(b2Vec2(position.x, position.y), -hitbox->getBody()->GetAngle()); }
void Entity::setScale(glm::vec3 scale) { 
	this->scale = scale; 
//	hitbox->getBody()->DestroyFixture(hitbox->getBody()->GetFixtureList());
	// remove fixture and then make a new one by calling ONLY the modifyShape function in hitbox, 
	// complete this function later as we're not really needing this right now
}
Hitbox * Entity::getHitbox() { return hitbox; }
