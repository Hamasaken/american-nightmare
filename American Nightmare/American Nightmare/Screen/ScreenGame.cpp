#include "ScreenGame.h"

ScreenGame::ScreenGame() : Screen()
{
	solidShader = nullptr;
	triangle = nullptr;
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
	triangle = new Model();
	if (triangle == nullptr) return false;

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

	triangle->BuildTriangle(openGL); // TEMP
	 // if (model->LoadModel(openGL, "Path/To/Model.file")) return false;
}

void ScreenGame::Update()
{
	// Update Stuff
}

void ScreenGame::Draw()
{
	// Starting draw section
	openGL->StartDraw(CLEAR_COLOR);

	// Building a new camera view matrix
	camera->buildViewMatrix();

	// Getting matrices
	glm::mat4 world = openGL->getWorldMatrix();
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 projection = openGL->getProjectionMatrix();

	// Setting Shader
	solidShader->SetShader(openGL);
	solidShader->SetParameters(openGL, world, view, projection);

	// Drawing triangle
	triangle->Draw(openGL);

	// Ending Draw section
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
	if (triangle != nullptr)
	{
		triangle->Stop(openGL);
		triangle = nullptr;
	}

	// Removes Camera & openGL ptr
	Screen::Stop();
}
