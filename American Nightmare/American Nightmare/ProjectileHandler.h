#ifndef PROJECTILEHANDLER_H
#define PROJECTILEHANDLER_H

#include "Projectile.h"
#include "Accessories.h"

class ProjectileHandler : public Entity
{
private:
	Projectile *tempProj;
	std::vector<Projectile*> myProjtileVector;

	GLuint myShader;
	int dirInt;
	bool wasPressed;
	bool isPressed;

public:
	ProjectileHandler(b2World *world, GLuint shader, int CAP = 10);
	ProjectileHandler();
	~ProjectileHandler();

	void Update(GLint deltaT, b2World* world, glm::vec2 position);

	std::vector<Projectile*> getBullets();
};

#endif
