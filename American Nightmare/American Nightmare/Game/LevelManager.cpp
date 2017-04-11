#include "LevelManager.h"

LevelManager::LevelManager() { }

LevelManager::LevelManager(const LevelManager & other) { }

LevelManager::~LevelManager() { }

bool LevelManager::Start()
{

	return true;
}

void LevelManager::Stop()
{
	// Unloads the map objects
	StopMap();
}

void LevelManager::StopMap()
{
	// Unloads every object in map
	for (Object* object : map)
	{
		if (object != nullptr)
		{
			object->Stop();
			delete object;
			object = nullptr;
		}
	}
}

bool LevelManager::LoadLevel(GLuint shader, std::string levelFile)
{
	// Deleting current level
	StopMap();

	// Gettings paths to files
	std::string modelPath = MODEL_PATH;
	std::string texturePath = TEXTURE_PATH;

	// TEMPORARY 
	for (int i = 0; i < 2; i++)
	{
		map.push_back(new Object());
		if (map[i] == nullptr) return false;
		if (!map[i]->Start(modelPath + "model.m", texturePath + "gammal-dammsugare.jpg"))
			return false;
		map[i]->setShader(shader);
	}

	// TEMPORARY SHOWCASE MAP
	map[0]->setScale(glm::vec3(8, 5, 3));
	map[0]->setRotation(glm::vec3(0, 0, 40));
	map[0]->setPosition(glm::vec3(-2, 0, -10));
	map[1]->setScale(glm::vec3(15, 15, 0));;
	map[1]->setPosition(glm::vec3(0, -10, 0));
	map[1]->setRotation(glm::vec3(0.f, -90, 0.f));

	return true;
}

void LevelManager::Update(sf::Time delta)
{
	// Updating every object on map
	for (Object* object : map)
		object->Update();
}

std::vector<Object*> LevelManager::getMap()
{
	return map;
}
