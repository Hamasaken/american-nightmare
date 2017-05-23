#include "ProjectileHandler.h"
#include <iostream>

void ProjectileHandler::initiateProjectiles(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos, GLuint shader)
{
	
	this->myShader = shader;
	this->myMesh =  const_cast<MeshManager::Mesh*>(mesh);
	this->myMaterial = const_cast<MaterialManager::Material*>(material);
	/*this->mymaterial = const_cast<Materialmanager::Material*>(material);*/
	
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
	/*for (int i = 0; i < CAP; i++)
	{
		delete this->myProjectiles[i];
	}
	delete[]this->myProjectiles;*/
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
			delete temp;
			temp = nullptr;
			myProjtileVector.erase(myProjtileVector.begin() + i);
			i--;
		}
	}
}


std::vector<Projectile*> ProjectileHandler::getBullets()
{
	return myProjtileVector;
}

void ProjectileHandler::fireProjectiles(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos)
{
	glm::vec2 direction = fromScreenToNDC(glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y), glm::vec2(1280, 720), glm::vec2(320, 180));
	direction = glm::normalize(direction);
	Projectile* p = new Projectile(mesh, material, world, pos + glm::vec2(3 * direction.x, 3 * -(direction.y)));
	p->setShader(myShader);
	myProjtileVector.push_back(p);
	myProjtileVector.back()->fireBullet(world, pos, direction);
}
