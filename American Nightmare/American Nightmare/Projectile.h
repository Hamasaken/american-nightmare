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

	bool isFired;

	MaterialManager materialManager;

	bool right = false;
	bool left = false;
	bool up = false;
	bool down = false;

public:
	Projectile(b2World *world, GLuint shader);
	Projectile();
	~Projectile();

	void fireBullet(b2World* world, glm::vec2 position, int dirInt);
	b2Vec2 normalize(const b2Vec2& source);
	bool getIsFired();

	void Update(GLint deltaT);
	void Update(GLint deltaT, b2World* world, glm::vec2 position);
};

#endif // !PROJECTILE_H
