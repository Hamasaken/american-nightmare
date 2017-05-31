#include "EntityManager.h"

extern MeshManager* meshManager;
extern MaterialManager* materialManager;

EntityManager::EntityManager() { }

EntityManager::EntityManager(const EntityManager & other) { }

EntityManager::~EntityManager() { }

bool EntityManager::Start(b2World* world, SoundManager* soundManager, ProjectileHandler* ph, glm::vec2 screenSize)
{
	this->world = world;
	this->soundManager = soundManager;
	this->screenSize = screenSize;
	this->ph = ph;

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
	case ESpawnerType::zombie2:
	case ESpawnerType::flying1:
	case ESpawnerType::zombie1:
	{
		Enemy* e = new Enemy();
		e->Start(board.mesh, board.material, world);
		e->setShader(board.shader);
		e->AddAnimation(board.textureID, board.normalMap, board.animationFile);
		e->setPosition(glm::vec3(position.x, -position.y, 0));
		enemyList.push_back(e);
	} break;

	case ESpawnerType::skater1:
	{
		Enemy* e = new ZombieRoller();
		e->Start(board.mesh, board.material, world);
		e->setShader(board.shader);
		e->AddAnimation(board.textureID, board.normalMap, board.animationFile);
		e->setPosition(glm::vec3(position.x, -position.y, 0));
		enemyList.push_back(e);
	} break;

	
	case ESpawnerType::trash:
		{
			ph->spawnProjectile(ProjectileData(board.mesh, board.material, false), position);
		} break;

	case ESpawnerType::box:
		{
			ph->spawnProjectile(ProjectileData(board.mesh, board.material, false), position);
		} break;
	default: 
		success = false;
		break;
	}

	return success;
}

void EntityManager::Update(GLfloat deltaT, glm::vec3 playerPosition, bool playerDead, b2World* world)
{
	for (int i = 0; i < enemyList.size(); i++)
	{
		Enemy* e = enemyList[i];

		// Check if enemy is on screen
		if (e->getIsDead())
		{
			glm::vec2 temp = glm::vec2(e->getPosition());
			e->Stop();
			delete e;
			e = nullptr;
			enemyList.erase(enemyList.begin() + i);
			i--;

			float speed = 0.40f;
			int r = rand() % 100 + 1;

			if (r > 0)
			{
				ph->spawnProjectile(ProjectileData(meshManager->getMesh("quad"), materialManager->getMaterial("zombieheadmaterial"), true), temp);
				ph->getBullets()->back()->fireBullet(temp, glm::vec2(randBetweenF(-speed, speed), randBetweenF(-speed, 0)));
			}
			if (r > 10)
			{
				ph->spawnProjectile(ProjectileData(meshManager->getMesh("quad"), materialManager->getMaterial("zombiehandmaterial"), false), temp);
				ph->getBullets()->back()->fireBullet(temp, glm::vec2(randBetweenF(-speed, speed), randBetweenF(-speed, 0)));
			}

			if (r > 25)
			{
				ph->spawnProjectile(ProjectileData(meshManager->getMesh("quad"), materialManager->getMaterial("zombiefootmaterial"), false), temp);
				ph->getBullets()->back()->fireBullet(temp, glm::vec2(randBetweenF(-speed, speed), randBetweenF(-speed, 0)));
			}
			if (r > 45)
			{
				ph->spawnProjectile(ProjectileData(meshManager->getMesh("quad"), materialManager->getMaterial("zombiehandmaterial"), false), temp);
				ph->getBullets()->back()->fireBullet(temp, glm::vec2(randBetweenF(-speed, speed), randBetweenF(-speed, 0)));
			}
			if (r > 65)
			{
				ph->spawnProjectile(ProjectileData(meshManager->getMesh("quad"), materialManager->getMaterial("zombiefootmaterial"), false), temp);
				ph->getBullets()->back()->fireBullet(temp, glm::vec2(randBetweenF(-speed, speed), randBetweenF(-speed, 0)));
			}
			if (r > 85)
			{
				ph->spawnProjectile(ProjectileData(meshManager->getMesh("quad"), materialManager->getMaterial("zombiebodymaterial"), false), temp);
				ph->getBullets()->back()->fireBullet(temp, glm::vec2(randBetweenF(-speed, speed), randBetweenF(-speed, 0)));
			}

		}
		else if (std::abs(playerPosition.x - e->getPosition().x) < ENEMY_UPDATE_DISTANCE)
		{
			e->Update(deltaT, b2Vec2(playerPosition.x, playerPosition.y), playerDead);

			SoundManager::SFX sfx = (rand() % 2) ? SoundManager::SFX_ZOMBIE_1 : SoundManager::SFX_ZOMBIE_2;
			soundManager->playModifiedSFX(sfx, 10, 0.05f);
		}
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
