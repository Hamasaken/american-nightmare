#include "MyContactListener.h"
#include "Game\StructReg.h"

extern MeshManager* meshManager;
extern MaterialManager* materialManager;

MyContactListener::MyContactListener() { }

MyContactListener::~MyContactListener()
{
	particleManager = nullptr;
	soundManager = nullptr;
	camera = nullptr;
}

void MyContactListener::Start(ParticleManager* particleManager, SoundManager* soundManager, ProjectileHandler* ph, MaterialManager* materialManager, MeshManager* meshManager, Camera* camera, Player* player)
{
	// Getting different managers parameters
	this->particleManager = particleManager;
	this->soundManager = soundManager;
	this->camera = camera;
	this->materialManager = materialManager;
	this->meshManager = meshManager;
	this->ph = ph;
	this->player = player;
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
			if (player->addPlayerProjectiles() == true && sf::Joystick::isButtonPressed(0, 4))
			{
				player->addNrOfProjectiles();
				player->pushProjectile(projectile->getProjectileData());
				projectile->setmarked(true);
				soundManager->playSFXOverDrive(SoundManager::SFX_SUCTION, 40, 0.15f);
			}
			else if (player->addPlayerProjectiles() == true && sf::Mouse::isButtonPressed(sf::Mouse::Right) == true)
			{
				player->addNrOfProjectiles();
				player->pushProjectile(projectile->getProjectileData());
				projectile->setmarked(true);
				soundManager->playSFXOverDrive(SoundManager::SFX_SUCTION, 40, 0.15f);
			}
			float angle = getAngleFromTwoPoints(projectile->getPosition(), player->getPosition());
			if (sin(angle) < 0.f) {
				player->setHasJumped(false);
			}
		}
		else if (enemy)
		{
			player->setContactWithEnemy(enemy);
			float angle = getAngleFromTwoPoints(enemy->getPosition(), player->getPosition());
			if (sin(angle) < 0.f) player->setHasJumped(false);
		}
		else if (vacuum)
		{
			//Should there be something here???
		}
		else if (entity)
		{
			float angle = getAngleFromTwoPoints(entity->getPosition(), player->getPosition());
			if (sin(angle) < 0.f) player->setHasJumped(false);
		}
		else if (hitbox)
		{
			float angle = getAngleFromTwoPoints(glm::vec3(hitbox->getPosition(), 0), player->getPosition());
			if (sin(angle) < 0.f) player->setHasJumped(false);
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
				b2Vec2 vec = projectile->getHitbox()->getBody()->GetLinearVelocity();
				if (abs(vec.x) > 15.f || abs(vec.y) > 15.f)
				{
					//Delets the projtile thats hit the enemy
					projectile->setmarked(true);

					camera->screenShake(250.f, 0.25f);
					particleManager->EffectBloodSplatter(enemy->getPosition(), getAngleFromTwoPoints(bodyA->getCenter(), bodyB->getCenter()), 0.08f, 25);
					soundManager->playSFXOverDrive(SoundManager::SFX_HIT, 40, 0.1f);
					enemy->TakeDamage(enemy->getDamage());
					glm::vec4 color = projectile->getIsZombiePart() ? glm::vec4(0.4f, 0.05f, 0.05f, 1.f) : glm::vec4(0.3f);
					particleManager->EffectBloodSplatter(projectile->getPosition(), getAngleFromTwoPoints(bodyB->getCenter(), bodyA->getCenter()), 0.045, 10, color, randBetweenF(0.3f, 0.5));
					if (enemy->getIsDead())
					{
						if (enemy == player->getContactWithEnemy())
							player->setContactWithEnemy(nullptr);
						camera->screenShake(750.f, 1.f); 
						soundManager->playSFXOverDrive(SoundManager::SFX_DEATH, 50, 0.0f);
						particleManager->EffectExplosionLights(enemy->getPosition(), 15, glm::vec4(0.5f, 0.05f, 0.05f, 1.f), randBetweenF(0.4f, 0.8f));
						particleManager->EffectBloodCloud(enemy->getPosition(), 10, glm::vec4(1.f), randBetweenF(1.f, 1.75f));
						particleManager->EffectBloodCloud(enemy->getPosition() + glm::vec3(randBetweenF(-2.f, 2.f), randBetweenF(-2.f, 2.f), 0), 6, glm::vec4(1.f), randBetweenF(0.45, 0.9));
						particleManager->EffectBloodCloud(enemy->getPosition() + glm::vec3(randBetweenF(-2.f, 2.f), randBetweenF(-2.f, 2.f), 0), 6, glm::vec4(1.f), randBetweenF(0.45, 0.9));
						particleManager->EffectBloodCloud(enemy->getPosition() + glm::vec3(randBetweenF(-2.f, 2.f), randBetweenF(-2.f, 2.f), 0), 6, glm::vec4(1.f), randBetweenF(0.45, 0.9));
						particleManager->EffectBloodCloud(enemy->getPosition() + glm::vec3(randBetweenF(-2.f, 2.f), randBetweenF(-2.f, 2.f), 0), 6, glm::vec4(1.f), randBetweenF(0.45, 0.9));
						particleManager->EffectBloodCloud(enemy->getPosition() + glm::vec3(randBetweenF(-2.f, 2.f), randBetweenF(-2.f, 2.f), 0), 6, glm::vec4(1.f), randBetweenF(0.45, 0.9));
						particleManager->EffectBloodCloud(enemy->getPosition() + glm::vec3(randBetweenF(-2.f, 2.f), randBetweenF(-2.f, 2.f), 0), 6, glm::vec4(1.f), randBetweenF(0.45, 0.9));
						particleManager->EffectBloodCloud(enemy->getPosition() + glm::vec3(randBetweenF(-2.f, 2.f), randBetweenF(-2.f, 2.f), 0), 6, glm::vec4(1.f), randBetweenF(0.45, 0.9));
						particleManager->EffectBloodCloud(enemy->getPosition() + glm::vec3(randBetweenF(-2.f, 2.f), randBetweenF(-2.f, 2.f), 0), 6, glm::vec4(1.f), randBetweenF(0.45, 0.9));
					}
				}
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