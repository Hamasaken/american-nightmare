#include "ScreenGame.h"

ScreenGame::ScreenGame() : Screen()
{
	solidShader = nullptr;
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
	// Creating Models
	////////////////////////////////////////////////////////////
	std::string modelPath = MODEL_PATH;
	std::string texturePath = TEXTURE_PATH;

	// Creating the player object
	player = new Player();
	if (player == nullptr) return false;
	if (!player->Start(openGL, modelPath + "model.m", texturePath + "texture.t")) 
		return false;

	// Creating a simple background wall
	wall = new Object();
	if (wall == nullptr) return false;
	if (!wall->Start(openGL, modelPath + "model.m", texturePath + "texture.t"))
		return false;

	// Creating a simple floor object too see depth
	floor = new Object();
	if (floor == nullptr) return false;
	if (!floor->Start(openGL, modelPath + "model.m", texturePath + "texture.t"))
		return false;

	////////////////////////////////////////////////////////////
	// Creating Shaders
	////////////////////////////////////////////////////////////
	std::string shaderPath = SHADER_PATH;

	// Creating a simple color shader
	solidShader = new SolidShader();
	if (solidShader == nullptr) return false;
	solidShader->Start(openGL, shaderPath + "solid_vs.glsl", shaderPath + "solid_fs.glsl");

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
	DrawObject(wall, solidShader);

	// Drawing background wall
	DrawObject(floor, solidShader);

	// Drawing player
	DrawObject(player, solidShader);

	////////////////////////////////////////////////////////////
	// Ending draw section
	////////////////////////////////////////////////////////////
	openGL->EndDraw();
}

void ScreenGame::Stop()
{
	// Deleting shaders
	if (solidShader != nullptr)
	{
		solidShader->Stop(openGL);
		solidShader = nullptr;
	}

	// Deleting player
	if (player != nullptr)
	{
		player->Stop();
		player = nullptr;
	}

	// Deleting wall
	if (wall != nullptr)
	{
		wall->Stop();
		wall = nullptr;
	}

	// Deleting floor
	if (floor != nullptr)
	{
		floor->Stop();
		floor = nullptr;
	}

	// Removes Camera & openGL ptr
	Screen::Stop();
}