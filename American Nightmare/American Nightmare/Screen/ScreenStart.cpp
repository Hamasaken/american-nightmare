#include "ScreenStart.h"

ScreenStart::ScreenStart() : Screen() 
{
	shaderManager = nullptr;
	guiManager = nullptr;
	materialManager = nullptr;
	meshManager = nullptr;
}

ScreenStart::ScreenStart(const ScreenStart& other) { }

ScreenStart::~ScreenStart() { }

bool ScreenStart::Start(glm::vec2 screenSize, glm::vec2 screenPosition, State* state, SoundManager* soundManager)
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
	particleManager->ShaderPair(shaderManager->getShader("particle_texture"), ParticleType::SMOKE);
	particleManager->ShaderPair(shaderManager->getShader("particle_light"), ParticleType::LIGHT_DUST);

	////////////////////////////////////////////////////////////
	// Creating Material Manager and loading textures/materials
	////////////////////////////////////////////////////////////
	materialManager = new MaterialManager();
	if (materialManager == nullptr) return false;

	// Loading materials
	materialManager->AddMaterial("GUI_1_mat", glm::vec3(0.1f), glm::vec3(0.5, 0.5, 0.5), glm::vec3(1.f), 1.f, "GUI_1_tex", TEXTURE_PATH "GUI_btn_1.png");
	materialManager->AddMaterial("backgroundmaterial", glm::vec3(0.1f), glm::vec3(1, 1, 1), glm::vec3(1.f), 1.f, "backgroundtexture", TEXTURE_PATH "background_2.jpg");
	materialManager->AddMaterial("smokematerial", glm::vec3(0.1f), glm::vec3(0.3f, 0.4f, 0.9f), glm::vec3(1.f), 1.f, "smoketexture", TEXTURE_PATH "smoke.png");
	if (materialManager->getMaterial("GUI_1_mat") == nullptr) printf("Button Material not found\n");
	if (materialManager->getMaterial("smokematerial") == nullptr) printf("Smoke Material not found\n");
	if (materialManager->getMaterial("backgroundmaterial") == nullptr) printf("Background material not found\n");

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
	guiManager->AddButton(GUIManager::PLAY, glm::vec3(0, 0.20f, 0), glm::vec2(0.225f, 0.05955), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quad"), "Play", FONT_PATH INGAME_FONT, 28.f, glm::vec4(0.875f));
	guiManager->AddButton(GUIManager::OPTIONS, glm::vec3(0, 0.f, 0), glm::vec2(0.225f, 0.05955), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quad"), "options", FONT_PATH INGAME_FONT, 28.f, glm::vec4(0.875f));
	guiManager->AddButton(GUIManager::POSTERS, glm::vec3(0, -0.20f, 0), glm::vec2(0.225f, 0.05955), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quad"), "posters", FONT_PATH INGAME_FONT, 28.f, glm::vec4(0.875f));
	guiManager->AddButton(GUIManager::EXIT, glm::vec3(0, -0.40f, 0), glm::vec2(0.225f, 0.05955), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quad"), "quit", FONT_PATH INGAME_FONT, 28.f, glm::vec4(0.875f));
	guiManager->AddText(glm::vec3(0.f, 0.6f, 0.f), 120.f, "American Nightmare", FONT_PATH INGAME_FONT);
	guiManager->setAlpha(0.9f);
	guiManager->setShader(shaderManager->getShader("texture"));

	// Adding background
	background = new Button();
	background->Start(screenSize, glm::vec3(0.f, 0.f, 0.1f), glm::vec2(1), materialManager->getMaterial("backgroundmaterial"), meshManager->getMesh("quad"));
	background->setShader(shaderManager->getShader("texture"));

	// Setting starting variables
	SetStartVariables();

	return true;
}

void ScreenStart::SetStartVariables()
{
	// Adding some ambient smoke on startmenu
	particleManager->EffectConstantSmoke(glm::vec3(2, 2, 12.5f), materialManager->getTextureID("smoketexture"), 10, glm::vec4(0.7));
	particleManager->EffectConstantSmoke(glm::vec3(1, 2, 12.5f), materialManager->getTextureID("smoketexture"), 10, glm::vec4(0.5));
	particleManager->EffectConstantSmoke(glm::vec3(0, 2, 12.5f), materialManager->getTextureID("smoketexture"), 10, glm::vec4(0.4));
	particleManager->EffectConstantSmoke(glm::vec3(-1, 2, 12.5f), materialManager->getTextureID("smoketexture"), 10, glm::vec4(0.6));
	particleManager->EffectConstantSmoke(glm::vec3(-2, 2, 12.5f), materialManager->getTextureID("smoketexture"), 10, glm::vec4(0.8));

	// Dust effect
	particleManager->EffectLightDust(glm::vec3(0.f, 3, 0.f), glm::vec3(10, 6, 2), 125, glm::vec4(0.35f));

	// Backing the camera a little bit backwards
	camera->setPosition(glm::vec3(0, 0, 15));

	// Setting meny music
	soundManager->playSong(SoundManager::SONG::MUSIC_WOOP);
}

void ScreenStart::Update(GLint deltaT)
{
	// Updating Buttons
	guiManager->Update(deltaT);

	// Updating particles
	particleManager->Update(deltaT);

	for (std::pair<Button*, GUIManager::Action> button : *guiManager->getButtonList())
	{
		if (button.first->getPressed())
		{
			switch (button.second)
			{
			case GUIManager::Action::PLAY:		soundManager->playModifiedSFX(SoundManager::SFX::SFX_BTN, 50, 0.2f); *state = State::Game;		break;
			case GUIManager::Action::OPTIONS:	soundManager->playModifiedSFX(SoundManager::SFX::SFX_BTN, 50, 0.2f); *state = State::Options;	break;
			case GUIManager::Action::POSTERS:	soundManager->playModifiedSFX(SoundManager::SFX::SFX_BTN, 50, 0.2f); *state = State::Posters;	break;
			case GUIManager::Action::EXIT:		soundManager->playModifiedSFX(SoundManager::SFX::SFX_BTN, 50, 0.2f); *state = State::Exit;		break;
			}
			button.first->setPressed(false);
		}
	}
}

void ScreenStart::UpdateScreenProperties(glm::vec2 screenSize, glm::vec2 screenPos)
{
	Screen::UpdateScreenProperties(screenSize, screenPos);

	// Updating guimanager
	guiManager->setScreenPosition(screenPos);
	guiManager->setScreenSize(screenSize);
}

void ScreenStart::Draw()
{
	// Getting view matrix from camera
	camera->buildViewMatrix();
	
	// Drawing background
	DrawObjectGUI(background, shaderManager);

	// Drawing GUI
	std::vector<std::pair<Button*, GUIManager::Action>>* buttons = guiManager->getButtonList();
	for (int i = 0; i < buttons->size(); i++)
	{
		DrawObjectGUI(buttons[0][i].first, shaderManager);
		if (buttons[0][i].first->getText()) DrawObjectGUI(buttons[0][i].first->getText(), shaderManager);
	}
	std::vector<Text*>* txts = guiManager->getTextList();
	for (int i = 0; i < txts->size(); i++)
		DrawObjectGUI(txts[0][i], shaderManager);

	// Drawing particles
	for (ParticleEmitter* emitter : *particleManager->getEmitters())
		DrawParticles(emitter, shaderManager);
}

void ScreenStart::Stop()
{
	// Deleteing background
	if (background != nullptr)
	{
		background->Stop();
		delete background;
		background = nullptr;
	}

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

	if (meshManager != nullptr)
	{
		meshManager->Clear();
		delete meshManager;
		meshManager = nullptr;
	}

	// Deletes Camera & OpenGL ptr
	Screen::Stop();
}