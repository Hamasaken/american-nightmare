#ifndef ENTITY_H
#define ENTITY_H

#include "Object.h"
#include "Hitbox.h"

class Entity : public Object
{
public:
	bool Start(std::string modelName, const MaterialManager::Material* material, b2World* world);
	bool Start(std::string modelName, const MaterialManager::Material* material, b2World* world, glm::vec2 position, glm::vec2 size, b2BodyType type, b2Shape::Type shapeType = b2Shape::e_polygon, float density = 0.f, float friction = 10.f);

	void Stop();
	void Update(GLint deltaT);
protected:
	Hitbox* hitbox;
};

#endif // !ENTITY_H