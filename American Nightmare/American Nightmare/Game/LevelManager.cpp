#include "LevelManager.h"

LevelManager::LevelManager() 
{
	//world = b2World(Gravity);
}

LevelManager::LevelManager(const LevelManager & other) { }

LevelManager::~LevelManager() { }

bool LevelManager::Start(GLuint playerShader)
{
	world = new b2World(Gravity);
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

	if (!player->Start(modelPath + "model.m", playerMaterial, *world, 0, 30, true))
		return false;
	player->setShader(playerShader);
	player->AddAnimation(playerMaterial, materialManager.getTextureID(tempNomralMapIndex), animationPath + "testanimationnormalmap.txt");
	// Backing the player up a little to the screen
	player->setPosition(glm::vec3(0.f, 0.f, 0.f));
	
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

	materialManager.AddMaterial("lightmaterial", glm::vec3(1.f), 0.f, "lighttexture", texturePath + "gammal-dammsugare.jpg");
	materialManager.AddMaterial("groundmaterial", glm::vec3(0.1f), 1.f, "groundtexture", texturePath + "temp_ground.jpg");
	materialManager.AddMaterial("backgroundmaterial", glm::vec3(0.1f), 1.f, "backgroundtexture", texturePath + "temp_background.jpg");

	// TEMPORARY SHOWCASE MAP
	const MaterialManager::Material* tempMaterial = materialManager.getMaterial("lightmaterial");
	if (tempMaterial == nullptr)
		printf("Material not found\n");
	else
	{
		map[0]->Start(modelPath + "model.m", tempMaterial, *world);
		map[0]->setScale(glm::vec3(8, 5, 3));
	}

	tempMaterial = materialManager.getMaterial("groundmaterial");
	if (tempMaterial == nullptr)
		printf("Material not found\n");
	else
	{
		//map[1]->shape.SetAsBox(5000, 1);		
		map[1]->Start(modelPath + "model.m", tempMaterial, *world);
		map[1]->setScale(glm::vec3(20, 1, 1));
		map[1]->setPosition(glm::vec3(0, 0, 0));
		map[1]->bodyDef.position = b2Vec2(map[1]->getPosition().x, map[1]->getPosition().y);
	}

	tempMaterial = materialManager.getMaterial("backgroundmaterial");
	if (tempMaterial == nullptr)
		printf("Material not found\n");
	else
	{
		map[2]->Start(modelPath + "model.m", tempMaterial, *world);
	}

	tempMaterial = materialManager.getMaterial("lightmaterial");
	if (tempMaterial == nullptr)
		printf("Material not found\n");
	else
	{
		map[3]->Start(modelPath + "model.m", tempMaterial, *world);
	}

	tempMaterial = materialManager.getMaterial("lightmaterial");
	if (tempMaterial == nullptr)
		printf("Material not found\n");
	else
	{
		map[4]->Start(modelPath + "model.m", tempMaterial, *world);
		map[4]->setPosition(glm::vec3(20, 5, 15));
	}

	player->setScale(glm::vec3(1.f, 1.f, 1.f));
	player->bodyDef.position = b2Vec2(player->getPosition().x, player->getPosition().y);

	// Temp lights
	//lightManager->AddPointLight(glm::vec4(-20, 5, 15, 1), glm::vec4(10, 10, 10, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);
	//lightManager->AddPointLight(glm::vec4(+20, 5, 15, 1), glm::vec4(11, 10, 10, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);


	lightManager->AddPointLight(glm::vec4(-10, 5, 15, 0), glm::vec4(10, 10, 10, 1), glm::vec4(10, 10, 10, 10), 10, 10, 10);
	lightManager->AddPointLight(glm::vec4(+10, 5, 15, 0), glm::vec4(10, 10, 10, 1), glm::vec4(10, 10, 10, 10), 10, 10, 10);
}

void LevelManager::Update(GLint deltaT)
{
	// Updating physics
	world->Step(1 / 60.f, 1, 1);

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