#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML\Graphics.hpp>
#include "Game\Entity.h"
#include <Box2D.h>
#include "Game\Hitbox.h"

class Projectile 
{
private:
	sf::Mouse myMouse;
	b2Vec2 myVec;

	//b2BodyDef bodyDef;
	//b2Body body;
	b2CircleShape shape;
	b2FixtureDef fixtureDef;

public:
	Projectile();
	~Projectile();

	void fireBullet();
};


#endif // !PROJECTILE_H

