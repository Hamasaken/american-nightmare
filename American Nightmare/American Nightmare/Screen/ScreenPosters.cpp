#include "ScreenPosters.h"

ScreenPosters::ScreenPosters() : Screen()
{
	shaderManager = nullptr;
	posterListGUI = nullptr;
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
	particleManager->ShaderPair(shaderManager->getShader("particle_texture"), ParticleType::SMOKE);
	particleManager->ShaderPair(shaderManager->getShader("particle_light"), ParticleType::LIGHT_DUST);

	////////////////////////////////////////////////////////////
	// Creating Material Manager and loading textures/materials
	////////////////////////////////////////////////////////////
	materialManager = new MaterialManager();
	if (materialManager == nullptr) return false;

	// Loading button texture
	materialManager->AddMaterial("GUI_1_mat", glm::vec3(0.1f), glm::vec3(0.5, 0.5, 0.5), glm::vec3(1.f), 1.f, "GUI_1_tex", TEXTURE_PATH "GUI_btn_1.png");
	materialManager->AddMaterial("smokematerial", glm::vec3(0.1f), glm::vec3(0.3f, 0.4f, 0.9f), glm::vec3(1.f), 1.f, "smoketexture", TEXTURE_PATH "smoke.png");
	if (materialManager->getMaterial("GUI_1_mat") == nullptr) printf("Button Material not found\n");
	if (materialManager->getMaterial("smokematerial") == nullptr) printf("Smoke Material not found\n");

	// Loading posters
	std::vector<const MaterialManager::Material*> posters;
	for (int i = 1; i < 11; i++)
	{
		materialManager->AddMaterial("postermaterial_" + std::to_string(i), glm::vec3(1.f), glm::vec3(1.f), glm::vec3(1.f), 0.f, "poster_" + std::to_string(i), (POSTER_PATH "poster_" + std::to_string(i) + ".jpg"));
		posters.push_back(materialManager->getMaterial("postermaterial_" + std::to_string(i)));
	}

	////////////////////////////////////////////////////////////
	// Creating Models
	////////////////////////////////////////////////////////////
	meshManager = new MeshManager();
	if (meshManager == nullptr) return false;

	////////////////////////////////////////////////////////////
	// Creating a GUI manager	
	////////////////////////////////////////////////////////////
	posterListGUI = new GUIManager();
	if (posterListGUI == nullptr) return false;
	if (!posterListGUI->Start(screenSize, screenPosition)) return false;

	// Right side hidden
	posterListGUI->AddButton(GUIManager::CANCEL, glm::vec3(2.f, 0, 0), glm::vec2(0.400f, 0.800f), posters[0], meshManager->getMesh("quad"));

	// Back Button
	posterListGUI->AddButton(GUIManager::STARTMENY, glm::vec3(0, -0.85f, 0), glm::vec2(0.225f, 0.05955), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quad"), "Back", FONT_PATH INGAME_FONT, 28.f, glm::vec4(0.875f));
	
	// Title
	posterListGUI->AddText(glm::vec3(0.f, 0.75f, 0.f), 80.f, "Posters", FONT_PATH INGAME_FONT);
	
	// Unlocked text
	posterListGUI->AddText(glm::vec3(-0.65f, 0.65f, 0.f), 50.f, "Unlocked\n10 / 10", FONT_PATH INGAME_FONT);
	posterListGUI->getTextList()->at(1)->setRotation(glm::vec3(0, 0, glm::pi<float>() * 0.08f));

	// Adding posters
	float y = 0.25f, x = -0.6f;
	for (int i = 0; i < 10; i++)
	{
		if (i == 5) { y -= 0.5f; x = -0.6f; }
		posterListGUI->AddButton(GUIManager::OK, glm::vec3(x, y, 0), glm::vec2(0.100f, 0.200f), posters[i], meshManager->getMesh("quad"));
		x += 0.30f;
	}
	
	// Setting configurations on GuiManager
	posterListGUI->setAlpha(1.f);
	posterListGUI->setShader(shaderManager->getShader("texture"));

	// Setting starting variables
	SetStartVariables();

	return true;
}

void ScreenPosters::SetStartVariables()
{
	// Backing the camera a little bit backwards
	camera->setPosition(glm::vec3(0, 0, 15));

	// Adding some ambient smoke on postermeny
	particleManager->EffectConstantSmoke(glm::vec3(2, 4.25, 12.5f), materialManager->getTextureID("smoketexture"), 10, glm::vec4(0.7));
	particleManager->EffectConstantSmoke(glm::vec3(1, 4.25, 12.5f), materialManager->getTextureID("smoketexture"), 10, glm::vec4(0.5));
	particleManager->EffectConstantSmoke(glm::vec3(0, 4.25, 12.5f), materialManager->getTextureID("smoketexture"), 10, glm::vec4(0.4));
	particleManager->EffectConstantSmoke(glm::vec3(-1, 4.25, 12.5f), materialManager->getTextureID("smoketexture"), 10, glm::vec4(0.6));
	particleManager->EffectConstantSmoke(glm::vec3(-2, 4.25, 12.5f), materialManager->getTextureID("smoketexture"), 10, glm::vec4(0.8));

	particleManager->EffectConstantSmoke(glm::vec3(2, 2, 12.5f), materialManager->getTextureID("smoketexture"), 10, glm::vec4(0.7));
	particleManager->EffectConstantSmoke(glm::vec3(1, 2, 12.5f), materialManager->getTextureID("smoketexture"), 10, glm::vec4(0.5));
	particleManager->EffectConstantSmoke(glm::vec3(0, 2, 12.5f), materialManager->getTextureID("smoketexture"), 10, glm::vec4(0.4));
	particleManager->EffectConstantSmoke(glm::vec3(-1, 2, 12.5f), materialManager->getTextureID("smoketexture"), 10, glm::vec4(0.6));
	particleManager->EffectConstantSmoke(glm::vec3(-2, 2, 12.5f), materialManager->getTextureID("smoketexture"), 10, glm::vec4(0.8));

	// Dust effect
	particleManager->EffectLightDust(glm::vec3(0.f, 3, 0.f), glm::vec3(8, 8, 2), 50, glm::vec4(0.33f));
}

void ScreenPosters::Update(GLint deltaT)
{
	// Updating particles
	particleManager->Update(deltaT);

	// Explosion behind poster
	static GLfloat timerOnExplosion = -1;
	static bool shouldExplode = false;
	if (shouldExplode)
	{
		if (timerOnExplosion < NULL) { particleManager->EffectSmokeCloud(glm::vec3(0.f, 3, 12.5f), materialManager->getTextureID("smoketexture"), 20, glm::vec4(1.f)); shouldExplode = false; }
		else if (shouldExplode) timerOnExplosion -= deltaT;
	}

	// Updating GUI / Button presses
	posterListGUI->Update(deltaT);
	std::vector<std::pair<Button*, GUIManager::Action>>* buttons = posterListGUI->getButtonList();
	for (int i = 0; i < buttons->size(); i++)
	{
		Button* btn = buttons[0][i].first;
		GUIManager::Action action = buttons[0][i].second;
		if (btn->getPressed())
		{
			switch (action)
			{
				case GUIManager::Action::OK:
					soundManager->playModifiedSFX(SoundManager::SFX::SFX_BTN, 50, 0.2f);
					soundManager->playModifiedSFX(SoundManager::SFX::SFX_RtoL, 70, 0.05f);
					timerOnExplosion = EXPLOSION_TIMER;
					shouldExplode = true;
					posterListGUI->setCenter(glm::vec2(2.0f, 0)); 
					posterListGUI->getButton(0)->setMaterial(btn->getMaterial());
					break;
				case GUIManager::Action::CANCEL:
					soundManager->playModifiedSFX(SoundManager::SFX::SFX_BTN, 50, 0.2f); 
					posterListGUI->setCenter(glm::vec2(0, 0)); break;
				case GUIManager::Action::STARTMENY: 
					soundManager->playModifiedSFX(SoundManager::SFX::SFX_BTN, 50, 0.2f);
					*state = State::StartMeny; 
					break; 
			}
			btn->setPressed(false);
		}
	}
}

void ScreenPosters::Draw()
{
	// Getting view matrix from camera
	camera->buildViewMatrix();
	
	// Drawing particles
	for (ParticleEmitter* emitter : *particleManager->getEmitters())
		DrawParticles(emitter, shaderManager);

	// Drawing GUI
	std::vector<std::pair<Button*, GUIManager::Action>>* buttons = posterListGUI->getButtonList();
	for (int i = 0; i < buttons->size(); i++)
	{
		DrawObjectGUI(buttons[0][i].first, shaderManager);
		if (buttons[0][i].first->getText()) DrawObjectGUI(buttons[0][i].first->getText(), shaderManager);
	}
	std::vector<Text*>* txts = posterListGUI->getTextList();
	for (int i = 0; i < txts->size(); i++)
		DrawObjectGUI(txts[0][i], shaderManager);
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
	if (posterListGUI != nullptr)
	{
		posterListGUI->Stop();
		delete posterListGUI;
		posterListGUI = nullptr;
	}

	// Deleting particle manager
	if (particleManager != nullptr)
	{
		particleManager->Stop();
		delete particleManager;
		particleManager = nullptr;
	}

	// Deleting meshmanager
	if (meshManager != nullptr)
	{
		meshManager->Clear();
		delete meshManager;
		meshManager = nullptr;
	}

	// Deletes Camera & OpenGL ptr
	Screen::Stop();
}

void ScreenPosters::UpdateScreenProperties(glm::vec2 screenSize, glm::vec2 screenPos)
{
	Screen::UpdateScreenProperties(screenSize, screenPos);

	// Updating guimanager
	posterListGUI->setScreenPosition(screenPos);
	posterListGUI->setScreenSize(screenSize);
}