#include "Trigger.h"

bool Trigger::InitializeTrigger(TriggerType type, b2World * world, glm::vec2 position, glm::vec2 size, std::string data, bool isSensor)
{
	this->triggerType = type;
	this->data = data;

	if (!InitializeHitbox(world, position, size, b2BodyType::b2_kinematicBody, b2Shape::e_polygon, true, 0, 0, false, true))
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
void Trigger::setData(std::string data) { this->data = data; }
std::string Trigger::getData() const { return data; }
void Trigger::setMapPart(void * ptr) { this->mapPart = ptr; }
void * Trigger::getMapPart() { return mapPart; }
