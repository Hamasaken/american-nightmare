#include "ScreenStart.h"

ScreenStart::ScreenStart() : Screen() 
{
	shaderManager = nullptr;
	guiManager = nullptr;
	materialManager = nullptr;
}

ScreenStart::ScreenStart(const ScreenStart& other) { }

ScreenStart::~ScreenStart() { }

bool ScreenStart::Start(glm::vec2 screenSize, glm::vec2 screenPosition, SoundManager* soundManager)
{
	Screen::Start(screenSize, screenPosition, soundManager);

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
	// Creating Material Manager and loading textures/materials
	////////////////////////////////////////////////////////////
	std::string texturePath = TEXTURE_PATH;
	materialManager = new MaterialManager();
	if (materialManager == nullptr) return false;

	// Loading materials
	materialManager->AddMaterial("lightmaterial", glm::vec3(1.f), 0.f, "lighttexture", texturePath + "gammal-dammsugare.jpg");
	if (materialManager->getMaterial("lightmaterial") == nullptr) printf("Light Material not found\n");

	////////////////////////////////////////////////////////////
	// Creating a GUI manager	
	////////////////////////////////////////////////////////////
	guiManager = new GUIManager();
	if (guiManager == nullptr) return false;
	if (!guiManager->Start(screenSize, screenPosition)) return false;
	guiManager->setShader(shaderManager->getShader("texture"));
	guiManager->AddButton(glm::vec3(0, 0, 0), glm::vec2(0.4f, 0.15f), materialManager->getMaterial("lightmaterial"));
	guiManager->AddButton(glm::vec3(0, 0.50f, 0), glm::vec2(0.4f, 0.15f), materialManager->getMaterial("lightmaterial"));
	guiManager->AddButton(glm::vec3(0, -0.50f, 0), glm::vec2(0.4f, 0.15f), materialManager->getMaterial("lightmaterial"));
	guiManager->setAlpha(1.f);

	// Setting starting variables
	SetStartVariables();

	return true;
}

void ScreenStart::SetStartVariables()
{
	// Backing the camera a little bit backwards
	camera->setPosition(glm::vec3(0, 0, 0));
}

void ScreenStart::Update(GLint deltaT)
{
	// Updating Buttons
	guiManager->Update(deltaT);
}

void ScreenStart::Draw()
{
	// Getting view matrix from camera
	camera->buildViewMatrix();

	for (Button* object : guiManager->getButtonList())
		DrawObjectGUI(object, shaderManager);
}

void ScreenStart::Stop()
{
	// Deleting shaders
	if (shaderManager != nullptr)
	{
		shaderManager->Stop();
		delete shaderManager;
		shaderManager = nullptr;
	}
	
	// Deleting material manager
	if (materialManager != nullptr)
	{
		materialManager->Clear();
		delete materialManager;
		materialManager = nullptr;
	}

	// Deleting gui
	if (guiManager != nullptr)
	{
		guiManager->Stop();
		delete guiManager;
		guiManager = nullptr;
	}

	// Deletes Camera & OpenGL ptr
	Screen::Stop();
}
