#include "MyContactListener.h"

MyContactListener::MyContactListener() { }

MyContactListener::~MyContactListener()
{
	particleManager = nullptr;
}

void MyContactListener::Start(ParticleManager* particleManager)
{
	// Getting different managers parameters
	this->particleManager = particleManager;
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
			player->getBody()->ApplyForce(b2Vec2(0, -100000), b2Vec2(), true);
		
			particleManager->EffectBloodSplatter(player->getPosition(), getAngleFromTwoPoints(bodyA->getCenter(), bodyB->getCenter())); // temp blood effect
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
