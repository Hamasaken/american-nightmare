#include "ScreenGame.h"

ScreenGame::ScreenGame() : Screen()
{
	shaderManager = nullptr;
	player = nullptr;
	wall = nullptr;
	floor = nullptr;
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

	// Setting startvariables
	SetStartVariables();

	return true;
}

void ScreenGame::SetStartVariables()
{
	// Backing the camera a little bit backwards
	camera->setPosition(glm::vec3(0, 0, 10));

	// Making wall & floor bigger
	wall->setScale(glm::vec3(8, 5, 3));
	wall->setRotation(glm::vec3(0, 0, 40));
	wall->setPosition(glm::vec3(-2, 0, -10));

	// Setting floor varaibles
	floor->setScale(glm::vec3(15, 15, 0));;
	floor->setPosition(glm::vec3(0, -10, 0));
	floor->setRotation(glm::vec3(0.f, -90, 0.f));
}

void ScreenGame::Update()
{

	// Updating player
	player->Update();

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

	// Drawing background wall
	DrawObject(wall, shaderManager);

	// Drawing background wall
	DrawObject(floor, shaderManager);

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

	// Deleting player
	if (player != nullptr)
	{
		player->Stop();
		delete player;
		player = nullptr;
	}

	// Deleting wall
	if (wall != nullptr)
	{
		wall->Stop();
		delete wall;
		wall = nullptr;
	}

	// Deleting floor
	if (floor != nullptr)
	{
		floor->Stop();
		delete floor;
		floor = nullptr;
	}

	// Removes Camera & openGL ptr
	Screen::Stop();
}