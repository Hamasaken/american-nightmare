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

void ProjectileHandler::initiateProjectiles(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos)
{
	this->wasPressed = false;
	this->myShader = shader;
	this->myMesh =  const_cast<MeshManager::Mesh*>(mesh);
	this->myMaterial = const_cast<MaterialManager::Material*>(material);
	this->isPressed = false;
	/*for (int i = 0; i < this->myProjtileVector.size(); i++)
		myProjtileVector.push_back(new Projectile(myMesh, myMaterial, world, pos));*/
		//myProjtileVector.push_back(new Projectile(world, myShader, pos));
}

ProjectileHandler::ProjectileHandler() {}

ProjectileHandler::ProjectileHandler(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos)
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
		//std::cout << "Something will happen!!!" << std::endl;
		myProjtileVector.push_back(new Projectile(myMesh, myMaterial, world, position));
		myProjtileVector.back()->fireBullet(world, position, fromScreenToNDC(glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y), glm::vec2{ 1280, 720 }, glm::vec2{ 320, 180 }));
	}

	for (int i = 0; i < this->myProjtileVector.size(); i++)
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

void ProjectileHandler::deleteProjects(b2World* world)
{
	cout << this->myProjtileVector.size() << endl;
	for (int i = 0; i < this->myProjtileVector.size(); i++)
	{
		if (this->myProjtileVector[i]->getmarked() == true)
		{
			Projectile* temp = this->myProjtileVector[i];
			//temp = this->projectiles[i];
			this->myProjtileVector[i] = this->myProjtileVector.back();
			this->myProjtileVector.back() = temp;
			//this->projectiles.back()->~Projectile();
			world->DestroyBody(this->myProjtileVector.back()->getHitbox()->getBody());
			this->myProjtileVector.pop_back();
		}
	}
}


std::vector<Projectile*> ProjectileHandler::getBullets()
{
	return myProjtileVector;
}