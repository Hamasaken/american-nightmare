#include "ProjectileHandler.h"


//ProjectileHandler::ProjectileHandler(b2World *world, GLuint shader, int CAP)
//{
//	this->dirInt = 0;
//	this->myShader = shader;
//	this->nrOfProjectiles = 0;
//	this->CAP = CAP;
//	this->myProjectiles = new Projectile*[this->CAP];
//	this->initiateFrom();
//}
//
//ProjectileHandler::ProjectileHandler() {}
//
//ProjectileHandler::~ProjectileHandler()
//{
//	freeMemory();
//}
//
//void ProjectileHandler::expand()
//{
//	this->CAP += 10;
//	Projectile* *temp = new Projectile*[this->CAP];
//
//	for (int i = 0; i < this->nrOfProjectiles; i++)
//	{
//		temp[i] = this->myProjectiles[i];
//	}
//	delete[] this->myProjectiles;
//	myProjectiles = temp;
//}
//
//void ProjectileHandler::freeMemory()
//{
//	for (int i = 0; i < this->nrOfProjectiles; i++)
//	{
//		delete[] this->myProjectiles[i];
//	}
//	delete[] myProjectiles;
//}
//
//void ProjectileHandler::initiateFrom(int from)
//{
//	for (int i = from; i < CAP; i++)
//	{
//		this->myProjectiles[i] = nullptr;
//	}
//}
//
//void ProjectileHandler::addProjectile(b2World* world)
//{
//	if (CAP == this->nrOfProjectiles)
//		expand();
//
//	this->myProjectiles[this->nrOfProjectiles] = new Projectile(world, myShader);
//	this->nrOfProjectiles++;
//}
//
//void ProjectileHandler::Update(GLint deltaT, b2World* world, glm::vec2 position)
//{
//	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//	{
//		addProjectile(world);
//		myProjectiles[this->nrOfProjectiles]->fireBullet(world, position, 2);
//	}
//
//	for (int i = 0; i < this->nrOfProjectiles; i++)
//		this->myProjectiles[i]->Update(deltaT);
//}

ProjectileHandler::ProjectileHandler(b2World *world, GLuint shader, int CAP)
{
	this->dirInt = 0;
	this->myShader = shader;

	//this->tempProj = new Projectile(world, myShader);
	//myProjtileVector.push_back(tempProj);
}

ProjectileHandler::ProjectileHandler() {}

ProjectileHandler::~ProjectileHandler()
{
	//for (int i = 0; i < myProjtileVector.size(); i++)
	//myProjtileVector[i] = myProjtileVector.erase();
}

void ProjectileHandler::Update(GLint deltaT, b2World* world, glm::vec2 position)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		myProjtileVector.push_back(new Projectile(world, myShader));
		dirInt = 1;
		myProjtileVector.back()->fireBullet(world, position, dirInt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		myProjtileVector.push_back(new Projectile(world, myShader));
		dirInt = 2;
		myProjtileVector.back()->fireBullet(world, position, dirInt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		myProjtileVector.push_back(new Projectile(world, myShader));
		dirInt = 3;
		myProjtileVector.back()->fireBullet(world, position, dirInt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		myProjtileVector.push_back(new Projectile(world, myShader));
		dirInt = 4;
		myProjtileVector.back()->fireBullet(world, position, dirInt);
	}

	for (int i = 0; i < myProjtileVector.size(); i++)
	{
		myProjtileVector[i]->Update(deltaT);
	}
}

//void ProjectileHandler::Update(GLint deltaT, b2World* world, glm::vec2 position)
//{
//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//	{
//		myProjtileVector.push_back( Projectile(world, myShader));
//		dirInt = 1;
//		myProjtileVector.back().fireBullet(world, position, dirInt);
//	}
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//	{
//		myProjtileVector.push_back( Projectile(world, myShader));
//		dirInt = 2;
//		myProjtileVector.back().fireBullet(world, position, dirInt);
//	}
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//	{
//		myProjtileVector.push_back( Projectile(world, myShader));
//		dirInt = 3;
//		myProjtileVector.back().fireBullet(world, position, dirInt);
//	}
//	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//	{
//		myProjtileVector.push_back( Projectile(world, myShader));
//		dirInt = 4;
//		myProjtileVector.back().fireBullet(world, position, dirInt);
//	}
//
//	for (int i = 0; i < myProjtileVector.size(); i++)
//	{
//		//myProjtileVector[i]->Update(deltaT);
//	}
//
//
//	printf("Nu é Jag en badboll");
//}


std::vector<Projectile*> ProjectileHandler::getBullets()
{
	return myProjtileVector;
}