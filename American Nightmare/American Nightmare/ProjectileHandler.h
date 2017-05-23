#ifndef PROJECTILEHANDLER_H
#define PROJECTILEHANDLER_H

#include "Projectile.h"
#include "Accessories.h"
#include <SDL.h>

class ProjectileHandler
{
private:
	std::vector <Projectile*> myProjtileVector;
	GLuint myShader;

	glm::vec2 screenSize;
	glm::vec2 screenPos;
	MeshManager::Mesh* myMesh;
	MaterialManager::Material* myMaterial;

	void initiateProjectiles(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos, GLuint shader);

public:
	//ProjectileHandler(b2World* world, GLuint shader, int CAP = 10);
	ProjectileHandler(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos, GLuint shader, glm::vec2 screenPos, glm::vec2 screenSize);
	ProjectileHandler();
	~ProjectileHandler();

	void Update(GLint deltaT, b2World* world, glm::vec2 position);
	void deleteProjects(b2World* world);
	std::vector<Projectile*> getBullets();
	void UpdateScreenProperties(glm::vec2 screenSize, glm::vec2 screenPos);
	void fireProjectiles(const MeshManager::Mesh* mesh, const MaterialManager::Material*  material, b2World *world, glm::vec2 pos, bool isCircle);
};

#endif
