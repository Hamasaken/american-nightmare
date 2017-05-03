#include "Trigger.h"
#include "Player.h"

bool Trigger::InitializeTrigger(TriggerType type, b2World * world, glm::vec2 position, glm::vec2 size, bool isSensor)
{
	this->triggerType = type;

	if (!InitializeHitbox(world, position, size, b2BodyType::b2_kinematicBody, b2Shape::e_polygon, true, 0, 0, false, isSensor))
		return false;

	return true;
}

void Trigger::CheckCollision(void* bodyPtr)
{
	// Check if triggered by the player
	b2ContactEdge* contact = body->GetContactList();
	if (contact != nullptr)
	{
		b2Body* body = contact->other;
		if (body == bodyPtr)
		{
			isTriggered = true;
		}
	}
}

void Trigger::setIsTriggered(bool isTriggered) { this->isTriggered = isTriggered; }
bool Trigger::getIsTriggered() const { return isTriggered; }

////////////////////////////////////////////////////////////
// Door
////////////////////////////////////////////////////////////
std::string Door::getLevelName()
{
	return levelName;
}
