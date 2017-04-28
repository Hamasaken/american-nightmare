#include "Projectile.h"

Projectile::Projectile(b2World *world, GLuint shader)
{
	std::string modelPath = MODEL_PATH;
	std::string texturePath = TEXTURE_PATH;
	materialManager.AddMaterial("lightmaterial", glm::vec3(1.f), 0.f, "lighttexture", texturePath + "gammal-dammsugare.jpg");
		
	setShader(shader);
	Start(modelPath + "model.m", materialManager.getMaterial("lightmaterial"), world, glm::vec2(0, 0), glm::vec2(0.5f, 0.5f), b2_dynamicBody, b2Shape::e_circle, 1.f, 0.5f);
	setScale(glm::vec3(0.5f, 0.5f, 1));

	isPressed = false;
}

Projectile::~Projectile()
{
}

void Projectile::fireBullet(b2World* world, glm::vec2 position)
{
	hitbox->AddBodyToWorld(world, position, b2_dynamicBody, false);
	hitbox->getBody()->ApplyLinearImpulseToCenter({500, 0 }, true);

}

void Projectile::Update(GLint deltaT,b2World* world, glm::vec2 position)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isPressed)
	{
		fireBullet(world, position);
	}

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
