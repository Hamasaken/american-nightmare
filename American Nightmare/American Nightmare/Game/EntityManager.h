#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "..\Accessories.h"
#include "../ANNIE/LevelFile.h"
#include "Player.h"
#include "Entity.h"
#include "../Enemy.h"

class EntityManager
{
private:
	struct EntityBoard
	{
		ESpawnerType type;
		const MeshManager::Mesh* mesh;
		const MaterialManager::Material* material;
		GLuint shader;
		GLuint textureID;
		GLuint normalMap;
		std::string animationFile;

		EntityBoard(ESpawnerType type, GLuint shader, const MeshManager::Mesh* mesh, const MaterialManager::Material* material)
		{
			this->type = type;
			this->shader = shader;
			this->mesh = mesh;
			this->material = material;
			this->textureID = -1;
			this->normalMap = -1;
			this->animationFile = "";
		}
		
		EntityBoard(ESpawnerType type, GLuint shader, const MeshManager::Mesh* mesh, const MaterialManager::Material* material, GLuint textureID, GLuint normalMap, std::string animationFile)
		{
			this->type = type;
			this->shader = shader;
			this->mesh = mesh;
			this->material = material;
			this->textureID = textureID;
			this->normalMap = normalMap;
			this->animationFile = animationFile;
		}
	};

public:
	EntityManager();
	EntityManager(const EntityManager& other);
	~EntityManager();

	bool Start(b2World* world, glm::vec2 screenSize);
	void Stop();

	bool AddEntityBoard(ESpawnerType type, GLuint shader, const MeshManager::Mesh* mesh, const MaterialManager::Material* material);
	bool AddEntityBoard(ESpawnerType type, GLuint shader, const MeshManager::Mesh* mesh, const MaterialManager::Material* material, GLuint textureID, GLuint normalMap, std::string animationFile);

	bool SpawnEntity(ESpawnerType type, glm::vec2 position);
	void Update(GLfloat deltaT, glm::vec3 playerPosition);

	std::vector<Enemy*>* getEnemyList();
	std::vector<Entity*>* getEntityList();

private:
	EntityBoard getBoard(ESpawnerType type);

	b2World* world;
	glm::vec2 screenSize; // For only updating/drawing things inside with quadtree

	std::vector<EntityBoard> entityBoards;
	std::vector<Enemy*> enemyList;
	std::vector<Entity*> entityList;
};

#endif // !MESHMANAGER_H

