#ifndef ARM_H
#define ARM_H

#define ARM_SIZE_X 1.f
#define ARM_SIZE_Y 0.2f
#define ARM_SIZE_Z 0.2f
#define ARM_DENSITY 0.f
#define ARM_FRICTION 0.0f
#define ARM_VEL_X 0.f
#define ARM_VEL_Y 0.f

#define ARM_MAX_VEL_X 0.f
#define ARM_MAX_VEL_Y 0.f

#include "Game\Entity.h"

class Arm : public Entity
{
private:

	b2RevoluteJointDef jointDef;


public:
	Arm();
	~Arm();

	bool Start(std::string modelName, const MaterialManager::Material* material, b2World* world, b2Body* player);
	b2Body* getBody();
};

#endif // !ARM_H
