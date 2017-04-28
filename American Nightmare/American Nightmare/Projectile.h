#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML\Graphics.hpp>
#include "Game\Entity.h"
#include <Box2D.h>
#include "Game\Hitbox.h"

class Projectile : public Entity
{
private:
	std::string modelPath;
	std::string texturePath;

	bool isPressed;

	MaterialManager materialManager;
public:
	Projectile(b2World *world, GLuint shader);
	~Projectile();

	void fireBullet(b2World* world, glm::vec2 position);
	b2Vec2 normalize(const b2Vec2& source);

	void Update(GLint deltaT, b2World* world, glm::vec2 position);
};

#endif // !PROJECTILE_H

//
//void Bullet::move(float gameTime, sf::Vector2f playerPos)
//{
//	sf::Vector2f thisPosition = mSprite.getPosition();
//	sf::Vector2f direction = normalize(playerPos - thisPosition);
//
//	mSprite.move(direction * mSpeed * gameTime);
//}
//
//void Bullet::setToIdel()
//{
//	this->idle = true;
//	this->mSprite.setPosition(-50, -50);
//	this->aDirection = sf::Vector2f(0.0, 0.0);
//}
//
//sf::Vector2f Bullet::normalize(const sf::Vector2f& source)
//{
//	float length = sqrt((source.x * source.x) + (source.y * source.y));
//
//	if (length != 0)
//	{
//		return sf::Vector2f(source.x / length, source.y / length);
//	}
//	else
//	{
//		return source;
//	}
//}
