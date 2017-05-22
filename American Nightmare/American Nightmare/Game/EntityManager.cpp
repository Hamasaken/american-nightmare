#include "EntityManager.h"

EntityManager::EntityManager() { }

EntityManager::EntityManager(const EntityManager & other) { }

EntityManager::~EntityManager() { }

bool EntityManager::Start(b2World* world, glm::vec2 screenSize)
{
	this->world = world;
	this->screenSize = screenSize;

	return true;
}

void EntityManager::Stop()
{
	for (Enemy* e : enemyList)
	{
		e->Stop();
		delete e;
		e = nullptr;
	}

	for (Entity* e : entityList)
	{
		e->Stop();
		delete e;
		e = nullptr;
	}

	entityBoards.clear();
	enemyList.clear();
	entityList.clear();
}

bool EntityManager::AddEntityBoard(ESpawnerType type, GLuint shader, const MeshManager::Mesh * mesh, const MaterialManager::Material * material)
{
	if (mesh == nullptr) return false;
	if (material == nullptr) return false;

	entityBoards.push_back(EntityBoard(type, shader, mesh, material));

	return true;
}

bool EntityManager::AddEntityBoard(ESpawnerType type, GLuint shader, const MeshManager::Mesh * mesh, const MaterialManager::Material * material, GLuint textureID, GLuint normalMap, std::string animationFile)
{
	if (mesh == nullptr) return false;
	if (material == nullptr) return false;

	entityBoards.push_back(EntityBoard(type, shader, mesh, material, textureID, normalMap, animationFile));

	return true;
}

bool EntityManager::SpawnEntity(ESpawnerType type, glm::vec2 position)
{
	EntityBoard board = getBoard(type);
	GLboolean success = true;

	switch (type)
	{
	case ESpawnerType::zombie1:
	case ESpawnerType::zombie2:
	case ESpawnerType::skater1:
	case ESpawnerType::flying1:
		{
			Enemy* e = new Enemy();
			e->Start(board.mesh, board.material, world);
			e->setShader(board.shader);
			e->AddAnimation(board.textureID, board.normalMap, board.animationFile);
			enemyList.push_back(e);
		} break;
	
	case ESpawnerType::trash:
		{
			Entity* e = new Entity();
			e->Start(board.mesh, board.material, world);
			e->setShader(board.shader);
			entityList.push_back(e);
		} break;

	default: 
		success = false;
		break;
	}

	return success;
}

void EntityManager::Update(GLfloat deltaT, glm::vec3 playerPosition)
{
	for (Enemy* e : enemyList)
	{
		e->Update(deltaT, b2Vec2(playerPosition.x, playerPosition.y));
	}

	for (Entity* e : entityList)
	{
		e->Update(deltaT);
	}
}

std::vector<Enemy*>* EntityManager::getEnemyList()
{
	return &enemyList;
}

std::vector<Entity*>* EntityManager::getEntityList()
{
	return &entityList;
}

EntityManager::EntityBoard EntityManager::getBoard(ESpawnerType type)
{
	for (EntityBoard board : entityBoards)
	{
		if (board.type == type)
		{
			return board;
		}
	}

	printf("Could not find this: %d, entity's board.\n", type);
	return EntityBoard(ESpawnerType::trash, -1, nullptr, nullptr);
}
