#include "ScreenGame.h"

ScreenGame::ScreenGame() : Screen()
{
	shaderManager = nullptr;
	levelManager = nullptr;
	player = nullptr;
}

ScreenGame::ScreenGame(const ScreenGame& other) { }

ScreenGame::~ScreenGame() { }

bool ScreenGame::Start(OpenGL * openGL)
{
	// Starting Camera & getting openGL pointer
	Screen::Start(openGL);

	////////////////////////////////////////////////////////////
	// Creating Shader Manager
	////////////////////////////////////////////////////////////
	std::string shaderPath = SHADER_PATH;
	shaderManager = new ShaderManager();
	if (shaderManager == nullptr) return false;

	// Adding Shader Programs
	//shaderManager->AddShader(openGL, "solid", shaderPath + "solid_vs.glsl", shaderPath + "solid_fs.glsl");
	shaderManager->AddShader(openGL, "texture", shaderPath + "texture_vs.glsl", shaderPath + "texture_fs.glsl");

	////////////////////////////////////////////////////////////
	// Creating Models
	////////////////////////////////////////////////////////////
	std::string modelPath = MODEL_PATH;
	std::string texturePath = TEXTURE_PATH;

	// Creating the player object
	player = new Player();
	if (player == nullptr) return false;
	if (!player->Start(openGL, modelPath + "model.m", texturePath + "texture.t"))
		return false;
	player->setShader(shaderManager->GetShader("texture"));

<<<<<<< HEAD
	// Creating a simple background wall
	wall = new Object();
	if (wall == nullptr) return false;
	if (!wall->Start(openGL, modelPath + "model.m", texturePath + "texture.t"))
		return false;
	wall->setShader(shaderManager->GetShader("texture"));

	// Creating a simple floor object too see depth
	floor = new Object();
	if (floor == nullptr) return false;
	if (!floor->Start(openGL, modelPath + "model.m", texturePath + "texture.t"))
		return false;
	floor->setShader(shaderManager->GetShader("texture"));
=======
	// Creating a simple level
	levelManager = new LevelManager();
	if (levelManager == nullptr) return false;
	if (!levelManager->Start(openGL))
		return false;
>>>>>>> origin/master

	// Setting startvariables
	SetStartVariables();

	return true;
}

void ScreenGame::SetStartVariables()
{
	// Backing the camera a little bit backwards
	camera->setPosition(glm::vec3(0, 0, 10));

	// Making wall & floor bigger
	levelManager->LoadLevel(shaderManager->GetShader("solid"), "0.lvl");
}

void ScreenGame::Update()
{
	sf::Time delta = sf::Time::Zero; // fix this, temporary

					 // Updating player
	player->Update();

	// Updating map objects
	levelManager->Update(delta);

	// Moving the camera to follow player object
	camera->smoothToPosition(glm::vec3(player->getPosition().x, player->getPosition().y, camera->getPosition().z));

	// Building a new camera view matrix
	camera->buildViewMatrix();
}

void ScreenGame::Draw()
{
	////////////////////////////////////////////////////////////
	// Starting draw section
	////////////////////////////////////////////////////////////
	openGL->StartDraw(CLEAR_COLOR);

	// Drawing map
	for (Object* object : levelManager->getMap())
		DrawObject(object, shaderManager);

	// Drawing player
	DrawObject(player, shaderManager);

	////////////////////////////////////////////////////////////
	// Ending draw section
	////////////////////////////////////////////////////////////
	openGL->EndDraw();
}

void ScreenGame::Stop()
{
	// Deleting shaders
	if (shaderManager != nullptr)
	{
		shaderManager->Stop(openGL);
		delete shaderManager;
		shaderManager = nullptr;
	}

	// Deleting map
	if (levelManager != nullptr)
	{
		levelManager->Stop();
		delete levelManager;
		levelManager = nullptr;
	}

	// Deleting player
	if (player != nullptr)
	{
		player->Stop();
		delete player;
		player = nullptr;
	}

	// Removes Camera & openGL ptr
	Screen::Stop();
}