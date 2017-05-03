#ifndef PROJECTILEHANDLER_H
#define PROJECTILEHANDLER_H

#include "Projectile.h"

class ProjectileHandler : public Entity
{
private:
	std::vector<Projectile*> myProjtileVector;
	GLuint myShader;

	int dirInt;
public:
	ProjectileHandler(b2World *world, GLuint shader);
	ProjectileHandler();
	~ProjectileHandler();

	void Update(GLint deltaT, b2World* world, glm::vec2 position);
};

#endif
