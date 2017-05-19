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

//void ProjectileHandler::initiateProjectiles(b2World *world, GLuint shader)
//{
//	this->wasPressed = false;
//	this->CAP = 5;
//	this->currentBullet = CAP - 1;
//	this->myProjectiles = new Projectile*[this->CAP];
//
//	for (int i = 0; i < this->CAP; i++)
//		this->myProjectiles[i] = new Projectile(world, shader);
//}

void ProjectileHandler::initiateProjectiles(const MeshManager::Mesh* mesh, const MaterialManager::Material * material, b2World *world, glm::vec2 pos)
{
	this->wasPressed = false;
	this->CAP = 5;
	this->nrOfProjectiles = 0;
	this->currentBullet = CAP;
	this->myShader = shader;

	for (int i = 0; i < this->CAP; i++)
		myProjtileVector.push_back(new Projectile(mesh, material, world, pos));
		//myProjtileVector.push_back(new Projectile(world, myShader, pos));
}

ProjectileHandler::ProjectileHandler() {}

ProjectileHandler::ProjectileHandler(const MeshManager::Mesh* mesh, const MaterialManager::Material * material, b2World *world, glm::vec2 pos)
{
	this->initiateProjectiles(mesh, material, world, pos);

	//for (int i = 0; i < CAP; i++)
	//{
	//	myProjtileVector.push_back(new Projectile(world, myShader));
	//	this->nrOfBullets++;
	//}
}

ProjectileHandler::~ProjectileHandler()
{
	/*for (int i = 0; i < CAP; i++)
	{
		delete this->myProjectiles[i];
	}
	delete[]this->myProjectiles;*/
}

void ProjectileHandler::Update(GLint deltaT, b2World* world, glm::vec2 position)
{
	this->isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if (isPressed && !wasPressed)
	{
		this->wasPressed = true;
		std::cout << "Something will happen!!!" << std::endl;

		//
		//myProjtileVector[nrOfProjectiles]->fireBullet(world, position, fromScreenToNDC(glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y), glm::vec2{ 1280, 720 }, glm::vec2{ 320, 180 }));
		this->nrOfProjectiles++;
		//
		//myProjtileVector.back()->fireBullet(world, position, fromScreenToNDC(glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y), glm::vec2{ 1280, 720 }, glm::vec2{ 320, 180 }));
		//myProjtileVector.pop_back();
	}

	for (int i = 0; i < CAP; i++)
	{
		if (myProjtileVector[i]->getIsFired() == true)
		{
			myProjtileVector[i]->Update(deltaT, world, glm::vec3(position.x, position.y, 0.5f));
		}
		else
		{
			//myProjtileVector[i]->setPosition(position);
		}
	}

	this->wasPressed = isPressed;
}

void ProjectileHandler::addProjectile(b2World* world)
{
	//myProjtileVector.push_back(new Projectile(world, myShader));
}

int ProjectileHandler::getNrOffProjectiles()const
{
	return this->nrOfProjectiles;
}

int ProjectileHandler::getCAP()const
{
	return this->CAP;
}
//std::vector<Projectile*> ProjectileHandler::getBullets()
//{
//	return projectileVector;
//}