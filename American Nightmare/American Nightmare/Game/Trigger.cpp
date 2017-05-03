#include "Trigger.h"

bool Trigger::InitializeTrigger(TriggerType type, b2World * world, glm::vec2 position, glm::vec2 size)
{
	this->triggerType = type;

	if (!InitializeHitbox(world, position, size, b2BodyType::b2_kinematicBody, b2Shape::e_polygon, true, 0, 0, false))
		return false;

	return true;
}

void Trigger::CheckCollision(GLfloat deltaT, void* bodyPtr)
{
	// Check if triggered by the player
	b2ContactEdge* contact = body->GetContactList();
	if (contact != nullptr)
	{
		b2Body* body = contact->other;
		// !!!!! Don't forget!!!!!  Go through whole list of contacts if multiple things are colliding
		if (body != nullptr)
		{
			if (body == (void*)(bodyPtr))
				isTriggered = true;
	//		else
	//			printf("%p\n", body);
		}
	}
//	else
//	{
//		printf("No collisions\n", body);
//	}
}

void Trigger::setIsTriggered(bool isTriggered) { this->isTriggered = isTriggered; }
bool Trigger::getIsTriggered() const { return isTriggered; }

void Trigger::ModifyShape(glm::vec2 size, b2Shape::Type shapeType, float density, float friction)
{
	// Creating shape for body
	b2PolygonShape shape;
	shape.m_type = shapeType;
	shape.SetAsBox(size.x, size.y); // half the total size here

	// Creating the fixture
	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;	// making the trigger a sensor
	fixtureDef.shape = &shape;
	fixtureDef.density = density;
	fixtureDef.friction = friction;
	fixtureDef.restitution = 0;	
	fixture = body->CreateFixture(&fixtureDef);
}
