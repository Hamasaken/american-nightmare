#ifndef PROJECTILEHANDLER_H
#define PROJECTILEHANDLER_H

#include "Projectile.h"
#include "Accessories.h"
#include <SDL.h>

class ProjectileHandler : public Entity
{
private:
	std::vector <Projectile*> myProjtileVector;
	GLuint myShader;
	bool wasPressed;
	bool isPressed;
	
	MeshManager::Mesh* myMesh;
	MaterialManager::Material* myMaterial;

	void initiateProjectiles(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos);

public:
	//ProjectileHandler(b2World* world, GLuint shader, int CAP = 10);
	ProjectileHandler(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos);
	ProjectileHandler();
	~ProjectileHandler();

	void Update(GLint deltaT, b2World* world, glm::vec2 position);
	void deleteProjects(b2World* world);
	std::vector<Projectile*> getBullets();
};

#endif
