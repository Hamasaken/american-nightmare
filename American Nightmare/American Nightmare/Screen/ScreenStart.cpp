#include "ScreenStart.h"

ScreenStart::ScreenStart() : Screen() { }

ScreenStart::ScreenStart(const ScreenStart& other) { }

ScreenStart::~ScreenStart() { }

bool ScreenStart::Start(glm::vec2 screenSize, SoundManager* soundManager)
{
	Screen::Start(screenSize, soundManager);

	////////////////////////////////////////////////////////////
	// Creating Shader Manager
	////////////////////////////////////////////////////////////
	std::string shaderPath = SHADER_PATH;
	shaderManager = new ShaderManager();
	if (shaderManager == nullptr) return false;

	// Adding Shader Programs
	shaderManager->AddShader("solid", shaderPath + "solid_vs.glsl", shaderPath + "solid_fs.glsl");
	shaderManager->AddShader("texture", shaderPath + "texture_vs.glsl", shaderPath + "texture_fs.glsl");

	////////////////////////////////////////////////////////////
	// Creating Meny Buttons
	////////////////////////////////////////////////////////////
	std::string texturePath = TEXTURE_PATH;
	std::string fontPath = FONT_PATH;

	/*
	start = new Button();
	if (start == nullptr) return false;
	if (!start->Start(screenSize, glm::vec3(1, 1, 1), glm::vec2(200, 50), texturePath + "gammal-dammsugare.jpg", glm::vec4(0.8f, 1.f, 0.8f, 1.f))) return false;
	if (!start->StartText(fontPath + "framd.ttf", 40)) return false;
	start->setShader(shaderManager->getShader("solid"));

	// Poster Button
	posters = new Button();
	if (posters == nullptr) return false;
	if (!posters->Start(screenSize, glm::vec3(1, 1, 1), glm::vec2(200, 50), texturePath + "temp_ground.jpg", glm::vec4(0.8f, 1.f, 0.8f, 1.f))) return false;
	if (!posters->StartText(fontPath + "framd.ttf", 40)) return false;
	posters->setShader(shaderManager->getShader("texture"));

	// Options Button
	options = new Button();
	if (options == nullptr) return false;
	if (!options->Start(screenSize, glm::vec3(1, 1, 1), glm::vec2(200, 50), texturePath + "gammal-dammsugare.jpg", glm::vec4(0.8f, 1.f, 0.8f, 1.f))) return false;
	if (!options->StartText(fontPath + "framd.ttf", 40)) return false;
	options->setShader(shaderManager->getShader("texture"));

	// Exit Button
	exit = new Button();
	if (exit == nullptr) return false;
	if (!exit->Start(screenSize, glm::vec3(1, 1, 1), glm::vec2(200, 50), texturePath + "temp_ground.jpg", glm::vec4(0.8f, 1.f, 0.8f, 1.f))) return false;
	if (!exit->StartText(fontPath + "framd.ttf", 40)) return false;
	exit->setShader(shaderManager->getShader("texture"));

	// Logo Text
	logo = new Text();
	if (logo == nullptr) return false;
	if (!logo->Start(screenSize, fontPath+ "framd.ttf", 90, glm::vec3(290, 20, 0))) return false;
	logo->setShader(shaderManager->getShader("texture"));

	*/

	// Setting starting variables
	SetStartVariables();

	return true;
}

void ScreenStart::SetStartVariables()
{
	// Backing the camera a little bit backwards
	camera->setPosition(glm::vec3(0, 0, 0));
	
	// Creating Logo Text
	logo->CreateText("American Nightmare", glm::vec4(1.f, 0.6f, 0.3f, 1.f));
}

void ScreenStart::Update(GLint deltaT)
{
	// Drawing Buttons
	start->Update(deltaT);
	posters->Update(deltaT);
	options->Update(deltaT);
	exit->Update(deltaT);
}

void ScreenStart::Draw()
{
	// Getting view matrix from camera
	camera->buildViewMatrix();

	// Drawing button
	DrawObject(start, shaderManager);
	DrawObject(posters, shaderManager);
	DrawObject(options, shaderManager);
	DrawObject(exit, shaderManager);
	DrawObject(logo, shaderManager);
}

void ScreenStart::Stop()
{
	if (shaderManager != nullptr)
	{
		shaderManager->Stop();
		delete shaderManager;
		shaderManager = nullptr;
	}

	// Deleting buttons
	if (start != nullptr)
	{
		start->Stop();
		delete start;
		start = nullptr;
	}
	if (posters != nullptr)
	{
		posters->Stop();
		delete posters;
		posters = nullptr;
	}
	if (options != nullptr)
	{
		options->Stop();
		delete options;
		options = nullptr;
	}

	if (exit != nullptr)
	{
		exit->Stop();
		delete exit;
		exit = nullptr;
	}

	// Deleting texts
	if (logo != nullptr)
	{
		logo->Stop();
		delete logo;
		logo = nullptr;
	}

	// Deletes Camera & OpenGL ptr
	Screen::Stop();
}
