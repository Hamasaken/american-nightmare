#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H

#include <Box2D.h>
#include "Game\Particle\ParticleManager.h"
#include "Game\Object.h"
#include "Game\Entity.h"
#include "Game\Player.h"
#include "SoundManager.h"
#include "Enemy.h"

class MyContactListener : public b2ContactListener
{
private:
	ParticleManager* particleManager;
	SoundManager* soundManager;

public:
	MyContactListener();
	~MyContactListener();

	void Start(ParticleManager* particleManager, SoundManager* soundManager);

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif // MYCONTACTLISTENER_H
