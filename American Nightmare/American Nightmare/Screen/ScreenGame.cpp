#include "ScreenGame.h"

ScreenGame::ScreenGame() : Screen()
{
	particleManager = nullptr;
	shaderManager = nullptr;
	levelManager = nullptr;
	materialManager = nullptr;
	guiManager = nullptr;
}

ScreenGame::ScreenGame(const ScreenGame& other) { }

ScreenGame::~ScreenGame() { }

bool ScreenGame::Start(glm::vec2 screenSize, glm::vec2 screenPosition, State* state, SoundManager* soundManager)
{
	// Starting Camera & getting openGL pointer
	Screen::Start(screenSize, screenPosition, state, soundManager);

	////////////////////////////////////////////////////////////
	// Creating Shader Manager
	////////////////////////////////////////////////////////////
	std::string shaderPath = SHADER_PATH;
	shaderManager = new ShaderManager();
	if (shaderManager == nullptr) return false;

	// Adding Shader Programs
	shaderManager->AddShader("solid", shaderPath + "solid_vs.glsl", shaderPath + "solid_fs.glsl");
	shaderManager->AddShader("texture", shaderPath + "texture_vs.glsl", shaderPath + "texture_fs.glsl");
	shaderManager->AddShader("texture_animation", shaderPath + "texture_animation_vs.glsl", shaderPath + "texture_fs.glsl");
	shaderManager->AddShader("texture_animation_normal", shaderPath + "texture_animation_vs.glsl", shaderPath + "texture_animation_fs.glsl");
	shaderManager->AddShader("particle", shaderPath + "particle_vs.glsl", shaderPath + "particle_gs.glsl", shaderPath + "particle_fs.glsl");
	shaderManager->AddShader("particle_light", shaderPath + "particle_light_vs.glsl", shaderPath + "particle_light_gs.glsl", shaderPath + "particle_light_fs.glsl");
	shaderManager->AddShader("deferred", shaderPath + "dr_vs.glsl", shaderPath + "dr_fs.glsl");
	shaderManager->AddShader("deferred_final", shaderPath + "drfinal_vs.glsl", shaderPath + "drfinal_fs.glsl");
	shaderManager->AddShader("shadow", shaderPath + "shadowmap_vs.glsl", shaderPath + "shadowmap_fs.glsl");
	shaderManager->AddShader("debug", shaderPath + "debug_shader_vs.glsl", shaderPath + "debug_shader_fs.glsl");

	// Initialize Deferred Rendering
	drRendering.Start(screenSize, shaderManager->getShader("deferred_final"), shaderManager->getShader("shadow"));

	////////////////////////////////////////////////////////////
	// Creating Material Manager and loading textures/materials
	////////////////////////////////////////////////////////////
	std::string texturePath = TEXTURE_PATH;
	materialManager = new MaterialManager();
	if (materialManager == nullptr) return false;

	// Loading materials
	materialManager->AddMaterial("playermaterial", glm::vec3(0.1), 1.f, "playertexture", texturePath + "Walk01.png");
	materialManager->AddMaterial("lightmaterial", glm::vec3(1.f), 0.f, "lighttexture", texturePath + "gammal-dammsugare.jpg");
	materialManager->AddMaterial("groundmaterial", glm::vec3(0.1f), 1.f, "groundtexture", texturePath + "temp_ground.jpg");
	materialManager->AddMaterial("backgroundmaterial", glm::vec3(0.1f), 1.f, "backgroundtexture", texturePath + "temp_background.jpg");
	if (materialManager->getMaterial("playermaterial") == nullptr) printf("Player Material not found\n");
	if (materialManager->getMaterial("lightmaterial") == nullptr) printf("Light Material not found\n");
	if (materialManager->getMaterial("groundmaterial") == nullptr) printf("Ground Material not found\n");
	if (materialManager->getMaterial("backgroundmaterial") == nullptr) printf("Background Material not found\n");

	////////////////////////////////////////////////////////////
	// Creating Particle Manager
	////////////////////////////////////////////////////////////
	particleManager = new ParticleManager();
	if (particleManager == nullptr) return false;
	if (!particleManager->Start())
		return false;
	particleManager->setShader(shaderManager->getShader("particle_light"));

	////////////////////////////////////////////////////////////
	// Creating Models
	////////////////////////////////////////////////////////////

	// Creating a simple level
	levelManager = new LevelManager();
	if (levelManager == nullptr) return false;
	if (!levelManager->Start(shaderManager->getShader("texture_animation_normal"), materialManager, particleManager))
		return false;

	////////////////////////////////////////////////////////////
	// Creating a GUI manager	
	////////////////////////////////////////////////////////////
	guiManager = new GUIManager();
	if (guiManager == nullptr) return false;
	if (!guiManager->Start(screenSize, screenPosition)) return false;
	guiManager->setShader(shaderManager->getShader("texture"));
	guiManager->AddButton(GUIManager::STARTMENY, glm::vec3(0, 0, 0), glm::vec2(0.4f, 0.15f), materialManager->getMaterial("lightmaterial"));
	guiManager->AddButton(GUIManager::OK, glm::vec3(0, 0.50f, 0), glm::vec2(0.4f, 0.15f), materialManager->getMaterial("lightmaterial"));
	guiManager->AddButton(GUIManager::EXIT, glm::vec3(0, -0.50f, 0), glm::vec2(0.4f, 0.15f), materialManager->getMaterial("lightmaterial"));
//	guiManager->AddText(glm::vec3(0, 0.5f, 0), 30.f, "WHAT", "framd.ttf");
	guiManager->setAlpha(0.f);

	// Setting startvariables
	SetStartVariables();

	return true;
}

void ScreenGame::SetStartVariables()
{
	// Setting game state
	gameState = PLAYING;

	// Backing the camera a little bit backwards
	camera->setPosition(glm::vec3(0, 0, 15));

	// Making wall & floor bigger
	levelManager->LoadLevel(shaderManager->getShader("deferred"), "0.lvl");

	// Adding shadow light to drRendering
	drRendering.setShadowLight(levelManager->getLightManager()->getDirectionalLightList()[0]);
}

void ScreenGame::Update(GLint deltaT)
{
	switch (gameState)
	{
	case GameState::PAUSING: UpdatePausing(deltaT); break;
	case GameState::PAUSED: UpdatePaused(deltaT); break;
	case GameState::PLAYING: UpdatePlaying(deltaT); break;
	case GameState::UNPAUSING: UpdateUnpausing(deltaT); break;
	}
}

void ScreenGame::Draw()
{
	if (drRendering.useShadows())
	{
		// Bindind depth FBO
		glBindFramebuffer(GL_FRAMEBUFFER, drRendering.getShadowFBO());

		shaderManager->setShader(drRendering.getShadowShader());

		glClear(GL_DEPTH_BUFFER_BIT);

		// Drawing shadowmap
		for (Object* object : levelManager->getMap())
			DrawObjectShadowMap(object, shaderManager, drRendering.getLightSpaceMatrix());

		DrawObjectShadowMap(levelManager->getPlayer(), shaderManager, drRendering.getLightSpaceMatrix());

		DrawObjectShadowMap(levelManager->getEnemy(), shaderManager, drRendering.getLightSpaceMatrix());

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	// Disable Blend for DR
	glDisable(GL_BLEND);

	// Bind DR frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, drRendering.getDRFBO());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Drawing map
	for (Object* object : levelManager->getMap())
		DrawObjectGeometryPass(object, shaderManager);

	//Draw Projectile///////////////////////////////////////////////////////
	////TESTING
	//////////////////////////////////////////////////////////////////////
	//DrawObject(levelManager->getProjectile(), shaderManager);
	//DrawObject(levelManager->getProjectiles(), shaderManager);


	// Transfer deferred rendering depth buffer to forward rendering
	glBindFramebuffer(GL_READ_FRAMEBUFFER, drRendering.getDRFBO());
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, screenSize.x, screenSize.y, 0, 0, screenSize.x, screenSize.y, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	// Unbind DR frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Reenable Blend
	glEnable(GL_BLEND);

	// DR: Light pass
	DrawObjectLightPass(&drRendering, shaderManager, levelManager->getLightManager()->getPointLightList(), levelManager->getLightManager()->getDirectionalLightList(), drRendering.getLightSpaceMatrix(), drRendering.useShadows());


	// Drawing player
	DrawObjectAnimation(levelManager->getPlayer(), shaderManager, levelManager->getLightManager()->getPointLightList(), levelManager->getLightManager()->getDirectionalLightList(), drRendering.getLightSpaceMatrix(), drRendering.getShadowMap(), drRendering.useShadows());

	// Draw Enemy
	DrawObjectAnimation(levelManager->getEnemy(), shaderManager, levelManager->getLightManager()->getPointLightList(), levelManager->getLightManager()->getDirectionalLightList(), drRendering.getLightSpaceMatrix(), drRendering.getShadowMap(), drRendering.useShadows());

	// Drawing vertices
	DrawParticles(particleManager, shaderManager);

	// Drawing gui Manager if we're paused
	if (gameState != PLAYING)
	{
		for (std::pair<Button*, GUIManager::Action> button : *guiManager->getButtonList())
			DrawObjectGUI(button.first, shaderManager);
		for (Text* object : *guiManager->getTextList())
			DrawObjectGUI(object, shaderManager);
	}

	// Temp shadow map debug
	/*if (drRendering.useShadows())
	{
		shaderManager->setShader("debug");

		glm::mat4 tempWorld = glm::translate(glm::mat4(1.f), glm::vec3(-0.60f, -0.60f, 0.f)) *
			glm::scale(glm::mat4(1.f), glm::vec3(0.4f, 0.4f, 0.4f));

		shaderManager->SetParameters(tempWorld, glm::mat4(), glm::mat4());

		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, drRendering.getShadowMap());
		glUniform1i(glGetUniformLocation(shaderManager->getShader(), "texture"), 0);

		glDisable(GL_DEPTH_TEST);
		drRendering.getFinalRenderQuad()->Draw();
		glEnable(GL_DEPTH_TEST);
	}*/
}

void ScreenGame::UpdatePaused(GLint deltaT)
{
	// Updating Buttons
	guiManager->Update(deltaT);

	for (std::pair<Button*, GUIManager::Action> button : *guiManager->getButtonList())
	{
		if (button.first->getPressed())
		{
			switch (button.second)
			{
			case GUIManager::Action::OK:  gameState = UNPAUSING; break;
			case GUIManager::Action::STARTMENY: *state = State::StartMeny; break;
			case GUIManager::Action::EXIT: *state = State::Exit; break;
			}
			button.first->setPressed(false);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
		gameState = UNPAUSING;
}

void ScreenGame::UpdatePlaying(GLint deltaT)
{
	// Check if user is pausing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
		gameState = PAUSING;

	// Temporary for testing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U))
		particleManager->EffectExplosionLights(levelManager->getPlayer()->getPosition(), 10, glm::vec4(randBetweenF(0.1f, 0.25f), randBetweenF(0.80f, 1.f), randBetweenF(0.60f, 1.f), randBetweenF(0.80f, 1)));

	// Updating particles effects
	particleManager->Update(deltaT);

	// Updating map objects
	levelManager->Update(deltaT);

	// Moving the camera to follow player object
	camera->smoothToPosition(glm::vec3(levelManager->getPlayer()->getPosition().x, levelManager->getPlayer()->getPosition().y, camera->getPosition().z));

	// Building a new camera view matrix
	camera->buildViewMatrix();
}

void ScreenGame::UpdatePausing(GLint deltaT)
{
	static GLint pausTimer = 0.f;
	pausTimer += deltaT;
	guiManager->setAlpha(pausTimer / PAUS_TIMER);
	if (pausTimer >= PAUS_TIMER)
	{
		pausTimer = 0.f;
		gameState = PAUSED;
	}
}

void ScreenGame::UpdateUnpausing(GLint deltaT)
{
	static GLint unpausTimer = PAUS_TIMER;
	unpausTimer -= deltaT;
	guiManager->setAlpha(unpausTimer / PAUS_TIMER);
	if (unpausTimer <= NULL)
	{
		unpausTimer = PAUS_TIMER;
		gameState = PLAYING;
	}
}

void ScreenGame::Stop()
{
	// Deleting material manager
	if (materialManager != nullptr)
	{
		materialManager->Clear();
		delete materialManager;
		materialManager = nullptr;
	}

	// Deleting particles
	if (particleManager != nullptr)
	{
		particleManager->Stop();
		delete particleManager;
		particleManager = nullptr;
	}

	// Deleting shaders
	if (shaderManager != nullptr)
	{
		shaderManager->Stop();
		delete shaderManager;
		shaderManager = nullptr;
	}

	// Deleting map
	if (levelManager != nullptr)
	{
		levelManager->Stop();
		delete levelManager;
		levelManager = nullptr;
	}

	// Deleting gui
	if (guiManager != nullptr)
	{
		guiManager->Stop();
		delete guiManager;
		guiManager = nullptr;
	}

	drRendering.Stop();

	// Removes Camera & openGL ptr
	Screen::Stop();
}