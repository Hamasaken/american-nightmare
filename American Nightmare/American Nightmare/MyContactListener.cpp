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
	void* ptr = nullptr;

	Player* playerA = dynamic_cast<Player*>(bodyA);
	Player* playerB = dynamic_cast<Player*>(bodyB);
	if (playerA || playerB)
	{
		Object* other;
		Player* player;
		if (playerA)
		{
			player = playerA;
			other = bodyB;
			ptr = bodyB;
		}
		else
		{
			player = playerB;
			other = bodyA;
			ptr = bodyB;
		}

		Projectile* projectile = dynamic_cast<Projectile*>(other);
		Enemy* enemy = dynamic_cast<Enemy*>(other);
		Vacuum* vacuum = dynamic_cast<Vacuum*>(other);
		Entity* entity = dynamic_cast<Entity*>(other);
		Hitbox* hitbox = static_cast<Hitbox*>(ptr);
		if (projectile)
		{
			if (player->addPlayerProjectiles() == true && sf::Mouse::isButtonPressed(sf::Mouse::Right) == true)
			{
				player->addNrOfProjectiles();
				projectile->setmarked(true);
				soundManager->playSFXOverDrive(SoundManager::SFX_SUCTION, 30, 0.15f);
			}
			float angle = getAngleFromTwoPoints(projectile->getPosition(), player->getPosition());
			if (angle < 0 && angle > -3.14) player->setHasJumped(false);
		}
		else if (enemy)
		{
			player->setContactWithEnemy(enemy);
		}
		else if (vacuum)
		{

		}
		else if (entity)
		{
			float angle = getAngleFromTwoPoints(entity->getPosition(), player->getPosition());
			if (angle < 0 && angle > -3.14) player->setHasJumped(false);
		}
		else if (hitbox)
		{
			float angle = getAngleFromTwoPoints(glm::vec3(hitbox->getPosition(), 0), player->getPosition());
			if (angle < 0 && angle > -3.14) player->setHasJumped(false);
		}
	}
	else
	{
		Enemy* enemyA = dynamic_cast<Enemy*>(bodyA);
		Enemy* enemyB = dynamic_cast<Enemy*>(bodyB);
		if (enemyA || enemyB)
		{
			Object* other;
			Enemy* enemy;
			if (enemyA)
			{
				enemy = enemyA;
				other = bodyB;
				ptr = bodyB;
			}
			else
			{
				enemy = enemyB;
				other = bodyA;
				ptr = bodyB;
			}

			Projectile* projectile = dynamic_cast<Projectile*>(other);
			if (projectile)
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
				Projectile* projectileA = dynamic_cast<Projectile*>(bodyA);
				Projectile* projectileB = dynamic_cast<Projectile*>(bodyB);
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













	/*
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	Projectile* projectileA = nullptr;
	Projectile* projectileB = nullptr;

	player = dynamic_cast<Player*>(bodyA);
	if (!player)
	{
		player = dynamic_cast<Player*>(bodyB);
		if (player)
		{
			Object* temp = bodyA;
			bodyA = bodyB;
			bodyB = temp;
		}
	} 

	if (player && !player->getIsDead())
	{
		enemy = dynamic_cast<Enemy*>(bodyB);
		projectileA = dynamic_cast<Projectile*>(bodyA);
		if (enemy)
		{
			player->setContactWithEnemy(enemy);
		}
		else if (projectileA)
		{
			if (player->addPlayerProjectiles() == true && sf::Mouse::isButtonPressed(sf::Mouse::Right) == true)
			{
				player->addNrOfProjectiles();
				projectileA->setmarked(true);
				soundManager->playSFXOverDrive(SoundManager::SFX_SUCTION, 30, 0.15f);
			}
		}
		else
		{
			Vacuum* vac = dynamic_cast<Vacuum*>(bodyB);
			if (!vac)
			{
				Entity* ent = dynamic_cast<Entity*>(bodyB);
				if (!ent)
				{
					Hitbox* hitbox = static_cast<Hitbox*>(contact->GetFixtureB()->GetBody()->GetUserData());
					if (hitbox)
					{
						float angle = getAngleFromTwoPoints(glm::vec3(hitbox->getPosition(), 0), player->getPosition());
						printf("%f\n", angle);
						if (angle < 0 && angle > -3.14) player->setHasJumped(false);
					}
				}
			}
		}
	}
	*/

}


void MyContactListener::EndContact(b2Contact* contact)
{
	if (contact == nullptr) return;

	Object* bodyA = static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Object* bodyB = static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player* playerA = dynamic_cast<Player*>(bodyA);
	Player* playerB = dynamic_cast<Player*>(bodyB);
	if (playerA || playerB)
	{
		Object* other;
		Player* player;
		if (playerA)
		{
			player = playerA;
			other = bodyB;
		}
		else
		{
			player = playerB;
			other = bodyA;
		}

		Enemy* enemy = dynamic_cast<Enemy*>(other);
		if (enemy)
		{
			player->setContactWithEnemy(nullptr);
		}
	}
	else
	{
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
	
}