#include "LevelManager.h"

LevelManager::LevelManager() { }

LevelManager::LevelManager(const LevelManager & other) { }

LevelManager::~LevelManager() { }

bool LevelManager::Start(GLuint playerShader, MaterialManager* materialManager, ParticleManager* particleManager, SoundManager* soundManager)
{
	this->materialManager = materialManager;
	this->particleManager = particleManager;
	this->soundManager = soundManager;

	contactManager.Start(particleManager, soundManager);

	world = new b2World(b2Vec2(NULL, GRAVITY));
	world->SetContactListener(&contactManager);

	lightManager = new LightManager();

	std::string modelPath = MODEL_PATH;
	std::string texturePath = TEXTURE_PATH;
	std::string animationPath = ANIMATION_PATH;

	GLint tempNomralMapIndex = materialManager->AddTexture("playernormalmap", texturePath + "Walk01_nor.png");
	// Loading in materials
	materialManager->AddMaterial("lightmaterial", glm::vec3(1.f), 0.f, "lighttexture", texturePath + "gammal-dammsugare.jpg");
	materialManager->AddMaterial("groundmaterial", glm::vec3(0.1f), 1.f, "groundtexture", texturePath + "temp_ground.jpg");
	materialManager->AddMaterial("backgroundmaterial", glm::vec3(0.1f), 1.f, "backgroundtexture", texturePath + "temp_background.jpg");
	if (materialManager->getMaterial("lightmaterial") == nullptr) printf("Material not found\n");
	if (materialManager->getMaterial("groundmaterial") == nullptr) printf("Material not found\n");
	if (materialManager->getMaterial("backgroundmaterial") == nullptr) printf("Material not found\n");


	materialManager->AddMaterial("playermaterial", glm::vec3(0.1), 1.f, "playertexture", texturePath + "Walk01.png");
	//GLint tempNomralMapIndex = materialManager->AddTexture("playernormalmap", texturePath + "Walk01_nor.png");

	// Creating the player object
	player = new Player();
	if (player == nullptr) return false;

	const MaterialManager::Material* playerMaterial = materialManager->getMaterial("playermaterial");
	const MaterialManager::Material* vacuumMaterial = materialManager->getMaterial("lightmaterial");

	if (!player->Start(modelPath + "model.m", playerMaterial, /*vacuumMaterial, */world))
		return false;
	player->setShader(playerShader);
	player->AddAnimation(playerMaterial, materialManager->getTextureID(tempNomralMapIndex), animationPath + "testanimationnormalmap.txt");
	// Backing the player up a little to the screen
	player->setPosition(glm::vec3(0.f, 0.f, 0.f));
	
	//player->getVac()->setShader(mapShader);

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

	// These are getting removed in screen instead
	materialManager = nullptr;
	particleManager = nullptr;
	soundManager = nullptr;
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

	// Unloads every hitbox in the map
	for (Hitbox* hitbox : hitboxes)
	{
		if (hitbox != nullptr)
		{
			hitbox->Stop();
			delete hitbox;
			hitbox = nullptr;
		}
	}

	// Unloads every trigger in the map
	for (Trigger* trigger : triggers)
	{
		if (trigger != nullptr)
		{
			trigger->Stop();
			delete trigger;
			trigger = nullptr;
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
	// Clearing map if already created
	StopMap();

	// Gettings paths to files
	std::string modelPath = MODEL_PATH;
	std::string texturePath = TEXTURE_PATH;

	////////////////////////////////////////////////////////////
	// Level Music
	////////////////////////////////////////////////////////////
	soundManager->playSong(SoundManager::SONG::MUSIC_BOOGIE);

	////////////////////////////////////////////////////////////
	// Map Visuals
	////////////////////////////////////////////////////////////
	// Dammsugare in the middle of the screen
	Entity* box = new Entity();
	box->setShader(shader);
	box->Start(modelPath + "model.m", materialManager->getMaterial("lightmaterial"), world, glm::vec2(-10, 0), glm::vec2(8.f, 5.f), b2_staticBody);
	box->setScale(glm::vec3(8, 5, 3));
	map.push_back(box);

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
		moveble->Start(modelPath + "model.m", materialManager->getMaterial("lightmaterial"), world, glm::vec2((rand() % 40) - 20, (rand() % 40)), glm::vec2(0.5f, 0.5f), b2_dynamicBody, b2Shape::e_polygon, false, 1.f, 0.5f);
		moveble->setScale(glm::vec3(0.5f, 0.5f, 1));
		map.push_back(moveble);
	}

	////////////////////////////////////////////////////////////
	// Map Collision (Invisible)
	////////////////////////////////////////////////////////////
	//Hitbox* hitbox = new Hitbox();
	//hitbox->InitializeHitbox(world, glm::vec2(0, 0), glm::vec2(40.f, 1), b2_staticBody);	 // ground
	//hitboxes.push_back(hitbox);
	//hitbox = new Hitbox();
	//hitbox->InitializeHitbox(world, glm::vec2(20, 7.5f), glm::vec2(10.f, 1), b2_staticBody);	// platform
	//hitboxes.push_back(hitbox);
	//hitbox = new Hitbox();
	//hitbox->InitializeHitbox(world, glm::vec2(-40, 0), glm::vec2(1.f, 20.f), b2_staticBody);	// left wall
	//hitboxes.push_back(hitbox);
	//hitbox = new Hitbox();
	//hitbox->InitializeHitbox(world, glm::vec2(40, 0), glm::vec2(1.f, 20.f), b2_staticBody);	// right wall
	//hitboxes.push_back(hitbox);
	//hitbox = new Hitbox();
	//hitbox->InitializeHitbox(world, glm::vec2(-10, 0), glm::vec2(8.f, 5.f), b2_staticBody);	// dammsugare
	//hitboxes.push_back(hitbox);

	////////////////////////////////////////////////////////////
	// Action Triggers
	////////////////////////////////////////////////////////////
	Trigger* trigger = new Trigger();
	trigger->InitializeTrigger(Trigger::EFFECT, world, glm::vec2(10, 20), glm::vec2(1.f, 1.f));
	triggers.push_back(trigger);

	trigger = new Trigger();
	trigger->InitializeTrigger(Trigger::SPAWN, world, glm::vec2(-10, 15), glm::vec2(1.f, 1.f));
	triggers.push_back(trigger);

	// Triggers visual
	background = new Object();
	background->setShader(shader);
	background->Start(modelPath + "model.m", materialManager->getMaterial("lightmaterial"));
	background->setScale(glm::vec3(1, 1, 1));
	background->setPosition(glm::vec3(10, 20, 0));
	background->setRotation(glm::vec3(0, 0, 0));
	map.push_back(background);

	// Trigger visual
	background = new Object();
	background->setShader(shader);
	background->Start(modelPath + "model.m", materialManager->getMaterial("lightmaterial"));
	background->setScale(glm::vec3(1, 1, 1));
	background->setPosition(glm::vec3(-10, 15, 0));
	background->setRotation(glm::vec3(0, 0, 0));
	map.push_back(background);


	//// Making some boxes to reload with
	for (int i = 0; i < 50; i++)
	{
		Projectile* moveble = new Projectile();
		moveble->setShader(shader);
		moveble->Start(modelPath + "model.m", materialManager->getMaterial("lightmaterial"), world, glm::vec2(0, 0), glm::vec2(0.5f, 0.5f), b2_dynamicBody, b2Shape::e_polygon, 1.f, 0.5f);
		moveble->setScale(glm::vec3(0.5f, 0.5f, 1));
		projectiles.push_back(moveble);
	}

	//// Making some boxes to move around
	//for (int i = 0; i < 100; i++)
	//{
		//Entity* moveble = new Entity();
		//moveble->setShader(shader);
		//moveble->Start(modelPath + "model.m", materialManager.getMaterial("lightmaterial"), world, glm::vec2(0, 0), glm::vec2(0.5f, 0.5f), b2_dynamicBody, b2Shape::e_polygon, 1.f, 0.5f);
		//moveble->setScale(glm::vec3(0.5f, 0.5f, 1));
		//map.push_back(moveble);
	//}
	//
	//A Projectile
	//for (int i = 0; i < 100; i++)
	//{
	//	shoot(shader, modelPath);
	//}

	////////////////////////////////////////////////////////////
	// Lights
	////////////////////////////////////////////////////////////
	Object* light = new Object();
	light->setShader(shader);
	light->Start(modelPath + "model.m", materialManager->getMaterial("lightmaterial"));
	light->setPosition(glm::vec3(-20, 10, 15));
	map.push_back(light);

	light = new Object();
	light->setShader(shader);
	light->Start(modelPath + "model.m", materialManager->getMaterial("lightmaterial"));
	light->setPosition(glm::vec3(20, 10, 15));
	map.push_back(light);

	//// Temp lights
	//lightManager->AddPointLight(glm::vec4(-20, 5, 15, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);
	//lightManager->AddPointLight(glm::vec4(+20, 5, 15, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);

	//lightManager->AddPointLight(glm::vec4(-10, 5, 15, 0), glm::vec4(1, 1, 1, 1), glm::vec4(10, 10, 10, 10), 10, 10, 10);
	//lightManager->AddPointLight(glm::vec4(+10, 5, 15, 0), glm::vec4(1, 1, 1, 1), glm::vec4(10, 10, 10, 10), 10, 10, 10);

	//myPH = new ProjectileHandler(world, shader);
	//myPH = new ProjectileHandler(world, shader, 10);
	
	//moveble = new Projectile(world, shader);

	//myProjectile = new Projectile(world, shader);
	/*lightManager->AddPointLight(glm::vec4(-20, 5, 15, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);
	lightManager->AddPointLight(glm::vec4(+20, 5, 15, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), 1, 1, 1);
	*/lightManager->AddPointLight(glm::vec4(-20, 10, 5, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), 1, 1, 0.01f, 0.01f);
	lightManager->AddPointLight(glm::vec4(20, 10, 5, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), 1, 1, 0.01f, 0.01f);

	lightManager->AddDirectionalLight(glm::vec4(5, 20, 20, 1), glm::vec4(-0.5f, -0.5f, -1, 1), glm::vec4(1, 1, 1, 1), glm::vec4(1, 1, 1, 1), 0.3f);
}

void LevelManager::Update(GLint deltaT)
{
	// Updating player
	//player->Update(deltaT);
	player->Update(deltaT, world, player->getPlayerPosAsGLM());

	//Update Projectile
	//myPH->Update(deltaT, world);

	//myProjectile->Update(deltaT, world, player->getPlayerPosAsGLM());
	
	//moveble->Update(deltaT);
	//myPH->Update(deltaT, world, player->getPlayerPosAsGLM());
	//moveble->Update(deltaT, world, player->getPlayerPosAsGLM());

	// Updating enemies
	enemy->Update(deltaT, player->getBody()->GetPosition());

	// Updating physics
	world->Step(1 / 60.f, 3, 3);

	// Updating every object on map
	deleteProjects();

	 for (Projectile* proj : projectiles)
		 proj->Update(deltaT, world, player->getPlayerPosAsGLM());

	for (Object* object : map)
		object->Update(deltaT);

	// Updating triggers and checking for collisions
	for (Trigger* trigger : triggers)
		if (!trigger->getIsTriggered())	
			trigger->CheckCollision(player->getBody());
	
	// Checking triggers
	CheckTriggers();
}

void LevelManager::CheckTriggers()
{
	for (Trigger* trigger : triggers)
	{
		if (trigger->getIsTriggered())
		{
			switch (trigger->triggerType)
			{

			////////////////////////////////////////////////////////////
			// Door - The player switches level
			////////////////////////////////////////////////////////////
			case Trigger::DOOR:	

				// Checks if the door have a level file
				if (!trigger->getData().empty())
				{
					// Loads new level with the current player's shader
					LoadLevel(player->getShader(), trigger->getData());
				} 
				break;

			////////////////////////////////////////////////////////////
			// Popup - For popups with text/pictures, anything
			////////////////////////////////////////////////////////////
			case Trigger::POPUP:				
				break;

			////////////////////////////////////////////////////////////
			// Push - Move an entity with a force
			////////////////////////////////////////////////////////////
			case Trigger::PUSH:		
				break;

			////////////////////////////////////////////////////////////
			// Effect - Starts an particle effect
			////////////////////////////////////////////////////////////
			case Trigger::EFFECT:

				// Effects
				soundManager->playModifiedSFX(SoundManager::SFX::SFX_BIP, 50, 0.5f);
				particleManager->EffectExplosionLights(glm::vec3(trigger->getPosition(), 0), 1, glm::vec4(1, 1, 1, 1));

				// Temporary effect, clear all lights and a new light
				lightManager->Clear(); 	
				lightManager->AddPointLight(glm::vec4(20, 10, 5, 1), glm::vec4(1, 1, 0.25f, 1), glm::vec4(1, 1, 1, 1), 1, 1, 0.01f, 0.001f);
				break;

			////////////////////////////////////////////////////////////
			// SFX - Plays a sound effect
			////////////////////////////////////////////////////////////
			case Trigger::SFX:					
				break;

			////////////////////////////////////////////////////////////
			// Spawn Trigger - Spawns anything, anywhere, (currently boxes)
			////////////////////////////////////////////////////////////
			case Trigger::SPAWN:

				// Temporary sound effect
				soundManager->playSFX(SoundManager::SFX::SFX_POWERUP);
			{
				Entity* moveble = new Entity();
				moveble->setShader(map[0]->getShader());
				moveble->Start("", materialManager->getMaterial("groundmaterial"), world, glm::vec2((rand() % 40) - 20, (rand() % 40)), glm::vec2(randBetweenF(0.25f, 0.75f), randBetweenF(0.25f, 0.75f)), b2_dynamicBody, b2Shape::e_polygon, false, 1.f, 1.f);
				map.push_back(moveble);
			}

				break;


			////////////////////////////////////////////////////////////
			// Save - Save station for the player, saves the game
			////////////////////////////////////////////////////////////
			case Trigger::SAVE:
				break;

			////////////////////////////////////////////////////////////
			// Cutscene - Switches screen to cutscene and plays a cutscene
			////////////////////////////////////////////////////////////
			case Trigger::CUTSCENE:				
				break;
			}

			// Trigger is now reactivated
			trigger->setIsTriggered(false);
		}
	}
}

std::vector<Object*> LevelManager::getMap()
{
	return map;
}
//
//std::vector<Projectile*> LevelManager::getProj()
//{
//	return this->myPH->getBullets();
//}

std::vector<Projectile*> LevelManager::getProjectiles()
{
	return this->projectiles;
}

const LightManager* LevelManager::getLightManager() const {	return lightManager; }
Player* LevelManager::getPlayer() { return player; }
Enemy* LevelManager::getEnemy() { return enemy; }

void LevelManager::deleteProjects()
{
	
	for (int i = 0; i < this->projectiles.size(); i++)
	{
		
		if (this->projectiles[i]->getmarked() == true)
		{
			Projectile* temp;
			temp = this->projectiles[i];
			this->projectiles[i] = this->projectiles.back();
			this->projectiles.back() = temp;
			this->projectiles.back()->~Projectile();
			projectiles.pop_back();
		}
	}
}

//ProjectileHandler* LevelManager::getProjectiles() { return myPH; }
//Projectile* LevelManager::getProjectile() { return moveble; }
