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
}

void ScreenGame::Draw()
{

	// Getting matrices
	glm::mat4 world = openGL->getWorldMatrix();
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 projection = openGL->getProjectionMatrix();

	////////////////////////////////////////////////////////////
	// Starting draw section
	////////////////////////////////////////////////////////////
	openGL->StartDraw(CLEAR_COLOR);

	// Building a new camera view matrix
	camera->buildViewMatrix();

	// Setting Shader
	solidShader->SetShader(openGL);
	solidShader->SetParameters(openGL, world, view, projection);

	// Drawing player
	player->Draw();

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
