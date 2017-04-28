#include "LevelManager.h"

LevelManager::LevelManager() { }

LevelManager::LevelManager(const LevelManager & other) { }

LevelManager::~LevelManager() { }

bool LevelManager::Start(GLuint playerShader)
{
	world = new b2World(b2Vec2(NULL, GRAVITY));
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

	if (!player->Start(modelPath + "model.m", playerMaterial, world))
		return false;
	player->setShader(playerShader);
	player->AddAnimation(playerMaterial, materialManager.getTextureID(tempNomralMapIndex), animationPath + "testanimationnormalmap.txt");
	// Backing the player up a little to the screen
	player->setPosition(glm::vec3(0.f, 0.f, 0.f));
	

	// Making a Enemy
	enemy = new Enemy();
	if (enemy == nullptr) return false;

	const MaterialManager::Material* enemyMaterial = materialManager.getMaterial("playermaterial");

	if (!enemy->Start(modelPath + "model.m", playerMaterial, world))
		return false;
	enemy->setShader(playerShader);
	enemy->AddAnimation(enemyMaterial, materialManager.getTextureID(tempNomralMapIndex), animationPath + "testanimationnormalmap.txt");
	// Backing the player up a little to the screen
	enemy->setPosition(glm::vec3(10.f, 0.f, 0.f));

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

	// Loading in materials
	materialManager.AddMaterial("lightmaterial", glm::vec3(1.f), 0.f, "lighttexture", texturePath + "gammal-dammsugare.jpg");
	materialManager.AddMaterial("groundmaterial", glm::vec3(0.1f), 1.f, "groundtexture", texturePath + "temp_ground.jpg");
	materialManager.AddMaterial("backgroundmaterial", glm::vec3(0.1f), 1.f, "backgroundtexture", texturePath + "temp_background.jpg");
	if (materialManager.getMaterial("lightmaterial") == nullptr) printf("Material not found\n");
	if (materialManager.getMaterial("groundmaterial") == nullptr) printf("Material not found\n");
	if (materialManager.getMaterial("backgroundmaterial") == nullptr) printf("Material not found\n");

	// Dammsugare in the middle of the screen
	Entity* box = new Entity();
	box->setShader(shader);
	box->Start(modelPath + "model.m", materialManager.getMaterial("lightmaterial"), world, glm::vec2(-10, 0), glm::vec2(8.f, 5.f), b2_staticBody);
	box->setScale(glm::vec3(8, 5, 3));
	map.push_back(box);

	// Creating platforms

	// Ground platform
	Entity* platform = new Entity();
	platform->setShader(shader);
	platform->Start(modelPath + "model.m", materialManager.getMaterial("groundmaterial"), world, glm::vec2(0, 0), glm::vec2(40.f, 1.f), b2_staticBody);
	platform->setScale(glm::vec3(40, 1, 1));
	map.push_back(platform);

	// Above platform
	platform = new Entity();
	platform->setShader(shader);
	platform->Start(modelPath + "model.m", materialManager.getMaterial("groundmaterial"), world, glm::vec2(20, -7.5f), glm::vec2(10.f, 1.f), b2_staticBody);
	platform->setScale(glm::vec3(10, 1, 1));
	map.push_back(platform);

	// Right wall
	platform = new Entity();
	platform->setShader(shader);
	platform->Start(modelPath + "model.m", materialManager.getMaterial("groundmaterial"), world, glm::vec2(40, -20), glm::vec2(1.f, 20.f), b2_staticBody);
	platform->setScale(glm::vec3(1, 20, 1));
	map.push_back(platform);

	// Left wall
	platform = new Entity();
	platform->setShader(shader);
	platform->Start(modelPath + "model.m", materialManager.getMaterial("groundmaterial"), world, glm::vec2(-40, -20), glm::vec2(1.f, 20.f), b2_staticBody);
	platform->setScale(glm::vec3(1, 20, 1));
	map.push_back(platform);

	// Background
	Object* background = new Object();
	background->setShader(shader);
	background->Start(modelPath + "model.m", materialManager.getMaterial("backgroundmaterial"));
	background->setScale(glm::vec3(40, 20, 1));
	background->setPosition(glm::vec3(0, 20, -1));
	map.push_back(background);

	//// Making some boxes to move around
	//for (int i = 0; i < 100; i++)
	//{
	//	Entity* moveble = new Entity();
	//	moveble->setShader(shader);
	//	moveble->Start(modelPath + "model.m", materialManager.getMaterial("lightmaterial"), world, glm::vec2(0, 0), glm::vec2(0.5f, 0.5f), b2_dynamicBody, b2Shape::e_polygon, 1.f, 0.5f);
	//	moveble->setScale(glm::vec3(0.5f, 0.5f, 1));
	//	map.push_back(moveble);
	//}
	//
	//A Projectile
	//for (int i = 0; i < 100; i++)
	//{
		//shoot(shader, modelPath);
	//}

	// Texture on lights for testing
	Object* light = new Object();
	light->setShader(shader);
	light->Start(modelPath + "model.m", materialManager.getMaterial("lightmaterial"));
	light->setPosition(glm::vec3(-20, 5, 15));
	map.push_back(light);

	light = new Object();
	light->setShader(shader);
	light->Start(modelPath + "model.m", materialManager.getMaterial("lightmaterial"));
	light->setPosition(glm::vec3(20, 5, 15));
	map.push_back(light);

	// Temp lights
	lightManager->AddPointLight(glm::vec4(-20, 5, 15, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);
	lightManager->AddPointLight(glm::vec4(+20, 5, 15, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);

	lightManager->AddPointLight(glm::vec4(-10, 5, 15, 0), glm::vec4(1, 1, 1, 1), glm::vec4(10, 10, 10, 10), 10, 10, 10);
	lightManager->AddPointLight(glm::vec4(+10, 5, 15, 0), glm::vec4(1, 1, 1, 1), glm::vec4(10, 10, 10, 10), 10, 10, 10);

	myProjectile = new Projectile(world, shader);
	//lightManager->AddPointLight(glm::vec4(-20, 5, 15, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);
	//lightManager->AddPointLight(glm::vec4(+20, 5, 15, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);
	lightManager->AddPointLight(glm::vec4(20, 5, 15, 1), glm::vec4(10, 10, 10, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);
}

void LevelManager::Update(GLint deltaT)
{
	// Updating physics
	world->Step(1 / 30.f, 3, 3);

	// Updating player
	player->Update(deltaT);

	//Update Projectile
	myProjectile->Update(deltaT, world, player->getPlayerPosAsGLM());
	
	//moveble->Update(deltaT);

	enemy->Update(deltaT, player->getBody()->GetPosition());

	// Updating every object on map
	/*for (Object* object : map)
		object->Update(deltaT);*/

	for (Object* object : map)
		object->Update(deltaT);
}

std::vector<Object*> LevelManager::getMap()
{
	return map;
}


//void LevelManager::shoot(GLuint shader, std::string modelPath)
//{
//	moveble = new Projectile(world, shader);
//	//moveble->setShader(shader);
//	//moveble->Start(modelPath + "model.m", materialManager.getMaterial("lightmaterial"), world, glm::vec2(0, 0), glm::vec2(0.5f, 0.5f), b2_dynamicBody, b2Shape::e_polygon, 1.f, 0.5f);
//	//moveble->setScale(glm::vec3(0.5f, 0.5f, 1));
//	map.push_back(moveble);
//}

const LightManager* LevelManager::getLightManager() const {	return lightManager; }
Player* LevelManager::getPlayer() { return player; }
Enemy* LevelManager::getEnemy() { return enemy; }
Projectile* LevelManager::getProjectile() { return myProjectile; }
