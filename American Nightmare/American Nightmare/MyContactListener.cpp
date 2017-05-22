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
	if (player)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(bodyB);
		if (enemy)
		{
			player->setContactWithEnemy(enemy);
		}

		Projectile* myProjectile = dynamic_cast<Projectile*>(bodyB);
		if (myProjectile)
		{
			soundManager->playSFXOverDrive(SoundManager::SFX_SUCTION, 0.15f);
			myProjectile->setmarked(true);
			
			
			/*if (player->addPlayerProjectiles() == true)
			{

			player->setCheckForProjectilePickUp(true);
			}
			else
			{
			player->setCheckForProjectilePickUp(false);
			}*/
		}
	}

	//Fixa Senare

	Vacuum* vacuumA = dynamic_cast<Vacuum*>(bodyA);
	Vacuum* vacuumB = dynamic_cast<Vacuum*>(bodyB);
	if (vacuumA || vacuumB)
	{
		printf("vacuum\n");
		//printf("vacuum IS ALIVE First\n");
		Projectile* enemyA = dynamic_cast<Projectile*>(bodyA);
		Projectile* enemyB = dynamic_cast<Projectile*>(bodyB);
		if (enemyA || enemyB)
		{
			printf("vacuum IS ALIVE Second\n");
			//printf("Enemy is hurting you!!!\n");
			//enemy->getBody()->ApplyForce(b2Vec2(0, -1000), b2Vec2(), true);
			
			printf("Enemy is hurting you!!!\n");
			player->getBody()->ApplyForce(b2Vec2(0, 0), b2Vec2(), true);
		}
	}


}

void MyContactListener::EndContact(b2Contact* contact)
{
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
}

void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	/* handle pre-solve event */
}

void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{	/* handle post-solve event */}