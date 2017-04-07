#include "ScreenGame.h"

ScreenGame::ScreenGame() : Screen()
{
	solidShader = nullptr;
	player = nullptr;
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
	player = new Player();
	if (player == nullptr) return false;
	if (!player->Start(openGL, modelPath + "model.m", texturePath + "texture.t")) 
		return false;

	////////////////////////////////////////////////////////////
	// Creating Shaders
	////////////////////////////////////////////////////////////
	std::string shaderPath = SHADER_PATH;
	solidShader = new SolidShader();
	if (solidShader == nullptr) return false;
	solidShader->Start(openGL, shaderPath + "solid_vs.glsl", shaderPath + "solid_fs.glsl");

	SetStartVariables();

	return true;
}

void ScreenGame::SetStartVariables()
{
	// Backing the camera a little bit backwards
	camera->setPosition(glm::vec3(0, 0, 10));
}

void ScreenGame::Update()
{
	// Updating player
	player->Update();

	// Follows player
	camera->smoothToPosition(glm::vec3(player->getPosition().x, player->getPosition().y, camera->getPosition().z));
}

void ScreenGame::Draw()
{
	////////////////////////////////////////////////////////////
	// Starting draw section
	////////////////////////////////////////////////////////////
	openGL->StartDraw(CLEAR_COLOR);

	// Building a new camera view matrix
	camera->buildViewMatrix();

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
