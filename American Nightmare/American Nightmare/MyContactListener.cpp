#include "MyContactListener.h"
#include "Game\Object.h"
#include "Game\Entity.h"
#include "Game\Player.h"
#include "Enemy.h"


MyContactListener::MyContactListener()
{
}

MyContactListener::~MyContactListener()
{
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
			printf("Enemy is hurting you!!!\n");
			player->getBody()->ApplyForce(b2Vec2(0, -1000000), b2Vec2(), true);
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
