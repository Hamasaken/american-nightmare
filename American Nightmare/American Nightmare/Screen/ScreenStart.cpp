#include "ScreenStart.h"

ScreenStart::ScreenStart() : Screen()
{

}

ScreenStart::ScreenStart(const ScreenStart& other) { }

ScreenStart::~ScreenStart() { }

bool ScreenStart::Start(glm::vec2 screenSize)
{
	Screen::Start(screenSize);

	////////////////////////////////////////////////////////////
	// Creating Shader Manager
	////////////////////////////////////////////////////////////
	std::string shaderPath = SHADER_PATH;
	shaderManager = new ShaderManager();
	if (shaderManager == nullptr) return false;

	// Adding Shader Programs
	shaderManager->AddShader("solid", shaderPath + "solid_vs.glsl", shaderPath + "solid_fs.glsl");

	////////////////////////////////////////////////////////////
	// Creating Meny Buttons
	////////////////////////////////////////////////////////////
	button = new Button();
	if (button == nullptr) return false;
	if (!button->Start(screenSize, glm::vec2(0, 0), glm::vec2(25, 25))) return false;
	button->setShader(shaderManager->getShader("solid"));

	SetStartVariables();

	return true;
}

void ScreenStart::SetStartVariables()
{
	// Backing the camera a little bit backwards
	camera->setPosition(glm::vec3(0, 0, 10));
}

void ScreenStart::Update(GLint deltaT)
{
	button->Update(deltaT);
}

void ScreenStart::Draw()
{
	// Getting view matrix from camera
	camera->buildViewMatrix();

	// Drawing button
	DrawObject(button, shaderManager);
}

void ScreenStart::Stop()
{
	// Deleting button
	if (button != nullptr)
	{
		button->Stop();
		delete button;
		button = nullptr;
	}

	// Deletes Camera & OpenGL ptr
	Screen::Stop();
}
