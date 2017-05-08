#ifndef PROJECTILEHANDLER_H
#define PROJECTILEHANDLER_H

#include "Projectile.h"

class ProjectileHandler : public Entity
{
private:
	//Projectile* *myProjectiles;
	//int nrOfProjectiles;
	//int CAP;
	//
	//Help functions
	//void expand();
	//void freeMemory();
	//void initiateFrom(int from = 0);
	//void addProjectile(b2World* world);


	Projectile *tempProj;
	GLuint myShader;
	int dirInt;
	std::vector<Projectile*> myProjtileVector;
public:
	ProjectileHandler(b2World *world, GLuint shader, int CAP = 10);
	ProjectileHandler();
	~ProjectileHandler();

	void Update(GLint deltaT, b2World* world, glm::vec2 position);

	std::vector<Projectile*> getBullets();
};

#endif
