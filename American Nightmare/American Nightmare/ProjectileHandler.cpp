#include "ProjectileHandler.h"


ProjectileHandler::ProjectileHandler(b2World *world, GLuint shader)
{
	this->myProjectiles = new Projectile[CAP];

	for (int i = 0; i < this->CAP; i++)
		this->myProjectiles[i] =  Projectile(world, shader);
}

ProjectileHandler::~ProjectileHandler()
{
}

void ProjectileHandler::Update(GLint deltaT, b2World* world)
{
	for (int i = 0; i < this->CAP; i++)
	{
		if (this->myProjectiles[i].getIsFired() == true)
			this->myProjectiles[i].Update(deltaT);
	}
}