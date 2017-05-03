#include "ProjectileHandler.h"


ProjectileHandler::ProjectileHandler(b2World *world, GLuint shader)
{
	this->dirInt = 0;
}

ProjectileHandler::ProjectileHandler() {}

ProjectileHandler::~ProjectileHandler()
{
}

void ProjectileHandler::Update(GLint deltaT, b2World* world, glm::vec2 position)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		myProjtileVector.push_back(new Projectile(world, shader));
		dirInt = 1;
		myProjtileVector.back()->fireBullet(world, position, dirInt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		myProjtileVector.push_back(new Projectile(world, shader));
		dirInt = 2;
		myProjtileVector.back()->fireBullet(world, position, dirInt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		myProjtileVector.push_back(new Projectile(world, shader));
		dirInt = 3;
		myProjtileVector.back()->fireBullet(world, position, dirInt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		myProjtileVector.push_back(new Projectile(world, shader));
		dirInt = 4;
		myProjtileVector.back()->fireBullet(world, position, dirInt);
	}

	for (int i = 0; i < myProjtileVector.capacity(); i++)
		myProjtileVector.at(i)->Update(deltaT);
}