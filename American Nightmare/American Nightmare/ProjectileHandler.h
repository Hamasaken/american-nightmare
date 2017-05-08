#ifndef PROJECTILEHANDLER_H
#define PROJECTILEHANDLER_H

#include "Projectile.h"

class ProjectileHandler : public Entity
{
private:
	Projectile* myProjectiles;
	const int CAP = 10;
	
public:
	ProjectileHandler(b2World *world, GLuint shader);
	ProjectileHandler();
	~ProjectileHandler();


	void Update(GLint deltaT, b2World* world);
};

#endif
