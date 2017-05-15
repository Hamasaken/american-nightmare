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

	MaterialManager materialManager;

	int damage;
	bool damageOn;
	bool marked;

public:
	Projectile(b2World *world, GLuint shader);
	Projectile();
	~Projectile();

	void fireBullet(b2World* world, glm::vec2 position, glm::vec2 direction);

	b2Vec2 normalize(const b2Vec2& source);

	void setDamageOn(bool damageOn);
	bool getDamageOn()const;

	void setmarked(bool marked);
	bool getmarked()const;

	void Update(GLint deltaT);
	void Update(GLint deltaT, b2World* world, glm::vec2 position);
};

#endif // !PROJECTILE_H
