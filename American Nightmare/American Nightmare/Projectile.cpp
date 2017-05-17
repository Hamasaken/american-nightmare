#include "Projectile.h"

Projectile::Projectile(b2World *world, GLuint shader, glm::vec2 pos)
{
	std::string modelPath = MODEL_PATH;
	std::string texturePath = TEXTURE_PATH;
	materialManager.AddMaterial("lightmaterial", glm::vec3(1.f), 0.f, "lighttexture", texturePath + "gammal-dammsugare.jpg");
	
	this->playerPosition = pos;

	setShader(shader);
	Start(modelPath + "model.m", materialManager.getMaterial("lightmaterial"), world, playerPosition, glm::vec2(0.5f, 0.5f), b2_dynamicBody, b2Shape::e_circle, 1.f, 0.5f);
	//Start(modelPath + "model.m", materialManager.getMaterial("lightmaterial"), world, glm::vec2(0, 0), glm::vec2(0.5f, 0.5f), b2_dynamicBody, b2Shape::e_circle, 1.f, 0.5f);
	setScale(glm::vec3(0.25f, 0.25f, 1));

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
	//hitbox->InitializeHitbox(world, glm::vec2(position.x + 2, position.y), glm::vec2(0.25f, 0.25f), b2_dynamicBody);
	hitbox->getBody()->ApplyLinearImpulseToCenter({direction.x * 50000.f, direction.y * 50000.f }, true);
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

//void Projectile::Update(GLint deltaT)
//{
//	Entity::Update(deltaT);
//}

void Projectile::setIsFired(bool isProjectileFired)
{
	this->isProjectileFired = isProjectileFired;
}

bool Projectile::getIsFired()const
{
	return this->isProjectileFired;
}