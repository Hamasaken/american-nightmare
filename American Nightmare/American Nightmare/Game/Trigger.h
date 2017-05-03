#ifndef TRIGGER_H
#define TRIGGER_H

#include "Hitbox.h"

class Trigger : public Hitbox
{
public:
	enum TriggerType 
	{
		LEVEL_CHANGE,	// changes the current level
		POPUP,			// tutorial popups
		TELEPORT,		// moves the player to a new position on the current level
		EFFECT,			// particle effect
		SFX,			// sound effect
		SPAWN,			// spawns an entity
		CUTSCENE		// plays an cutscene
	};
	TriggerType triggerType;

public:
	bool InitializeTrigger(TriggerType type, b2World* world, glm::vec2 position, glm::vec2 size);
	void CheckCollision(GLfloat deltaT, void* playerBodyPtr);

	void setIsTriggered(bool isTriggered);
	bool getIsTriggered() const;

protected:
	////////////////////////////////////////////////////////////
	// \brief Creates a shape object and sends it into body
	// \param size The size in width and height in meters 
	// \param shapeType The type of shape to be created (polygon, circle, rope, mm)
	// \param density The density in kg/m2
	// \param friction The friction coffeinent [0:1]
	////////////////////////////////////////////////////////////
	void ModifyShape(glm::vec2 size, b2Shape::Type shapeType, float density, float friction);

private:
	bool isTriggered;
};

#endif // !TRIGGER_H
