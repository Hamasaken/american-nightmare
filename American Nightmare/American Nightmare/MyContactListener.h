#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H

#include <Box2D.h>
#include "Game\Camera.h"
#include "SoundManager.h"
#include "vacuum.h"
#include "Projectile.h"
#include "Game\Particle\ParticleManager.h"
#include "Game\Player.h"
#include "Enemy.h"

class MyContactListener : public b2ContactListener
{
private:
	MaterialManager* materialManager;
	MeshManager* meshManager;
	ParticleManager* particleManager;
	SoundManager* soundManager;
	Camera* camera;
	ProjectileHandler* ph;
	Player* player;
public:
	MyContactListener();
	~MyContactListener();

	void Start(ParticleManager* particleManager, SoundManager* soundManager, ProjectileHandler* ph, MaterialManager* materialManager, MeshManager* meshManager, Camera* camera, Player* player);

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};

#endif // MYCONTACTLISTENER_H
