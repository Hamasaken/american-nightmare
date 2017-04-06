#include "Game.h"

Game::Game()
{
	openGL = nullptr;
	solidShader = nullptr;
	model = nullptr;
	camera = nullptr;
}

Game::Game(const Game& other) { }

Game::~Game() { }

bool Game::Start(OpenGL* openGL, HWND hwnd)
{
	openGL = openGL;

	////////////////////////////////////////////////////////////
	// Creating Camera
	////////////////////////////////////////////////////////////
	camera = new Camera();
	if (camera == nullptr) return false;

	////////////////////////////////////////////////////////////
	// Creating Models
	////////////////////////////////////////////////////////////
	model = new Model();
	if (model == nullptr) return false;
	model->BuildTriangle(openGL); // TEMP
	// if (model->LoadModel(openGL, "Path/To/Model.file")) return false;

	////////////////////////////////////////////////////////////
	// Creating Shaders
	////////////////////////////////////////////////////////////
	std::string shaderPath = SHADER_PATH; 
	solidShader = new SolidShader();
	if (solidShader == nullptr) return false;
	solidShader->Start(openGL, hwnd, shaderPath + "solid_vs.glsl", shaderPath + "solid_fs.glsl");
	
	SetStartVariables();

	return true;
}

void Game::SetStartVariables()
{
	camera->setPosition(glm::vec3(0, 0, 10.f));
}

void Game::Stop()
{
	// Deleting Camera
	if (camera != nullptr) 
	{
		delete camera;
		camera = nullptr;
	}

	// Deleting models
	if (model != nullptr) 
	{
		model->Stop(openGL);
		model = nullptr;
	}

	// Deleting shaders
	if (solidShader != nullptr) 
	{
		solidShader->Stop(openGL);
		solidShader = nullptr;
	}

	openGL = nullptr;
}

bool Game::Update()
{
	if (!Draw())
		return false;

	return true;
}

bool Game::Draw()
{
	// Starting draw section
	openGL->StartDraw(CLEAR_COLOR);

	camera->buildViewMatrix();

	glm::mat4 world = openGL->getWorldMatrix();
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 projection = openGL->getProjectionMatrix();

	solidShader->SetShader(openGL);
	solidShader->SetParameters(openGL, world, view, projection);

	model->Draw(openGL);

	// Ending Draw section
	openGL->EndDraw();

	return true;
}