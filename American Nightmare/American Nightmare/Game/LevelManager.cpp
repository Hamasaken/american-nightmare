#include "LevelManager.h"

LevelManager::LevelManager() { }

LevelManager::LevelManager(const LevelManager & other) { }

LevelManager::~LevelManager() { }

bool LevelManager::Start(GLuint playerShader)
{
	lightManager = new LightManager();

	std::string modelPath = MODEL_PATH;
	std::string texturePath = TEXTURE_PATH;
	std::string animationPath = ANIMATION_PATH;

	materialManager.AddMaterial("playermaterial", glm::vec3(0.1), 1.f, "playertexture", texturePath + "Walk01.png");
	GLint tempNomralMapIndex = materialManager.AddTexture("playernormalmap", texturePath + "Walk01_nor.png");

	// Creating the player object
	player = new Player();
	if (player == nullptr) return false;

	const MaterialManager::Material* playerMaterial = materialManager.getMaterial("playermaterial");

	if (!player->Start(modelPath + "model.m", playerMaterial))
		return false;
	player->setShader(playerShader);
	player->AddAnimation(playerMaterial, materialManager.getTextureID(tempNomralMapIndex), animationPath + "testanimationnormalmap.txt");

	// Backing the player up a little to the screen
	player->setPosition(glm::vec3(0, 0, 10.f));
	player->setScale(glm::vec3(4, 4, 4));

	return true;
}

void LevelManager::Stop()
{
	// Deleting player
	if (player != nullptr)
	{
		player->Stop();
		delete player;
		player = nullptr;
	}
	// Unloads the map objects
	StopMap();
	lightManager->Clear();
	materialManager.Clear();
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
	for (int i = 0; i < 5; i++)
	{
		map.push_back(new Object());
		map[i]->setShader(shader);
	}

	materialManager.AddMaterial("lightmaterial", glm::vec3(0.1f), 0.f, "lighttexture", texturePath + "gammal-dammsugare.jpg");
	materialManager.AddMaterial("groundmaterial", glm::vec3(0.1f), 1.f, "groundtexture", texturePath + "temp_ground.jpg");
	materialManager.AddMaterial("backgroundmaterial", glm::vec3(0.1f), 1.f, "backgroundtexture", texturePath + "temp_background.jpg");

	// TEMPORARY SHOWCASE MAP
	const MaterialManager::Material* tempMaterial = materialManager.getMaterial("lightmaterial");
	if (tempMaterial == nullptr)
		printf("Material not found\n");
	else
	{
		map[0]->Start(modelPath + "model.m", tempMaterial);
		map[0]->setScale(glm::vec3(8, 5, 1));
		map[0]->setRotation(glm::vec3(0, 0, 40));
		map[0]->setPosition(glm::vec3(-2, 0, -10));
	}

	tempMaterial = materialManager.getMaterial("groundmaterial");
	if (tempMaterial == nullptr)
		printf("Material not found\n");
	else
	{
		map[1]->Start(modelPath + "model.m", tempMaterial);
		map[1]->setScale(glm::vec3(60, 100, 1));;
		map[1]->setPosition(glm::vec3(0, -2, 0));
		map[1]->setRotation(glm::vec3(0.f, -90, 0.f));
	}

	tempMaterial = materialManager.getMaterial("backgroundmaterial");
	if (tempMaterial == nullptr)
		printf("Material not found\n");
	else
	{
		map[2]->Start(modelPath + "model.m", tempMaterial);
		map[2]->setScale(glm::vec3(60, 15, 1));;
		map[2]->setPosition(glm::vec3(0, 13, -10));
		map[2]->setRotation(glm::vec3(0.f, 0.f, 0.f));
	}

	tempMaterial = materialManager.getMaterial("lightmaterial");
	if (tempMaterial == nullptr)
		printf("Material not found\n");
	else
	{
		map[3]->Start(modelPath + "model.m", tempMaterial);
		map[3]->setPosition(glm::vec3(-20, 5, 15));
		map[3]->setRotation(glm::vec3(0.f, 0.f, 0.f));
		map[3]->setScale(glm::vec3(0.5, 0.5, 1));
	}

	tempMaterial = materialManager.getMaterial("lightmaterial");
	if (tempMaterial == nullptr)
		printf("Material not found\n");
	else
	{
		map[4]->Start(modelPath + "model.m", tempMaterial);
		map[4]->setPosition(glm::vec3(20, 5, 15));
		map[4]->setRotation(glm::vec3(0.f, 0.f, 0.f));
		map[4]->setScale(glm::vec3(0.5, 0.5, 1));
	}

	// Temp lights
	lightManager->AddPointLight(glm::vec4(-20, 5, 15, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);
	lightManager->AddPointLight(glm::vec4(+20, 5, 15, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);
}

void LevelManager::Update(GLint deltaT)
{
	// Updating player
	player->Update(deltaT);

	// Updating every object on map
	for (Object* object : map)
		object->Update(deltaT);
}

std::vector<Object*> LevelManager::getMap()
{
	return map;
}

const LightManager* LevelManager::getLightManager() const {	return lightManager; }
Player* LevelManager::getPlayer() { return player; }