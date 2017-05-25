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

ProjectileHandler::ProjectileHandler(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, SoundManager* soundManager, ParticleManager* particleManager, glm::vec2 pos, GLuint shader, glm::vec2 screenPos, glm::vec2 screenSize)
{
	this->initiateProjectiles(mesh, material, world, pos, shader);

	this->particleManager = particleManager;
	this->soundManager = soundManager;
	this->screenSize = screenSize;
	this->screenPos = screenPos;
}

ProjectileHandler::~ProjectileHandler()
{
}

void ProjectileHandler::Update(GLint deltaT, b2World* world, glm::vec2 position, bool ammoFull)
{
	deleteProjects(world);
	for (int i = 0; i < this->myProjtileVector.size(); i++)
	{
		Projectile* p = myProjtileVector[i];
		if (abs(p->getHitbox()->getBody()->GetLinearVelocity().x) > 5.f && rand() % 2 == 1)
			particleManager->EffectSmokeCloud(p->getPosition(), 0, 1);
		p->Update(deltaT, world, glm::vec3(position.x, position.y, 0.5f));
	}
	
	if (!ammoFull)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			soundManager->playSFXOverDrive(SoundManager::SFX_HOVER, 15, 0.25f);
			for (int i = 0; i < this->myProjtileVector.size(); i++)
			{
				if (this->myProjtileVector[i]->getIsInVacRange() == true)
				{
					soundManager->playSFXOverDrive(SoundManager::SFX_HOVER, 40, 0.25f);
					float angle = getAngleFromTwoPoints(glm::vec3(position, 0), this->myProjtileVector[i]->getPosition());
					this->myProjtileVector[i]->getHitbox()->getBody()->ApplyForceToCenter(b2Vec2(cos(angle) * 500.f, -sin(angle) * 500.f), true);
				}
			}
		}
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

void ProjectileHandler::fireProjectiles(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos, bool isJumping, bool isCircle)
{
	glm::vec2 direction = fromScreenToNDC(glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y - 150), screenSize, screenPos);
	direction = glm::normalize(direction);

	if (direction.y > 0.f && abs(direction.x) < 0.5f && !isJumping)
	{
		return;
	}

	Projectile* p = new Projectile(mesh, material, world, pos + glm::vec2(1.35f * direction.x, -(direction.y) * 1.5f), isCircle);
	p->setShader(myShader);
	myProjtileVector.push_back(p);
	myProjtileVector.back()->fireBullet(world, pos, direction);
}
