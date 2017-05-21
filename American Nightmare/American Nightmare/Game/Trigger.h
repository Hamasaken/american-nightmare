#ifndef TRIGGER_H
#define TRIGGER_H

#include "Hitbox.h"

class Trigger : public Hitbox
{
public:
	enum TriggerType 
	{
		DOOR,			// changes the current level
		POPUP,			// tutorial popups
		PUSH,			// moves an entity
		EFFECT,			// particle effect
		SFX,			// sound effect
		SPAWN,			// spawns an entity
		SAVE,			// save station
		POSTER,			// unlocks a poster
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
	bool InitializeTrigger(TriggerType type, b2World* world, glm::vec2 position, glm::vec2 size, std::string data = "", bool isSensor = true);

	////////////////////////////////////////////////////////////
	// \brief Checks collision with this trigger
	// \param bodyPtr Pointer to another body
	////////////////////////////////////////////////////////////
	void CheckCollision(void* bodyPtr);

	// Gets & Sets
	void setIsTriggered(bool isTriggered);
	bool getIsTriggered() const;
	void setData(std::string data);
	std::string getData() const;
	void setMapPart(void* ptr);
	void* getMapPart();

private:
	bool isTriggered;		//< If the box is triggered by a body or not
	std::string data;		//< Extra Data for various things
	void* mapPart;			//< Extra Data for removable object parts 
};

#endif // !TRIGGER_H
