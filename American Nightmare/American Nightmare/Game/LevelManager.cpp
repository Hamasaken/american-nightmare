#include "LevelManager.h"

LevelManager::LevelManager() { }

LevelManager::LevelManager(const LevelManager & other) { }

LevelManager::~LevelManager() { }

bool LevelManager::Start(GLuint playerShader, MaterialManager* materialManager)
{
	this->materialManager = materialManager;

	world = new b2World(b2Vec2(NULL, GRAVITY));
	world->SetAllowSleeping(true);
	lightManager = new LightManager();

	std::string modelPath = MODEL_PATH;
	std::string texturePath = TEXTURE_PATH;
	std::string animationPath = ANIMATION_PATH;

	GLint tempNomralMapIndex = materialManager->AddTexture("playernormalmap", texturePath + "Walk01_nor.png");

	// Creating the player object
	player = new Player();
	if (player == nullptr) return false;

	const MaterialManager::Material* playerMaterial = materialManager->getMaterial("playermaterial");

	if (!player->Start(modelPath + "model.m", playerMaterial, world))
		return false;
	player->setShader(playerShader);
	player->AddAnimation(playerMaterial, materialManager->getTextureID(tempNomralMapIndex), animationPath + "testanimationnormalmap.txt");
	// Backing the player up a little to the screen
	player->setPosition(glm::vec3(0.f, 0.f, 0.f));
	
	// Making a Enemy
	enemy = new Enemy();
	if (enemy == nullptr) return false;

	const MaterialManager::Material* enemyMaterial = materialManager->getMaterial("playermaterial");
	if (!enemy->Start(modelPath + "model.m", playerMaterial, world))
		return false;
	enemy->setShader(playerShader);
	enemy->AddAnimation(enemyMaterial, materialManager->getTextureID(tempNomralMapIndex), animationPath + "testanimationnormalmap.txt");
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
	materialManager = nullptr;
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

	////////////////////////////////////////////////////////////
	// Map Visuals
	////////////////////////////////////////////////////////////

	// Background
	Object* background = new Object();
	background->setShader(shader);
	background->Start(modelPath + "model.m", materialManager->getMaterial("backgroundmaterial"));
	background->setScale(glm::vec3(40, 20, 1));
	background->setPosition(glm::vec3(0, 20, -10));
	map.push_back(background);

	// Ground
	background = new Object();
	background->setShader(shader);
	background->Start(modelPath + "model.m", materialManager->getMaterial("groundmaterial"));
	background->setScale(glm::vec3(40, 20, 1));
	background->setPosition(glm::vec3(0, 1, 0));
	background->setRotation(glm::vec3(1.5 * 3.14, 0, 0));
	map.push_back(background);

	// Right wall
	background = new Object();
	background->setShader(shader);
	background->Start(modelPath + "model.m", materialManager->getMaterial("backgroundmaterial"));
	background->setScale(glm::vec3(40, 20, 1));
	background->setPosition(glm::vec3(39, 20, 0));
	background->setRotation(glm::vec3(0, 1.5 * 3.14, 0));
	map.push_back(background);

	// Left wall
	background = new Object();
	background->setShader(shader);
	background->Start(modelPath + "model.m", materialManager->getMaterial("backgroundmaterial"));
	background->setScale(glm::vec3(40, 20, 1));
	background->setPosition(glm::vec3(-39, 20, 0));
	background->setRotation(glm::vec3(0, -1.5 * 3.14, 0));
	map.push_back(background);

	// Left platform
	background = new Object();
	background->setShader(shader);
	background->Start(modelPath + "model.m", materialManager->getMaterial("groundmaterial"));
	background->setScale(glm::vec3(8, 5, 3));
	background->setPosition(glm::vec3(-10, 0, 0));
	map.push_back(background);


	// Right platform cave
	background = new Object();
	background->setShader(shader);
	background->Start(modelPath + "model.m", materialManager->getMaterial("lightmaterial"));
	background->setScale(glm::vec3(10.f, 15.f, 1));
	background->setPosition(glm::vec3(20, 6.5, 0));
	background->setRotation(glm::vec3(-45, 0, 0));
	map.push_back(background);

	// Right platform cave
	background = new Object();
	background->setShader(shader);
	background->Start(modelPath + "model.m", materialManager->getMaterial("groundmaterial"));
	background->setScale(glm::vec3(10.f, 15.f, 1));
	background->setPosition(glm::vec3(20, 8.5, 0));
	background->setRotation(glm::vec3(-45, 0, 0));
	map.push_back(background);

	////////////////////////////////////////////////////////////
	// Fun boxes
	////////////////////////////////////////////////////////////
	for (int i = 0; i < 100; i++)
	{
		Entity* moveble = new Entity();
		moveble->setShader(shader);
		moveble->Start(modelPath + "model.m", materialManager->getMaterial("lightmaterial"), world, glm::vec2((rand() % 40) - 20, -(rand() % 40)), glm::vec2(0.5f, 0.5f), b2_dynamicBody, b2Shape::e_polygon, false, 1.f, 0.5f);
		moveble->setScale(glm::vec3(0.5f, 0.5f, 1));
		map.push_back(moveble);
	}

	////////////////////////////////////////////////////////////
	// Map Collision (Invisible)
	////////////////////////////////////////////////////////////
	Hitbox* hitbox = new Hitbox();
	hitbox->InitializeHitbox(world, glm::vec2(0, 0), glm::vec2(40.f, 1), b2_staticBody);	 // ground
	hitboxes.push_back(hitbox);
	hitbox = new Hitbox();
	hitbox->InitializeHitbox(world, glm::vec2(20, -7.5f), glm::vec2(10.f, 1), b2_staticBody);	// platform
	hitboxes.push_back(hitbox);
	hitbox = new Hitbox();
	hitbox->InitializeHitbox(world, glm::vec2(-40, 0), glm::vec2(1.f, 20.f), b2_staticBody);	// left wall
	hitboxes.push_back(hitbox);
	hitbox = new Hitbox();
	hitbox->InitializeHitbox(world, glm::vec2(40, 0), glm::vec2(1.f, 20.f), b2_staticBody);	// right wall
	hitboxes.push_back(hitbox);
	hitbox = new Hitbox();
	hitbox->InitializeHitbox(world, glm::vec2(-10, 0), glm::vec2(8.f, 5.f), b2_staticBody);	// dammsugare
	hitboxes.push_back(hitbox);

	////////////////////////////////////////////////////////////
	// Lights
	////////////////////////////////////////////////////////////
	Object* light = new Object();
	light->setShader(shader);
	light->Start(modelPath + "model.m", materialManager->getMaterial("lightmaterial"));
	light->setPosition(glm::vec3(-20, 5, 15));
	map.push_back(light);

	light = new Object();
	light->setShader(shader);
	light->Start(modelPath + "model.m", materialManager->getMaterial("lightmaterial"));
	light->setPosition(glm::vec3(20, 5, 15));
	map.push_back(light);

	lightManager->AddPointLight(glm::vec4(-20, 5, 15, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);
	lightManager->AddPointLight(glm::vec4(+20, 5, 15, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);
	lightManager->AddPointLight(glm::vec4(-10, 5, 15, 0), glm::vec4(1, 1, 1, 1), glm::vec4(10, 10, 10, 10), 10, 10, 10);
	lightManager->AddPointLight(glm::vec4(+10, 5, 15, 0), glm::vec4(1, 1, 1, 1), glm::vec4(10, 10, 10, 10), 10, 10, 10);
}

void LevelManager::Update(GLint deltaT)
{
	// Updating player
	player->Update(deltaT);

	enemy->Update(deltaT, player->getBody()->GetPosition());

	// Updating physics
	world->Step(1 / 60.f, 3, 3);

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
Enemy* LevelManager::getEnemy() { return enemy; };