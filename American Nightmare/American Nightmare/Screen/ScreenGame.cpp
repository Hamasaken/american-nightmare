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
	shaderManager->AddShader("particle_light", shaderPath + "particle_light_vs.glsl", shaderPath + "particle_light_gs.glsl", shaderPath + "particle_light_fs.glsl");
	shaderManager->AddShader("deferred", shaderPath + "dr_vs.glsl", shaderPath + "dr_fs.glsl");
	shaderManager->AddShader("deferred_final", shaderPath + "drfinal_vs.glsl", shaderPath + "drfinal_fs.glsl");
	shaderManager->AddShader("shadow", shaderPath + "shadowmap_vs.glsl", shaderPath + "shadowmap_fs.glsl");
	shaderManager->AddShader("shadowtransparent", shaderPath + "shadowmap_transparent_vs.glsl", shaderPath + "shadowmap_transparent_fs.glsl");
	shaderManager->AddShader("debug", shaderPath + "debug_shader_vs.glsl", shaderPath + "debug_shader_fs.glsl");

	// Initialize Deferred Rendering
	drRendering.Start(screenSize, shaderManager->getShader("deferred_final"));

	// Initialize Shadow Manager
	shadowManager.Start(shaderManager->getShader("shadow"), shaderManager->getShader("shadowtransparent"));

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
	meshManager = new MeshManager();
	if (meshManager == nullptr) return false;
	
	// add quad mesh here later

	////////////////////////////////////////////////////////////
	// Level Manager
	////////////////////////////////////////////////////////////
	levelManager = new LevelManager();
	if (levelManager == nullptr) return false;
	if (!levelManager->Start(shaderManager->getShader("texture_animation_normal"), materialManager, meshManager, particleManager, soundManager))
		return false;

	////////////////////////////////////////////////////////////
	// Creating a GUI manager	
	////////////////////////////////////////////////////////////
	guiManager = new GUIManager();
	if (guiManager == nullptr) return false;
	if (!guiManager->Start(screenSize, screenPosition)) return false;
	guiManager->setShader(shaderManager->getShader("texture"));
	guiManager->AddButton(GUIManager::STARTMENY, glm::vec3(0, -0.25f, 0), glm::vec2(0.4f, 0.15f), materialManager->getMaterial("lightmaterial"), nullptr);
	guiManager->AddButton(GUIManager::OK, glm::vec3(0, 0.25f, 0), glm::vec2(0.4f, 0.15f), materialManager->getMaterial("lightmaterial"), nullptr);
	guiManager->AddButton(GUIManager::EXIT, glm::vec3(0, -0.75f, 0), glm::vec2(0.4f, 0.15f), materialManager->getMaterial("lightmaterial"), nullptr);
	guiManager->AddText(glm::vec3(0.f, 0.75f, 0.f), 70.f, "Paused", "framd.ttf");
	guiManager->setAlpha(0.f);

	////////////////////////////////////////////////////////////
	// Creating a UI manager	
	////////////////////////////////////////////////////////////
	uiManager = new GUIManager();
	if (uiManager == nullptr) return false;
	if (!uiManager->Start(screenSize, screenPosition)) return false;
	uiManager->setShader(shaderManager->getShader("texture"));
	uiManager->AddButton(GUIManager::OK, glm::vec3(0, -0.95, 0), glm::vec2(0.15f, 0.05f), materialManager->getMaterial("groundmaterial"), nullptr);
	uiManager->AddButton(GUIManager::PAUSE, glm::vec3(0.95f, -0.95, 0), glm::vec2(0.05f, 0.05f), materialManager->getMaterial("backgroundmaterial"), nullptr);
	uiManager->setAlpha(1.f);

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
	levelManager->LoadLevel(shaderManager->getShader("deferred"), LEVEL_PATH "lvl_1.anl", ARCHIVE_PATH "lvl_1.ana");

	// Adding shadow
	shadowManager.AddDirectional(levelManager->getLightManager()->getDirectionalLightList()[0], screenSize, 50, -30.f, 50);
	shadowManager.setUseShadows(false);
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
	// Draw shadow maps
	if (shadowManager.getUseShadows())
		DrawShadowMaps();		

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
	DrawObjectLightPass(&drRendering, shaderManager, levelManager->getLightManager()->getPointLightList(), levelManager->getLightManager()->getDirectionalLightList(), shadowManager.getDirectionalShadowMapList()[0]->lightSpaceMatrix, shadowManager.getDirectionalShadowMapList()[0]->lightDirection, shadowManager.getDirectionalShadowMapList()[0]->shadowMap, shadowManager.getUseShadows());

	// Drawing player
	DrawObjectAnimation(levelManager->getPlayer(), shaderManager, levelManager->getLightManager()->getPointLightList(), levelManager->getLightManager()->getDirectionalLightList(), shadowManager.getDirectionalShadowMapList()[0]->lightSpaceMatrix, shadowManager.getDirectionalShadowMapList()[0]->lightDirection, shadowManager.getDirectionalShadowMapList()[0]->shadowMap, shadowManager.getUseShadows());

	// Draw Enemy
	DrawObjectAnimation(levelManager->getEnemy(), shaderManager, levelManager->getLightManager()->getPointLightList(), levelManager->getLightManager()->getDirectionalLightList(), shadowManager.getDirectionalShadowMapList()[0]->lightSpaceMatrix, shadowManager.getDirectionalShadowMapList()[0]->lightDirection, shadowManager.getDirectionalShadowMapList()[0]->shadowMap, shadowManager.getUseShadows());

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
	else
	{
		for (std::pair<Button*, GUIManager::Action> button : *uiManager->getButtonList())
			DrawObjectGUI(button.first, shaderManager);
		for (Text* object : *uiManager->getTextList())
			DrawObjectGUI(object, shaderManager);
	}

	// Temp shadow map debug
	/*if (shadowManager.getUseShadows())
	{
		shaderManager->setShader("debug");

		glm::mat4 tempWorld = glm::translate(glm::mat4(1.f), glm::vec3(-0.60f, -0.60f, 0.f)) *
			glm::scale(glm::mat4(1.f), glm::vec3(0.4f, 0.4f, 0.4f));

		shaderManager->SetParameters(tempWorld, glm::mat4(), glm::mat4());

		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, shadowManager.getDirectionalShadowMapList()[0]->shadowMap);
		glUniform1i(glGetUniformLocation(shaderManager->getShader(), "texture"), 0);

		glDisable(GL_DEPTH_TEST);
		drRendering.getFinalRenderQuad()->Draw();
		glEnable(GL_DEPTH_TEST);
	}*/
}

void ScreenGame::DrawShadowMaps()
{
	for (int i = 0; i < shadowManager.getDirectionalShadowMapList().size(); i++)
	{
		// Set Viewport to resolution of shadow map
		glViewport(0, 0, shadowManager.getDirectionalShadowMapList()[i]->resolution.x, shadowManager.getDirectionalShadowMapList()[i]->resolution.y);
		// Bind depth FBO
		glBindFramebuffer(GL_FRAMEBUFFER, shadowManager.getDirectionalShadowMapList()[i]->shadowFBO);

		// Set shader
		shaderManager->setShader(shadowManager.getDirectionalShadowShader());

		glClear(GL_DEPTH_BUFFER_BIT);

		// Drawing shadowmap
		for (Object* object : levelManager->getMap())
			DrawObjectShadowMap(object, shaderManager, shadowManager.getDirectionalShadowMapList()[0]->lightSpaceMatrix);

		// Set shader for transparent objects
		shaderManager->setShader(shadowManager.getDirectionalShadowShaderTr());

		DrawObjectShadowMapTransparent(levelManager->getPlayer(), shaderManager, shadowManager.getDirectionalShadowMapList()[i]->lightSpaceMatrix);
		DrawObjectShadowMapTransparent(levelManager->getEnemy(), shaderManager, shadowManager.getDirectionalShadowMapList()[i]->lightSpaceMatrix);

		// Unbind FBO
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Reset Viewport to screen size
		glViewport(0, 0, screenSize.x, screenSize.y);
	}
	
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

	// Particle Managare Testing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U))
		particleManager->EffectExplosionLights(levelManager->getPlayer()->getPosition(), 10, glm::vec4(randBetweenF(0.1f, 0.25f), randBetweenF(0.80f, 1.f), randBetweenF(0.60f, 1.f), randBetweenF(0.80f, 1)));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
		particleManager->EffectTextureExplosion(levelManager->getPlayer()->getPosition(), materialManager->getMaterial("lightmaterial")->getTextureID(), 10, glm::vec4(randBetweenF(0.1f, 0.25f), randBetweenF(0.80f, 1.f), randBetweenF(0.60f, 1.f), randBetweenF(0.80f, 1)));

	// Updating particles effects
	particleManager->Update(deltaT);

	// Updating map objects
	levelManager->Update(deltaT);

	// Moving the camera to follow player object
	camera->smoothToPosition(glm::vec3(levelManager->getPlayer()->getPosition().x, levelManager->getPlayer()->getPosition().y, camera->getPosition().z));

	// Building a new camera view matrix
	camera->buildViewMatrix();

	// Updating UI presses
	uiManager->Update(deltaT);
	for (std::pair<Button*, GUIManager::Action> button : *uiManager->getButtonList())
	{
		if (button.first->getPressed())
		{
			switch (button.second)
			{ case GUIManager::Action::PAUSE:  gameState = PAUSING; break; }
			button.first->setPressed(false);
		}
	}
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

	// Deleting ui
	if (uiManager != nullptr)
	{
		uiManager->Stop();
		delete uiManager;
		uiManager = nullptr;
	}

	drRendering.Stop();

	// Removes Camera & openGL ptr
	Screen::Stop();
}