#ifndef PROJECTILEHANDLER_H
#define PROJECTILEHANDLER_H

#include "Projectile.h"
#include "Accessories.h"
#include <SDL.h>

class ProjectileHandler : public Entity
{
private:
	/*std::vector <Projectile*> myProjtileVector;
	GLuint myShader;
	bool wasPressed;
	bool isPressed;
	int nrOfBullets;
	int CAP;*/
	//Variables for shooting
	bool wasPressed;
	bool isPressed;

	//Variables for ProjectileHandler
	int currentBullet;
	int CAP;
	sf::Vector2f projectileVector[5];
	Projectile* *myProjectiles;
	void initiateProjectiles(b2World *world, GLuint shader);

public:
	//ProjectileHandler(b2World* world, GLuint shader, int CAP = 10);
	ProjectileHandler(b2World *world, GLuint shader);
	ProjectileHandler();
	~ProjectileHandler();

	void Update(GLint deltaT, b2World* world, glm::vec2 position);
	void deleteProjectiles();
	//std::vector<Projectile*> getBullets();
};

#endif
