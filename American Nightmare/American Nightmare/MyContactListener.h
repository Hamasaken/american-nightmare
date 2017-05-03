#ifndef MYCONTACTLISTENER_H
#define MYCONTACTLISTENER_H

#include <Box2D.h>

class MyContactListener : public b2ContactListener
{
private:

public:
	MyContactListener();
	~MyContactListener();

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif // MYCONTACTLISTENER_H
