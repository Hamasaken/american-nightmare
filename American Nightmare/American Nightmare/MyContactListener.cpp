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

	Player* player = dynamic_cast<Player*>(bodyA);
	if (player && !player->getIsDead())
	{
		Enemy* enemy = dynamic_cast<Enemy*>(bodyB);
		if (enemy)
		{
			player->setContactWithEnemy(enemy);
		}

		Projectile* myProjectile = dynamic_cast<Projectile*>(bodyB);
		if (myProjectile)
		{
			if (player->addPlayerProjectiles() == true && sf::Mouse::isButtonPressed(sf::Mouse::Right) == true)
			{
				player->addNrOfProjectiles();
				myProjectile->setmarked(true);
				soundManager->playSFXOverDrive(SoundManager::SFX_SUCTION, 0.15f);
			}
		}
	}

	Enemy* enemy = dynamic_cast<Enemy*>(bodyA);
	if (enemy)
	{
		Projectile* myProjectile = dynamic_cast<Projectile*>(bodyB);
		if (myProjectile)
		{
			particleManager->EffectBloodSplatter(enemy->getPosition(), getAngleFromTwoPoints(bodyA->getCenter(), bodyB->getCenter()), 0.08f, 25, glm::vec4(0.67f, 0.1f, 0.05f, 1.f));
			soundManager->playSFX(SoundManager::SFX_HIT);	// temp hit sfx
			enemy->TakeDamage(enemy->getDamage());
			if (enemy->getIsDead()) particleManager->EffectExplosionLights(enemy->getPosition(), 25, glm::vec4(0.67f, 0.1f, 0.05f, 1.f)); 
		}
	}

		//Fixa Senare
		Vacuum* vacuumA = dynamic_cast<Vacuum*>(bodyA);
		Vacuum* vacuumB = dynamic_cast<Vacuum*>(bodyB);
		if (vacuumA || vacuumB)
		{
			//printf("vacuum IS ALIVE First\n");
			Projectile* projectileA = dynamic_cast<Projectile*>(bodyA);
			Projectile* projectileB = dynamic_cast<Projectile*>(bodyB);
			if (projectileA)
			{
				projectileA->setIsInVacRange(true);
				
			}
			else if(projectileB)
			{
				projectileB->setIsInVacRange(true);
			}
		}

}


void MyContactListener::EndContact(b2Contact* contact)
{
	if (contact == nullptr) return;

	Player* player = static_cast<Player*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Enemy* enemy = static_cast<Enemy*>(contact->GetFixtureB()->GetBody()->GetUserData());

	if (player)
	{
		if (enemy)
		{
			player->setContactWithEnemy(nullptr);
		}
	}

	Object* bodyA = static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Object* bodyB = static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData());

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

void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	/* handle pre-solve event */
}

void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	/* handle post-solve event */
}