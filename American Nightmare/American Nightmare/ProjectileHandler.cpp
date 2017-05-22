#include "ProjectileHandler.h"
#include <iostream>

void ProjectileHandler::initiateProjectiles(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos, GLuint shader)
{
	
	this->myShader = shader;
	/*this->mymesh =  const_cast<Meshmanager::Mesh*>(mesh);
	this->mymaterial = const_cast<Materialmanager::Material*>(material);*/
	
	/*for (int i = 0; i < 10; i++)
	{
		Projectile* p = new Projectile(mesh, material, world, pos);
		p->setShader(shader);
		myProjtileVector.push_back(p);
	}*/
	//	myProjtileVector.push_back(new Projectile(world, myShader, pos));
}

ProjectileHandler::ProjectileHandler() {}

ProjectileHandler::ProjectileHandler(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos, GLuint shader)
{
	this->initiateProjectiles(mesh, material, world, pos, shader);

}

ProjectileHandler::~ProjectileHandler()
{
	for (int i = 0; i < myProjtileVector.size(); i++)
	{
		myProjtileVector[i]->setmarked(true);
	}
	for (int i = 0; i < this->myProjtileVector.size(); i++)
	{
		if (this->myProjtileVector[i]->getmarked() == true)
		{
			Projectile* temp = this->myProjtileVector[i];
			this->myProjtileVector[i] = this->myProjtileVector.back();
			this->myProjtileVector.back() = temp;
			//this->myProjtileVector.back()->~Projectile();
			//world->DestroyBody(this->myProjtileVector.back()->getHitbox()->getBody());
			this->myProjtileVector.pop_back();
		}
	}
	myProjtileVector.clear();
}

void ProjectileHandler::Update(GLint deltaT, b2World* world, glm::vec2 position)
{

	deleteProjects(world);
	for (int i = 0; i < this->myProjtileVector.size(); i++)
	{
		myProjtileVector[i]->Update(deltaT, world, glm::vec3(position.x, position.y, 0.5f));
	}
	

	
}

void ProjectileHandler::deleteProjects(b2World* world)
{
	for (int i = 0; i < this->myProjtileVector.size(); i++)
	{
		if (this->myProjtileVector[i]->getmarked() == true)
		{
			Projectile* temp = this->myProjtileVector[i];
			this->myProjtileVector[i] = this->myProjtileVector.back();
			this->myProjtileVector.back() = temp;
			//this->myProjtileVector.back()->~Projectile();
			//world->DestroyBody(this->myProjtileVector.back()->getHitbox()->getBody());
			this->myProjtileVector.pop_back();
		}
	}
}


std::vector<Projectile*> ProjectileHandler::getBullets()
{
	return myProjtileVector;
}

void ProjectileHandler::fireProjectiles(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos)
{
	Projectile* p = new Projectile(mesh, material, world, pos);
	p->setShader(myShader);
	myProjtileVector.push_back(p);
	myProjtileVector.back()->fireBullet(world, pos, fromScreenToNDC(glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y), glm::vec2{ 1920, 1080 }, glm::vec2{ 0, 0 }));
}
