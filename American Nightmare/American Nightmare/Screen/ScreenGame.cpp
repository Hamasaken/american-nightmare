#include "ScreenGame.h"

ScreenGame::ScreenGame() : Screen()
{
	solidShader = nullptr;
	player = nullptr;
	wall = nullptr;
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

	// Making wall big
	wall->setScale(glm::vec3(8, 5, 3));
}

void ScreenGame::Update()
{
	// Temporary spinning the background
	static int rotation = 0.f;
	rotation += 0.05f;
	wall->setRotation(glm::vec3(rotation, 0, 40));

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

	// Deleting model
	if (player != nullptr)
	{
		player->Stop();
		player = nullptr;
	}

	// Removes Camera & openGL ptr
	Screen::Stop();
}