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
	TriggerType triggerType;	//< The type of trigger this is

public:

	////////////////////////////////////////////////////////////
	// \brief Creates a hitbox for this trigger
	// \param type The type of trigger 
	// \param world Ptr to the world
	// \param position Position of the trigger
	// \param size Scale/Size of the trigger
	////////////////////////////////////////////////////////////
	bool InitializeTrigger(TriggerType type, b2World* world, glm::vec2 position, glm::vec2 size, bool isSensor = true);

	////////////////////////////////////////////////////////////
	// \brief Checks collision with this trigger
	// \param bodyPtr Pointer to another body
	////////////////////////////////////////////////////////////
	void CheckCollision(void* bodyPtr);

	// Gets & Sets
	void setIsTriggered(bool isTriggered);
	bool getIsTriggered() const;

private:
	bool isTriggered;	//< If the box is triggered by a body or not
};

class Door : public Trigger
{
public:
	std::string getLevelName();

private:
	std::string levelName;
};

#endif // !TRIGGER_H
