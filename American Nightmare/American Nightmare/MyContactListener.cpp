#include "MyContactListener.h"

MyContactListener::MyContactListener() { }

MyContactListener::~MyContactListener()
{
	particleManager = nullptr;
	soundManager = nullptr;
	camera = nullptr;
}

void MyContactListener::Start(ParticleManager* particleManager, SoundManager* soundManager, Camera* camera)
{
	// Getting different managers parameters
	this->particleManager = particleManager;
	this->soundManager = soundManager;
	this->camera = camera;
}

void MyContactListener::BeginContact(b2Contact* contact)
{
	Object* bodyA = static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Object* bodyB = static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player* player = nullptr;
	Enemy* enemy = nullptr;
	Projectile* projectileA = nullptr;
	Projectile* projectileB = nullptr;


	player = dynamic_cast<Player*>(bodyA);
	if (player && !player->getIsDead())
	{
		enemy = dynamic_cast<Enemy*>(bodyB);
		if (enemy)
		{
			player->setContactWithEnemy(enemy);
		}
		projectileA = dynamic_cast<Projectile*>(bodyB);
		if (projectileA)
		{
			if (player->addPlayerProjectiles() == true && sf::Mouse::isButtonPressed(sf::Mouse::Right) == true)
			{
				player->addNrOfProjectiles();
				projectileA->setmarked(true);
				soundManager->playSFXOverDrive(SoundManager::SFX_SUCTION, 30, 0.15f);
			}
		}
	}
	else
	{
		enemy = dynamic_cast<Enemy*>(bodyA);
		if (enemy)
		{
			projectileA = dynamic_cast<Projectile*>(bodyB);
			if (projectileA)
			{
				particleManager->EffectBloodSplatter(enemy->getPosition(), getAngleFromTwoPoints(bodyA->getCenter(), bodyB->getCenter()), 0.08f, 25, glm::vec4(0.67f, 0.1f, 0.05f, 1.f));
				soundManager->playSFX(SoundManager::SFX_HIT);	// temp hit sfx
				enemy->TakeDamage(enemy->getDamage());
				if (enemy->getIsDead()) particleManager->EffectExplosionLights(enemy->getPosition(), 25, glm::vec4(0.67f, 0.1f, 0.05f, 1.f));
			}
		}
		else
		{
			Vacuum* vacuumA = dynamic_cast<Vacuum*>(bodyA);
			Vacuum* vacuumB = dynamic_cast<Vacuum*>(bodyB);
			if (vacuumA || vacuumB)
			{
				//printf("vacuum IS ALIVE First\n");
				projectileA = dynamic_cast<Projectile*>(bodyA);
				projectileB = dynamic_cast<Projectile*>(bodyB);
				if (projectileA)
				{
					projectileA->setIsInVacRange(true);
				}
				else if (projectileB)
				{
					projectileB->setIsInVacRange(true);
				}
			}
		}
	}


}


void MyContactListener::EndContact(b2Contact* contact)
{
	if (contact == nullptr) return;

	Object* bodyA = static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Object* bodyB = static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player* player = dynamic_cast<Player*>(bodyA);
	if (player)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(bodyB);
		if (enemy)
		{
			player->setContactWithEnemy(nullptr);
		}
	}

	Vacuum* vacuumA = dynamic_cast<Vacuum*>(bodyA);
	Vacuum* vacuumB = dynamic_cast<Vacuum*>(bodyB);
	if (vacuumA || vacuumB)
	{
		Projectile* projectileA = dynamic_cast<Projectile*>(bodyA);
		Projectile* projectileB = dynamic_cast<Projectile*>(bodyB);
		if (projectileA)
		{
			projectileA->setIsInVacRange(false);

		}
		else if (projectileB)
		{
			projectileB->setIsInVacRange(false);
		}
	}
}