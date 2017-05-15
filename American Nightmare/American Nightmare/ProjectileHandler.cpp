#include "ProjectileHandler.h"
#include <iostream>

//ProjectileHandler::ProjectileHandler(b2World* world, GLuint shader, int CAP)
//{
//	this->dirInt = 0;
//	this->myShader = shader;
//	this->wasPressed = false;
//	this->nrOfBullets = 0;
//	this->CAP = CAP;
//
//	//for (int i = 0; i < CAP; i++)
//	//{
//	//	myProjtileVector.push_back(new Projectile(world, myShader));
//	//	this->nrOfBullets++;
//	//}
//}

void ProjectileHandler::initiateProjectiles(b2World *world, GLuint shader)
{
	this->wasPressed = false;
	this->CAP = 5;
	this->currentBullet = CAP - 1;
	this->myProjectiles = new Projectile*[this->CAP];

	for (int i = 0; i < this->CAP; i++)
		this->myProjectiles[i] = new Projectile(world, shader);
}

ProjectileHandler::ProjectileHandler() {}

ProjectileHandler::ProjectileHandler(b2World *world, GLuint shader)
{
	this->initiateProjectiles(world, shader);

	//for (int i = 0; i < CAP; i++)
	//{
	//	myProjtileVector.push_back(new Projectile(world, myShader));
	//	this->nrOfBullets++;
	//}
}

//ProjectileHandler::ProjectileHandler() {}

ProjectileHandler::~ProjectileHandler()
{
	for (int i = 0; i < CAP; i++)
	{
		delete this->myProjectiles[i];
	}
	delete[]this->myProjectiles;
}

void ProjectileHandler::Update(GLint deltaT, b2World* world, glm::vec2 position)
{
	this->isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if (isPressed && !wasPressed)
	{
		this->wasPressed = true;
		std::cout << "Something will happen!!!" << std::endl;

		//
		//myProjtileVector[nrOfBullets]->fireBullet(world, position, fromScreenToNDC(glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y), glm::vec2{ 1280, 720 }, glm::vec2{ 320, 180 }));
		//this->nrOfBullets--;
		//
		//myProjtileVector.back()->fireBullet(world, position, fromScreenToNDC(glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y), glm::vec2{ 1280, 720 }, glm::vec2{ 320, 180 }));
		//myProjtileVector.pop_back();
	}

	for (int i = 0; i < CAP; i++)
	{
		myProjectiles[i]->Update(deltaT);
	}

	this->wasPressed = isPressed;
}

void ProjectileHandler::deleteProjectiles()
{
	for (int i = 0; i < this->CAP; i++)
	{
		if (myProjectiles[i]->getmarked() == true)
		{
			delete this->myProjectiles[i];
		}
	}
}

//std::vector<Projectile*> ProjectileHandler::getBullets()
//{
//	return projectileVector;
//}