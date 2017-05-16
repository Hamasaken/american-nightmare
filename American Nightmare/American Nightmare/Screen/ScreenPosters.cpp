#include "ScreenPosters.h"

ScreenPosters::ScreenPosters() : Screen()
{
	shaderManager = nullptr;
	guiManager = nullptr;
	materialManager = nullptr;
	meshManager = nullptr;
}

ScreenPosters::ScreenPosters(const ScreenPosters& other) { }

ScreenPosters::~ScreenPosters() { }

bool ScreenPosters::Start(glm::vec2 screenSize, glm::vec2 screenPosition, State* state, SoundManager* soundManager)
{
	Screen::Start(screenSize, screenPosition, state, soundManager);

	////////////////////////////////////////////////////////////
	// Creating Shader Manager
	////////////////////////////////////////////////////////////
	std::string shaderPath = SHADER_PATH;
	shaderManager = new ShaderManager();
	if (shaderManager == nullptr) return false;

	// Adding Shader Programs
	shaderManager->AddShader("texture", shaderPath + "texture_vs.glsl", shaderPath + "texture_fs.glsl");
	shaderManager->AddShader("particle_light", shaderPath + "particle_light_vs.glsl", shaderPath + "particle_light_gs.glsl", shaderPath + "particle_light_fs.glsl");
	shaderManager->AddShader("particle_texture", shaderPath + "particle_texture_vs.glsl", shaderPath + "particle_texture_gs.glsl", shaderPath + "particle_texture_fs.glsl");

	////////////////////////////////////////////////////////////
	// Creating Particle Manager
	////////////////////////////////////////////////////////////
	particleManager = new ParticleManager();
	if (particleManager == nullptr) return false;
	particleManager->ShaderPair(shaderManager->getShader("particle_light"), ParticleType::LIGHT);
	particleManager->ShaderPair(shaderManager->getShader("particle_light"), ParticleType::BLOOD);
	particleManager->ShaderPair(shaderManager->getShader("particle_texture"), ParticleType::TEXTURE);

	////////////////////////////////////////////////////////////
	// Creating Material Manager and loading textures/materials
	////////////////////////////////////////////////////////////
	materialManager = new MaterialManager();
	if (materialManager == nullptr) return false;

	// Loading materials
	materialManager->AddMaterial("GUI_1_mat", glm::vec3(0.1f), glm::vec3(0.1f), glm::vec3(0.1f), 1.f, "GUI_1_tex", TEXTURE_PATH "GUI_btn_1.png");
	if (materialManager->getMaterial("GUI_1_mat") == nullptr) printf("Button Material not found\n");

	////////////////////////////////////////////////////////////
	// Creating Models
	////////////////////////////////////////////////////////////
	meshManager = new MeshManager();
	if (meshManager == nullptr) return false;

	////////////////////////////////////////////////////////////
	// Creating a GUI manager	
	////////////////////////////////////////////////////////////
	guiManager = new GUIManager();
	if (guiManager == nullptr) return false;
	if (!guiManager->Start(screenSize, screenPosition)) return false;
	guiManager->AddButton(GUIManager::STARTMENY, glm::vec3(0, -0.45f, 0), glm::vec2(0.225f, 0.075f), materialManager->getMaterial("GUI_1_mat"), nullptr, "Back", FONT_PATH INGAME_FONT, 40.f, glm::vec4(1, 1, 1, 1));
	guiManager->AddText(glm::vec3(0.f, 0.5f, 0.f), 40.f, "Posters", FONT_PATH INGAME_FONT);
	guiManager->setAlpha(1.f);
	guiManager->setShader(shaderManager->getShader("texture"));

	// Setting starting variables
	SetStartVariables();

	return true;
}

void ScreenPosters::SetStartVariables()
{
	// Backing the camera a little bit backwards
	camera->setPosition(glm::vec3(0, 0, 15));
}

void ScreenPosters::Update(GLint deltaT)
{
	// Updating Buttons
	guiManager->Update(deltaT);

//	particleManager->EffectExplosionLights(glm::vec3(13, 3, 0), 1, glm::vec4(1.f, 0.5f, 1.f, 0.1f));
//	particleManager->EffectExplosionLights(glm::vec3(-13, 3, 0), 1, glm::vec4(0.5f, 1.f, 1.f, 0.1f));
//	particleManager->Update(deltaT);

	for (std::pair<Button*, GUIManager::Action> button : *guiManager->getButtonList())
	{
		if (button.first->getPressed())
		{
			switch (button.second)
			{ case GUIManager::Action::STARTMENY: *state = State::StartMeny;	break; }
			button.first->setPressed(false);
		}
	}
}

void ScreenPosters::Draw()
{
	// Getting view matrix from camera
	camera->buildViewMatrix();
	
	// Drawing GUI
	for (std::pair<Button*, GUIManager::Action> button : *guiManager->getButtonList())
	{
		DrawObjectGUI(button.first, shaderManager);
		if (button.first->getText() != nullptr)
			DrawObjectGUI(button.first->getText(), shaderManager);
	}
	for (Text* object : *guiManager->getTextList())
		DrawObjectGUI(object, shaderManager);
}

void ScreenPosters::Stop()
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

	if (particleManager != nullptr)
	{
		particleManager->Stop();
		delete particleManager;
		particleManager = nullptr;
	}

	// Deletes Camera & OpenGL ptr
	Screen::Stop();
}
