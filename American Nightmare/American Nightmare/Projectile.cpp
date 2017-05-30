#include "Projectile.h"

Projectile::Projectile(const MeshManager::Mesh* mesh, const MaterialManager::Material * material, b2World *world, glm::vec2 pos, bool isCircle)
{
	Entity::Start(mesh, material, world, pos, glm::vec3(BULLET_SIZE_X, BULLET_SIZE_Y, BULLET_SIZE_Z), b2BodyType::b2_dynamicBody, ((isCircle) ? b2Shape::e_circle : b2Shape::e_polygon), false, BULLET_MASS, 1.);
	this->scale = glm::vec3(BULLET_SIZE_X, BULLET_SIZE_Y, BULLET_SIZE_Z);
	hitbox->getBody()->SetSleepingAllowed(true);

	this->hitbox->getBody()->SetUserData(this);

	this->damage = 10;
	this->damageOn = false;
	this->marked = false;
	this->isInVacRange = false;
	this->isZombiePart = false;

	// If the material is in anyway a zombie part (for blood smoke instead of smoke smoke)
	if (material->name.find("zombie") != std::string::npos)
		isZombiePart = true;

	this->projectileData = ProjectileData(mesh, material, isCircle);
}

Projectile::Projectile() {}

Projectile::~Projectile() { }

void Projectile::fireBullet(glm::vec2 position, glm::vec2 direction)
{	
	hitbox->getBody()->ApplyLinearImpulseToCenter({direction.x * 75.f, direction.y * 75.f }, true);
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

ProjectileData Projectile::getProjectileData()
{
	return projectileData;
}

void Projectile::Update(GLint deltaT,b2World* world, glm::vec2 position)
{
	Entity::Update(deltaT);
}

bool Projectile::getIsZombiePart() const
{
	return isZombiePart;
}

void Projectile::setIsFired(bool isProjectileFired)
{
	this->isProjectileFired = isProjectileFired;
}

bool Projectile::getIsFired()const
{
	return this->isProjectileFired;
}

void Projectile::setIsInVacRange(bool isInVacRange)
{
	this->isInVacRange = isInVacRange;
}

bool Projectile::getIsInVacRange()const
{
	return this->isInVacRange;
}