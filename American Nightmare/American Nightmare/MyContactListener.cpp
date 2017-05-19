#include "MyContactListener.h"

MyContactListener::MyContactListener() { }

MyContactListener::~MyContactListener()
{
	particleManager = nullptr;
	soundManager = nullptr;
}

void MyContactListener::Start(ParticleManager* particleManager, SoundManager* soundManager)
{
	// Getting different managers parameters
	this->particleManager = particleManager;
	this->soundManager = soundManager;
}

void MyContactListener::BeginContact(b2Contact* contact)
{
	Object* bodyA = static_cast<Object*>(contact->GetFixtureA()->GetBody()->GetUserData());
	Object* bodyB = static_cast<Object*>(contact->GetFixtureB()->GetBody()->GetUserData());

	Player* player = dynamic_cast<Player*>(bodyA);
	if (player)
	{
		if (dynamic_cast<Enemy*>(bodyB))
		{
			particleManager->EffectBloodSplatter(player->getPosition(), getAngleFromTwoPoints(bodyA->getCenter(), bodyB->getCenter()), 0.08f, 25, glm::vec4(0.67f, 0.1f, 0.05f, 1.f)); // temp blood effect
			soundManager->playSFX(SoundManager::SFX_HIT);	// temp hit sfx
			player->getHP() -= 1.f;
		}
	}
}

void MyContactListener::EndContact(b2Contact* contact)
{

}

void MyContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	/* handle pre-solve event */
}
void MyContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{	/* handle post-solve event */}
