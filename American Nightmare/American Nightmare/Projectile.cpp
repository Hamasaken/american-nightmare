#include "Projectile.h"

Projectile::Projectile(b2World *world, GLuint shader)
{

	std::string modelPath = MODEL_PATH;
	std::string texturePath = TEXTURE_PATH;
	materialManager.AddMaterial("lightmaterial", glm::vec3(1.f), 0.f, "lighttexture", texturePath + "gammal-dammsugare.jpg");
		
	setShader(shader);
	Start(modelPath + "model.m", materialManager.getMaterial("lightmaterial"), world, glm::vec2(0, 0), glm::vec2(0.5f, 0.5f), b2_dynamicBody, b2Shape::e_circle, 1.f, 0.5f);
	setScale(glm::vec3(0.25f, 0.25f, 1));

	isFired = false;
}

Projectile::Projectile(){}

Projectile::~Projectile()
{
	hitbox->Stop();
}

bool Projectile::getIsFired()
{
	return isFired;
}

void Projectile::fireBullet(b2World* world, glm::vec2 position, glm::vec2 direction)
{	
	hitbox->InitializeHitbox(world, glm::vec2(position.x + 2, position.y), glm::vec2(0.25f, 0.25f), b2_dynamicBody);
	hitbox->getBody()->ApplyLinearImpulseToCenter({direction.x * 50000.f, direction.y * 50000.f }, true);
}



//void Projectile::fireBullet(b2World* world, glm::vec2 position, int dirInt)
//{
//	if (dirInt == 1)
//	{
//		hitbox->InitializeHitbox(world, glm::vec2(position.x + 2, position.y), glm::vec2(0.5f, 0.5f), b2_dynamicBody);
//		hitbox->getBody()->ApplyLinearImpulseToCenter({50000.f, 0 }, true);
//	}
//	if (dirInt == 2)
//	{
//		hitbox->InitializeHitbox(world, glm::vec2(position.x - 2, position.y), glm::vec2(0.5f, 0.5f), b2_dynamicBody);
//		hitbox->getBody()->ApplyLinearImpulseToCenter({ -50000.f, 0 }, true);
//	}
//	if (dirInt == 3)
//	{
//		hitbox->InitializeHitbox(world, glm::vec2(position.x, position.y - 2), glm::vec2(0.5f, 0.5f), b2_dynamicBody);
//		hitbox->getBody()->ApplyLinearImpulseToCenter({ 0, -50000.f }, true);
//	}
//	if (dirInt == 4)
//	{
//		hitbox->InitializeHitbox(world, glm::vec2(position.x, position.y + 2), glm::vec2(0.5f, 0.5f), b2_dynamicBody);
//		hitbox->getBody()->ApplyLinearImpulseToCenter({ 0, 50000.f }, true);
//	}
//}

void Projectile::Update(GLint deltaT,b2World* world, glm::vec2 position)
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
		fireBullet(world, position, 2);*/

	Entity::Update(deltaT);
}

void Projectile::Update(GLint deltaT)
{
	Entity::Update(deltaT);
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
