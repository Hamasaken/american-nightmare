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

ProjectileHandler::ProjectileHandler(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos, GLuint shader, glm::vec2 screenPos, glm::vec2 screenSize)
{
	this->initiateProjectiles(mesh, material, world, pos, shader);

	this->screenSize = screenSize;
	this->screenPos = screenPos;
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
			world->DestroyBody(temp->getHitbox()->getBody());
			temp->Stop();
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

void ProjectileHandler::UpdateScreenProperties(glm::vec2 screenSize, glm::vec2 screenPos)
{
	this->screenPos = screenPos;
	this->screenSize = screenSize;
}

void ProjectileHandler::fireProjectiles(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos)
{
	glm::vec2 direction = fromScreenToNDC(glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y + 150), screenSize, screenPos);

	direction = glm::normalize(direction);
	Projectile* p = new Projectile(mesh, material, world, pos + glm::vec2(1.35f * direction.x, -(direction.y)));
	p->setShader(myShader);
	myProjtileVector.push_back(p);
	myProjtileVector.back()->fireBullet(world, pos, direction);
}
