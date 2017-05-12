#include "Arm.h"

Arm::Arm()
{
}

Arm::~Arm()
{
}

bool Arm::Start(std::string modelName, const MaterialManager::Material* material, b2World* world, b2Body* player)
{
	Entity::StartArm(modelName, material, world, player);

	jointDef.bodyA = player;
	jointDef.bodyB = hitbox->getBody();
	jointDef.collideConnected = false;

	jointDef.localAnchorA.Set(0, 1.66);
	jointDef.localAnchorB.Set(-0.4, 0);

	jointDef.referenceAngle = -90;

	return true;
}

b2Body* Arm::getBody()
{
	return hitbox->getBody();

}
