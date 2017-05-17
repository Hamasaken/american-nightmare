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
	particleManager->ShaderPair(shaderManager->getShader("particle_light"), ParticleType::LIGHT_DUST);
	particleManager->EffectLightDust();

	////////////////////////////////////////////////////////////
	// Creating Material Manager and loading textures/materials
	////////////////////////////////////////////////////////////
	materialManager = new MaterialManager();
	if (materialManager == nullptr) return false;

	// Loading materials
	materialManager->AddMaterial("titlematerial", glm::vec3(1.f), glm::vec3(1.f), glm::vec3(1.f), 0.f, "titletexture", TEXTURE_PATH "title.jpg");
	materialManager->AddMaterial("GUI_1_mat", glm::vec3(0.1f), glm::vec3(0.3f, 0.4f, 0.9f), glm::vec3(1.f), 1.f, "GUI_1_tex", TEXTURE_PATH "GUI_btn_1.png");
	if (materialManager->getMaterial("titlematerial") == nullptr) printf("Title Material not found\n");
	if (materialManager->getMaterial("GUI_1_mat") == nullptr) printf("Light Material not found\n");

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
	posterListGUI->AddButton(GUIManager::STARTMENY, glm::vec3(0, -0.85f, 0), glm::vec2(0.225f, 0.075f), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quad"), "Back", FONT_PATH INGAME_FONT, 40.f, glm::vec4(1, 1, 1, 1));
	posterListGUI->AddText(glm::vec3(0.f, 0.85f, 0.f), 40.f, "Posters", FONT_PATH INGAME_FONT);
	
	// Posters
	float y = 0.25f, x = -0.6f;
	for (int i = 0; i < 10; i++)
	{
		if (i == 5) { y -= 0.5f; x = -0.6f; }
		posterListGUI->AddButton(GUIManager::OK, glm::vec3(x, y, 0), glm::vec2(0.100f, 0.200f), materialManager->getMaterial("titlematerial"), meshManager->getMesh("quad"));
		x += 0.30f;
	}

	// Right side hidden
	posterListGUI->AddButton(GUIManager::CANCEL, glm::vec3(2.f, 0, 0), glm::vec2(0.400f, 0.800f), materialManager->getMaterial("titlematerial"), meshManager->getMesh("quad"));
	
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
}

void ScreenPosters::Update(GLint deltaT)
{
	// Updating Buttons
	posterListGUI->Update(deltaT);
	particleManager->Update(deltaT);

	for (std::pair<Button*, GUIManager::Action> button : *posterListGUI->getButtonList())
	{
		if (button.first->getPressed())
		{
			switch (button.second) 
			{
				case GUIManager::Action::OK: posterListGUI->setCenter(glm::vec2(2.0f, 0)); break;
				case GUIManager::Action::CANCEL: posterListGUI->setCenter(glm::vec2(0, 0)); break;
				case GUIManager::Action::STARTMENY: *state = State::StartMeny; break; 
			}
			button.first->setPressed(false);
		}
	}
}

void ScreenPosters::Draw()
{
	// Getting view matrix from camera
	camera->buildViewMatrix();
	
	// Drawing GUI
	for (std::pair<Button*, GUIManager::Action> button : *posterListGUI->getButtonList())
	{
		DrawObjectGUI(button.first, shaderManager);
		if (button.first->getText() != nullptr)
			DrawObjectGUI(button.first->getText(), shaderManager);
	}
	for (Text* object : *posterListGUI->getTextList())
		DrawObjectGUI(object, shaderManager);

	// Drawing particles
	for (ParticleEmitter* emitter : *particleManager->getEmitters())
		DrawParticles(emitter, shaderManager);
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
