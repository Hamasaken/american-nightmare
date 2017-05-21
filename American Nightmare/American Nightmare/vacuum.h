#ifndef VACUUM_H
#define VACUUM_H


#include "Accessories.h"
#include "Game\Hitbox.h"
#include "Game\Entity.h"

class Vacuum : public Entity
{
private:
	b2RevoluteJoint* joint;
public:
	Vacuum();
	~Vacuum();

	void startVac(b2World* world, b2Body* player);
	b2Body* getBody()const; 

	void Update(b2Vec2 Pos, GLint deltaT);
};
#endif // !VACUUM_H
