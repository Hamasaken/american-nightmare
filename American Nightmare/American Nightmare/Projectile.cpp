#include "Projectile.h"

Projectile::Projectile(const MeshManager::Mesh* mesh, const MaterialManager::Material * material, b2World *world, glm::vec2 pos)
{
	Entity::Start(mesh, material, world, pos, glm::vec3(1.0, 1.0, 1.0), b2BodyType::b2_dynamicBody, b2Shape::e_circle, true, 1.0, 0.25);
	
	this->damage = 10;
	this->damageOn = false;
	this->marked = false;
}

Projectile::Projectile(){}

Projectile::~Projectile()
{
	hitbox->Stop();
}

void Projectile::fireBullet(b2World* world, glm::vec2 position, glm::vec2 direction)
{	
	hitbox->getBody()->ApplyLinearImpulseToCenter({direction.x * 500.f, direction.y * 500.f }, true);
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