#include "LevelManager.h"

LevelManager::LevelManager() { }

LevelManager::LevelManager(const LevelManager & other) { }

LevelManager::~LevelManager() { }

bool LevelManager::Start()
{
	lightManager = new LightManager();
	return true;
}

void LevelManager::Stop()
{
	// Unloads the map objects
	StopMap();
	lightManager->Clear();
	delete lightManager;
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

	LoadTempLevel(shader);

	return true;
}

void LevelManager::LoadTempLevel(GLuint shader)
{
	// Gettings paths to files
	std::string modelPath = MODEL_PATH;
	std::string texturePath = TEXTURE_PATH;

	// TEMPORARY 
	for (int i = 0; i < 3; i++)
	{
		map.push_back(new Object());
		map[i]->setShader(shader);
	}

	map[0]->Start(modelPath + "model.m", texturePath + "gammal-dammsugare.jpg");
	map[1]->Start(modelPath + "model.m", texturePath + "temp_ground.jpg");
	map[2]->Start(modelPath + "model.m", texturePath + "temp_background.jpg");

	// TEMPORARY SHOWCASE MAP
	map[0]->setScale(glm::vec3(8, 5, 3));
	map[0]->setRotation(glm::vec3(0, 0, 40));
	map[0]->setPosition(glm::vec3(-2, 0, -10));
	map[1]->setScale(glm::vec3(60, 100, 0));;
	map[1]->setPosition(glm::vec3(0, -2, 0));
	map[1]->setRotation(glm::vec3(0.f, -90, 0.f));
	map[2]->setScale(glm::vec3(60, 15, 0));;
	map[2]->setPosition(glm::vec3(0, 13, -10));
	map[2]->setRotation(glm::vec3(0.f, 0.f, 0.f));

	lightManager->AddPointLight(glm::vec4(-20, 5, 5, 1), glm::vec4(1, 0, 0, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);
	lightManager->AddPointLight(glm::vec4(+20, 5, 5, 1), glm::vec4(0, 0, 1, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);
}

void LevelManager::Update(GLint deltaT)
{
	// Updating every object on map
	for (Object* object : map)
		object->Update(deltaT);
}

std::vector<Object*> LevelManager::getMap()
{
	return map;
}

const LightManager* LevelManager::getLightManager() const
{
	return lightManager;
}