#ifndef ENTITY_H
#define ENTITY_H

#include "Object.h"
#include "Hitbox.h"

class Entity : public Object
{
public:
	//bool Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, b2World* world);
	bool Start(const MeshManager::Mesh* mesh, const MaterialManager::Material * material, b2World* world, b2Body* player);
	bool Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, b2World* world, glm::vec2 position, glm::vec3 size, b2BodyType type, b2Shape::Type shapeType = b2Shape::e_polygon, bool fixedRotate = false, float density = 0.f, float friction = 10.f);

	void Stop();
	void Update(GLint deltaT);

	// overdriven set functions for box2d
	void setScale(glm::vec3 scale);
	void setPosition(glm::vec3 position);
	
	Hitbox* getHitbox();

protected:
	Hitbox* hitbox;
};

#endif // !ENTITY_H
