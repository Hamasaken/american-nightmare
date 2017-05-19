#ifndef HITBOX_H
#define HITBOX_H

#include "Box2D.h"
#include "../Accessories.h"
#include "Object.h"

class Hitbox
{
public:
	Hitbox();
	Hitbox(const Hitbox& other);
	~Hitbox();

	////////////////////////////////////////////////////////////
	// \brief Creates a 1x1 dynamic body, 0 density, 10 friction
	////////////////////////////////////////////////////////////
	bool InitializeHitbox(b2World* world);

	////////////////////////////////////////////////////////////
	// \brief Creates a body with parameters
	// \param world World ptr
	// \param position The starting position of the hitbox
	// \param size The full size of the hitbox
	// \param type Dynamic/Static/Other bodytype
	// \optional fixedRotate If the hitbox can rotate or not
	// \optional isBullet I don't what it does yet, sorry, glhf
	// \optional mass The mass of shape, defaults as 10kg
	// \optional friction Friction of the shape, defaults as 10.f
	// \optional isSensor If the hitbox have collision or not
	////////////////////////////////////////////////////////////
	bool InitializeHitbox(b2World* world, glm::vec2 position, glm::vec2 size, b2BodyType type, b2Shape::Type shapeType = b2Shape::e_polygon, bool fixedRotate = true, float mass = 25.0f, float friction = 0.75f, bool isBullet = false, bool isSensor = false);

	////////////////////////////////////////////////////////////
	// \brief Unloads body from world
	////////////////////////////////////////////////////////////
	void Stop();

	b2Body* getBody();
	glm::vec2 getPosition();

protected:

	////////////////////////////////////////////////////////////
	// \brief Creates a b2body object and sends it into world
	// \param position The starting position of this hitbox
	// \param type The Body type (static,dynamic,kin.)
	// \param isBullet If the body is a bullet or not
	////////////////////////////////////////////////////////////
	virtual void AddBodyToWorld(b2World* world, glm::vec2 position, b2BodyType type, bool fixedRotate, bool isBullet);

	////////////////////////////////////////////////////////////
	// \brief Creates a shape object and sends it into body
	// \param size The size in width and height in meters 
	// \param shapeType The type of shape to be created (polygon, circle, rope, mm)
	// \param mass The mass in kg
	// \param friction The friction coffeinent [0:1]
	// \param isSensor If the shape have colission or not
	////////////////////////////////////////////////////////////
	virtual void ModifyShape(glm::vec2 size, b2Shape::Type shapeType, float mass, float friction, bool isSensor);

	b2Body* body;			//< The body object inside world
	b2Fixture* fixture;
	b2MassData m;
};

#endif // !HITBOX_H
