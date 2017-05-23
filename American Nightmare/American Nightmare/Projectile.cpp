#include "Projectile.h"

Projectile::Projectile(const MeshManager::Mesh* mesh, const MaterialManager::Material * material, b2World *world, glm::vec2 pos)
{
	Entity::Start(mesh, material, world, pos, glm::vec3(BULLET_SIZE_X, BULLET_SIZE_Y, BULLET_SIZE_Z), b2BodyType::b2_dynamicBody, b2Shape::e_polygon, false, 0.5f, 0.25);

	this->scale = glm::vec3(BULLET_SIZE_X, BULLET_SIZE_Y, BULLET_SIZE_Z);
	this->damage = 10;
	this->damageOn = false;
	this->marked = false;
}

Projectile::Projectile() { }

Projectile::~Projectile() { }

void Projectile::fireBullet(b2World* world, glm::vec2 position, glm::vec2 direction)
{	
	hitbox->getBody()->ApplyLinearImpulseToCenter({direction.x * 50.f, direction.y * 50.f }, true);
}

b2Vec2 Projectile::normalize(const b2Vec2& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));

	if (length != 0)
	{
		return b2Vec2(source.x / length, source.y / length);
	}
	else
	{
		return b2Vec2(source.x, source.y);
	}
}

void Projectile::setDamageOn(bool damageOn)
{
	this->damageOn = damageOn;
}

bool Projectile::getDamageOn()const
{
	return this->damageOn;
}

void Projectile::setmarked(bool marked)
{
	this->marked = marked;
}

bool Projectile::getmarked()const
{
	return this->marked;
}

void Projectile::Update(GLint deltaT,b2World* world, glm::vec2 position)
{
	Entity::Update(deltaT);
}

void Projectile::setIsFired(bool isProjectileFired)
{
	this->isProjectileFired = isProjectileFired;
}

bool Projectile::getIsFired()const
{
	return this->isProjectileFired;
}