#include "ProjectileHandler.h"
#include <iostream>

extern MaterialManager* materialManager;

void ProjectileHandler::initiateProjectiles(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos, GLuint shader)
{
	this->world = world;
	this->myShader = shader;
	this->myMesh =  const_cast<MeshManager::Mesh*>(mesh);
	this->myMaterial = const_cast<MaterialManager::Material*>(material);
}

ProjectileHandler::ProjectileHandler() {}

ProjectileHandler::ProjectileHandler(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, SoundManager* soundManager, ParticleManager* particleManager, glm::vec2 pos, GLuint shader)
{
	this->initiateProjectiles(mesh, material, world, pos, shader);

	this->particleManager = particleManager;
	this->soundManager = soundManager;
}

ProjectileHandler::~ProjectileHandler() {}

void ProjectileHandler::Update(GLint deltaT, b2World* world, glm::vec2 position, bool ammoFull)
{
	deleteProjects(world); //Only deletes projectiles if they are marked by the Contactlistener.
	for (int i = 0; i < this->myProjtileVector.size(); i++)
	{
		Projectile* p = myProjtileVector[i];
		if (abs(p->getHitbox()->getBody()->GetLinearVelocity().x) > 5.f && rand() % 4 == 1)
		{
			if (!p->getIsZombiePart())
				particleManager->EffectSmokeCloud(p->getPosition(), materialManager->getTextureID("smoketexture"), 1, glm::vec4(0.9f), randBetweenF(0.1f, 0.35f));
			else
				particleManager->EffectSmokeCloud(p->getPosition(), materialManager->getTextureID("bloodtexture"), 1, glm::vec4(1.f), randBetweenF(0.15f, 0.35f));
		}

		float dist = abs(p->getHitbox()->getBody()->GetPosition().x - position.x);
		b2Body* body = p->getHitbox()->getBody();
		if (!body->IsAwake())
		{
			if (dist < 20.f)
				body->SetAwake(true);
		}
		else if (dist >= 20.f)
			body->SetAwake(false);

		p->Update(deltaT, world, glm::vec3(position.x, position.y, 0.5f));
	}
	
	if (!ammoFull)
	{
		if (sf::Joystick::isButtonPressed(0, 4))
		{
			soundManager->playSFXOverDrive(SoundManager::SFX_HOVER, 15, 0.25f);
			for (int i = 0; i < this->myProjtileVector.size(); i++)
			{

				if (this->myProjtileVector[i]->getIsInVacRange() == true)
				{
					soundManager->playSFXOverDrive(SoundManager::SFX_HOVER, 40, 0.25f);
					float angle = getAngleFromTwoPoints(glm::vec3(position, 0), this->myProjtileVector[i]->getPosition());
					this->myProjtileVector[i]->getHitbox()->getBody()->ApplyForceToCenter(b2Vec2(cos(angle) * 125.f, -sin(angle) * 125.f), true);
				}
			}
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			soundManager->playSFXOverDrive(SoundManager::SFX_HOVER, 15, 0.25f);
			for (int i = 0; i < this->myProjtileVector.size(); i++)
			{
				if (this->myProjtileVector[i]->getIsInVacRange() == true)
				{
					soundManager->playSFXOverDrive(SoundManager::SFX_HOVER, 40, 0.25f);
					float angle = getAngleFromTwoPoints(glm::vec3(position, 0), this->myProjtileVector[i]->getPosition());
					this->myProjtileVector[i]->getHitbox()->getBody()->ApplyForceToCenter(b2Vec2(cos(angle) * 125.f, -sin(angle) * 125.f), true);
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
			temp->Stop();
			delete temp;
			temp = nullptr;
			myProjtileVector.erase(myProjtileVector.begin() + i);
			i--;
		}
	}
}

std::vector<Projectile*>* ProjectileHandler::getBullets()
{
	return &myProjtileVector;
}

void ProjectileHandler::spawnProjectile(ProjectileData projectileData, glm::vec2 pos)
{
	Projectile*	p = new Projectile(projectileData.mesh, projectileData.material, world, pos, projectileData.isCircle);
	p->setShader(myShader);
	myProjtileVector.push_back(p);
}

void ProjectileHandler::fireProjectiles(ProjectileData projectileData, b2World *world, glm::vec2 pos, bool isJumping, glm::vec2 fireDirection)
{
	if (fireDirection.y > 0.f && abs(fireDirection.x) < 0.5f && !isJumping)
	{
		return;
	}

	Projectile* p = new Projectile(projectileData.mesh, projectileData.material, world, pos + glm::vec2(1.35f * fireDirection.x, -(fireDirection.y) * 1.5f), projectileData.isCircle);
	p->setShader(myShader);
	myProjtileVector.push_back(p);
	myProjtileVector.back()->fireBullet(pos, fireDirection);
}
