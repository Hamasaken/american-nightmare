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
	shaderManager = new ShaderManager();
	if (shaderManager == nullptr) return false;

	// Adding Shader Programs
	shaderManager->AddShader("solid", SHADER_PATH "solid_vs.glsl", SHADER_PATH "solid_fs.glsl");
	shaderManager->AddShader("texture", SHADER_PATH "texture_vs.glsl", SHADER_PATH "texture_fs.glsl");
	shaderManager->AddShader("texture_animation", SHADER_PATH "texture_animation_vs.glsl", SHADER_PATH "texture_fs.glsl");
	shaderManager->AddShader("texture_animation_normal", SHADER_PATH "texture_animation_vs.glsl", SHADER_PATH "texture_animation_fs.glsl");
	shaderManager->AddShader("particle_light", SHADER_PATH "particle_light_vs.glsl", SHADER_PATH "particle_light_gs.glsl", SHADER_PATH "particle_light_fs.glsl");
	shaderManager->AddShader("particle_texture", SHADER_PATH "particle_texture_vs.glsl", SHADER_PATH "particle_texture_gs.glsl", SHADER_PATH "particle_texture_fs.glsl");
	shaderManager->AddShader("deferred", SHADER_PATH "dr_vs.glsl", SHADER_PATH "dr_fs.glsl");
	shaderManager->AddShader("deferred_final", SHADER_PATH "drfinal_vs.glsl", SHADER_PATH "drfinal_fs.glsl");
	shaderManager->AddShader("shadowdir", SHADER_PATH "shadowmap_dir_vs.glsl", SHADER_PATH "shadowmap_dir_fs.glsl");
	shaderManager->AddShader("shadowdirtransparent", SHADER_PATH "shadowmap_dir_transparent_vs.glsl", SHADER_PATH "shadowmap_dir_transparent_fs.glsl");
	shaderManager->AddShader("shadowpoint", SHADER_PATH "shadowmap_point_vs.glsl", SHADER_PATH "shadowmap_point_gs.glsl", SHADER_PATH "shadowmap_point_fs.glsl");
	shaderManager->AddShader("debug", SHADER_PATH "debug_shader_vs.glsl", SHADER_PATH "debug_shader_fs.glsl");

	// Initialize Deferred Rendering
	drRendering.Start(screenSize, shaderManager->getShader("deferred_final"));

	// Initialize Shadow Manager
	shadowManager.Start(shaderManager->getShader("shadowdir"), shaderManager->getShader("shadowdirtransparent"), shaderManager->getShader("shadowpoint"), 0);

	////////////////////////////////////////////////////////////
	// Creating Material Manager and loading textures/materials
	////////////////////////////////////////////////////////////
	materialManager = new MaterialManager();
	if (materialManager == nullptr) return false;

	// Loading materials
	materialManager->AddMaterial("GUI_1_mat", glm::vec3(0.1f), glm::vec3(0.5, 0.5, 0.5), glm::vec3(1.f), 1.f, "GUI_1_tex", TEXTURE_PATH "GUI_btn_1.png");
	materialManager->AddMaterial("GUI_bar_blue", glm::vec3(0.1f), glm::vec3(0.5, 0.5, 0.7), glm::vec3(1.f), 1.f, "GUI_2_tex", TEXTURE_PATH "GUI_bar_1.jpg");
	materialManager->AddMaterial("GUI_bar_red", glm::vec3(0.1f), glm::vec3(0.7, 0.5, 0.5), glm::vec3(1.f), 1.f, "GUI_2_tex", TEXTURE_PATH "GUI_bar_1.png");
	materialManager->AddMaterial("playermaterial", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(0.5f), 0.01f, "playertexture", TEXTURE_PATH "Walk01.png");
	materialManager->AddMaterial("lightmaterial", glm::vec3(1.f), glm::vec3(1.f), glm::vec3(0.f), 0.01f, "lighttexture", TEXTURE_PATH "gammal-dammsugare.jpg");
	materialManager->AddMaterial("groundmaterial", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(0.f), 0.01f, "groundtexture", TEXTURE_PATH "temp_ground.jpg");
	materialManager->AddMaterial("backgroundmaterial", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(0.f), 0.01f, "backgroundtexture", TEXTURE_PATH "temp_background.jpg");
	materialManager->AddMaterial("smokematerial", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 1.f, "smoketexture", TEXTURE_PATH "smoke.png");
	if (materialManager->getMaterial("GUI_1_mat") == nullptr) printf("Button Material not found\n");
	if (materialManager->getMaterial("GUI_2_mat") == nullptr) printf("Button Material not found\n");
	if (materialManager->getMaterial("playermaterial") == nullptr) printf("Player Material not found\n");
	if (materialManager->getMaterial("lightmaterial") == nullptr) printf("Light Material not found\n");
	if (materialManager->getMaterial("groundmaterial") == nullptr) printf("Ground Material not found\n");
	if (materialManager->getMaterial("backgroundmaterial") == nullptr) printf("Background Material not found\n");
	if (materialManager->getMaterial("smokematerial") == nullptr) printf("Smoke Material not found\n");

	////////////////////////////////////////////////////////////
	// Creating Particle Manager
	////////////////////////////////////////////////////////////
	particleManager = new ParticleManager();
	if (particleManager == nullptr) return false;
	particleManager->ShaderPair(shaderManager->getShader("particle_light"), ParticleType::LIGHT);
	particleManager->ShaderPair(shaderManager->getShader("particle_light"), ParticleType::LIGHT_DUST);
	particleManager->ShaderPair(shaderManager->getShader("particle_light"), ParticleType::BLOOD);
	particleManager->ShaderPair(shaderManager->getShader("particle_texture"), ParticleType::TEXTURE);
	particleManager->ShaderPair(shaderManager->getShader("particle_texture"), ParticleType::SMOKE);

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
	guiManager->AddButton(GUIManager::STARTMENY, glm::vec3(0, 0.f, 0), glm::vec2(0.225f, 0.05955), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quad"), "Meny", FONT_PATH INGAME_FONT, 28.f, glm::vec4(0.875f));
	guiManager->AddButton(GUIManager::OK, glm::vec3(0, 0.20f, 0), glm::vec2(0.225f, 0.05955), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quad"), "Back", FONT_PATH INGAME_FONT, 28.f, glm::vec4(0.875f));
	guiManager->AddButton(GUIManager::EXIT, glm::vec3(0, -0.20f, 0), glm::vec2(0.225f, 0.05955), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quad"), "Exit to Desktop", FONT_PATH INGAME_FONT, 28.f, glm::vec4(0.875f));
	guiManager->AddText(glm::vec3(0.f, 0.70f, 0.f), 80.f, "Paused", FONT_PATH INGAME_FONT);
	guiManager->setAlpha(0.f);
	guiManager->setShader(shaderManager->getShader("texture"));
	guiManager->setInstantCenter(glm::vec2(0, 2));

	////////////////////////////////////////////////////////////
	// Creating a UI manager	
	////////////////////////////////////////////////////////////
	uiManager = new GUIManager();
	if (uiManager == nullptr) return false;
	if (!uiManager->Start(screenSize, screenPosition)) return false;
	uiManager->AddButton(GUIManager::PAUSE, glm::vec3(0.89f, -0.97, 0), glm::vec2(0.1125, 0.0297777778), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quad"), "Pause", FONT_PATH INGAME_FONT, 17.5f, glm::vec4(0.875f));
	uiManager->AddBar(levelManager->getPlayer()->getHP(), levelManager->getPlayer()->getHP(), glm::vec3(-0.3, -0.96, 0), glm::vec2(0.45, 0.1191), materialManager->getMaterial("GUI_bar_red"), meshManager->getMesh("quad"));
	uiManager->AddBar(levelManager->getPlayer()->getPower(), levelManager->getPlayer()->getPower(), glm::vec3(0.3, -0.96, 0), glm::vec2(0.45, 0.1191), materialManager->getMaterial("GUI_bar_blue"), meshManager->getMesh("quad"));
	uiManager->AddText(glm::vec3(-0.3, -0.96, 0), 30.f, "Health", FONT_PATH INGAME_FONT);
	uiManager->AddText(glm::vec3(0.3, -0.96, 0), 30.f, "Power", FONT_PATH INGAME_FONT);
	uiManager->setAlpha(0.40f);
	uiManager->setShader(shaderManager->getShader("texture"));
	uiManager->setInstantCenter(glm::vec2(0, 0));

	// Setting startvariables
	SetStartVariables();

	return true;
}

void ScreenGame::SetStartVariables()
{
	// Setting game state
	gameState = PLAYING;

	// Backing the camera a little bit backwards
	camera->setPosition(glm::vec3(0, 0, 18.5f));

	// Making wall & floor bigger
	levelManager->LoadLevel(shaderManager->getShader("deferred"), LEVEL_PATH "Level2.anl", ARCHIVE_PATH "Assets2.ana");

	// Adding shadow
	shadowManager.AddDirectional(levelManager->getLightManager()->getDirectionalLightList()[0], glm::vec3(5.f, 5.f, -10.f), glm::vec2(screenSize.x * 0.5, screenSize.y * 0.5), glm::vec2(60, 30), 5.f, 40);
	//shadowManager.AddDirectional(levelManager->getLightManager()->getDirectionalLightList()[1], screenSize, glm::vec2(60, 30), -30.f, 50);
	//shadowManager.AddDirectional(levelManager->getLightManager()->getDirectionalLightList()[2], screenSize, glm::vec2(60, 30), -30.f, 50);
	//shadowManager.AddPoint(levelManager->getLightManager()->getPointLightList()[1], glm::vec2(256, 256), 45, 0.1f);
	shadowManager.setUseShadows(true);
}

void ScreenGame::Update(GLint deltaT)
{
	switch (gameState)
	{
	case GameState::PAUSING:	UpdatePausing(deltaT);		break;
	case GameState::PAUSED:		UpdatePaused(deltaT);		break;
	case GameState::PLAYING:	UpdatePlaying(deltaT);		break;
	case GameState::UNPAUSING:	UpdateUnpausing(deltaT);	break;
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

	////TEST
	//for(Projectile* proj : levelManager->getProj())
	//	DrawObjectGeometryPass(proj, shaderManager);

	for (Projectile* projectiles : levelManager->getProjectiles())
		DrawObjectGeometryPass(projectiles, shaderManager);
	//TEST
	//for(Projectile* proj : levelManager->getProj())
	//	DrawObjectGeometryPass(proj, shaderManager);

	//DrawObjectGeometryPass(levelManager->getPlayer()->getVac(), shaderManager);

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


	//DrawObjectAnimation(levelManager->getPlayer(), shaderManager, levelManager->getLightManager()->getPointLightList(), levelManager->getLightManager()->getDirectionalLightList(), shadowManager.getDirectionalShadowMapList(), shadowManager.getPointShadowMapList(), shadowManager.getUseShadows());

	// DR: Light pass
	DrawObjectLightPass(&drRendering, shaderManager, levelManager->getLightManager()->getPointLightList(), levelManager->getLightManager()->getDirectionalLightList(), shadowManager.getDirectionalShadowMapList(), shadowManager.getPointShadowMapList(), shadowManager.getUseShadows());

	// Drawing player
	DrawObjectAnimation(levelManager->getPlayer(), shaderManager, levelManager->getLightManager()->getPointLightList(), levelManager->getLightManager()->getDirectionalLightList(), shadowManager.getDirectionalShadowMapList(), shadowManager.getPointShadowMapList(), shadowManager.getUseShadows());

	// Draw Enemy
	DrawObjectAnimation(levelManager->getEnemy(), shaderManager, levelManager->getLightManager()->getPointLightList(), levelManager->getLightManager()->getDirectionalLightList(), shadowManager.getDirectionalShadowMapList(), shadowManager.getPointShadowMapList(), shadowManager.getUseShadows());

	// Drawing particles
	for (ParticleEmitter* emitter : *particleManager->getEmitters())
		DrawParticles(emitter, shaderManager);

	// Drawing gui Manager if we're paused
	if (gameState != PLAYING)
	{
		// Drawing the paus meny
		std::vector<std::pair<Button*, GUIManager::Action>>* buttons = guiManager->getButtonList();
		for (int i = 0; i < buttons->size(); i++)
		{
			DrawObjectGUI(buttons[0][i].first, shaderManager);
			if (buttons[0][i].first->getText()) DrawObjectGUI(buttons[0][i].first->getText(), shaderManager);
		}
		std::vector<Text*>* txts = guiManager->getTextList();
		for (int i = 0; i < txts->size(); i++)
			DrawObjectGUI(txts[0][i], shaderManager);
	}
	else
	{
		// Drawing the ingame-ui bars & buttons
		std::vector<std::pair<Button*, GUIManager::Action>>* buttons = uiManager->getButtonList();
		for (int i = 0; i < buttons->size(); i++)
		{
			DrawObjectGUI(buttons[0][i].first, shaderManager);
			if (buttons[0][i].first->getText()) DrawObjectGUI(buttons[0][i].first->getText(), shaderManager);
		}

		std::vector<Bar*>* bars = uiManager->getBarList();
		for (int i = 0; i < bars->size(); i++)
			DrawObjectGUI(bars[0][i], shaderManager);

		std::vector<Text*>* txts = uiManager->getTextList();
		for (int i = 0; i < txts->size(); i++)
			DrawObjectGUI(txts[0][i], shaderManager);
	}

	// Temp shadow map debug
	/*if (shadowManager.getUseShadows())
	{
		shaderManager->setShader("debug");

		glm::mat4 tempWorld = glm::translate(glm::mat4(1.f), glm::vec3(-0.75f, -0.75f, 0.f)) *
			glm::scale(glm::mat4(1.f), glm::vec3(0.25f, 0.25f, 0.25f));

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
	// Directional
	for (int i = 0; i < shadowManager.getDirectionalShadowMapList().size(); i++)
	{
		// Set Viewport to resolution of shadow map
		glViewport(0, 0, shadowManager.getDirectionalShadowMapList()[i]->resolution.x, shadowManager.getDirectionalShadowMapList()[i]->resolution.y);

		shadowManager.getDirectionalShadowMapList()[i]->UpdateLightSpace(camera->getPosition(), glm::vec2(20, 10), 1.f, 20.f);
		// Bind depth FBO
		glBindFramebuffer(GL_FRAMEBUFFER, shadowManager.getDirectionalShadowMapList()[i]->shadowFBO);

		// Set shader
		shaderManager->setShader(shadowManager.getDirectionalShadowShader());

		glClear(GL_DEPTH_BUFFER_BIT);

		glCullFace(GL_FRONT);
		// Drawing shadowmap
		for (Object* object : levelManager->getMap())
			DrawObjectDirShadowMap(object, shaderManager, shadowManager.getDirectionalShadowMapList()[i]->lightSpaceMatrix);
		glCullFace(GL_BACK);

		// Set shader for transparent objects
		shaderManager->setShader(shadowManager.getDirectionalShadowShaderTr());

		DrawObjectDirShadowMapTransparent(levelManager->getPlayer(), shaderManager, shadowManager.getDirectionalShadowMapList()[i]->lightSpaceMatrix);
		DrawObjectDirShadowMapTransparent(levelManager->getEnemy(), shaderManager, shadowManager.getDirectionalShadowMapList()[i]->lightSpaceMatrix);

		// Unbind FBO
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Reset Viewport to screen size
		glViewport(0, 0, screenSize.x, screenSize.y);
	}

	// Point
	for (int i = 0; i < shadowManager.getPointShadowMapList().size(); i++)
	{
		// Set Viewport to resolution of shadow map
		glViewport(0, 0, shadowManager.getPointShadowMapList()[i]->resolution.x, shadowManager.getPointShadowMapList()[i]->resolution.y);
		glDisable(GL_CULL_FACE);
		// Bind depth FBO
		glBindFramebuffer(GL_FRAMEBUFFER, shadowManager.getPointShadowMapList()[i]->shadowFBO);

		// Set shader
		shaderManager->setShader(shadowManager.getPointShadowShader());

		glClear(GL_DEPTH_BUFFER_BIT);

		// Drawing shadowmap
		for (Object* object : levelManager->getMap())
			DrawObjectPointShadowMap(object, shaderManager, shadowManager.getPointShadowMapList()[i]);

		// Set shader for transparent objects
		//shaderManager->setShader(shadowManager.getDirectionalShadowShaderTr());

		//DrawObjectDirShadowMapTransparent(levelManager->getPlayer(), shaderManager, shadowManager.getDirectionalShadowMapList()[i]->lightSpaceMatrix);
		//DrawObjectDirShadowMapTransparent(levelManager->getEnemy(), shaderManager, shadowManager.getDirectionalShadowMapList()[i]->lightSpaceMatrix);

		// Unbind FBO
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Reset Viewport to screen size
		glViewport(0, 0, screenSize.x, screenSize.y);
		glEnable(GL_CULL_FACE);
	}
	
}

void ScreenGame::Pause()
{
	// Play button press
	soundManager->playModifiedSFX(SoundManager::SFX::SFX_BTN, 50, 0.2f);
	
	if (gameState == PAUSED)
	{
		gameState = UNPAUSING;
		guiManager->setCenter(glm::vec2(0, 2));
		uiManager->setCenter(glm::vec2(0, 0));
	}
	if (gameState == PLAYING)
	{
		gameState = PAUSING;
		guiManager->setCenter(glm::vec2(0, 0));
		uiManager->setCenter(glm::vec2(0, 2));
	}
}

void ScreenGame::UpdatePaused(GLint deltaT)
{
	// Updating Buttons
	guiManager->Update(deltaT);
	uiManager->Update(deltaT);

	// Update button presses
	std::vector<std::pair<Button*, GUIManager::Action>>* buttons = guiManager->getButtonList();
	for (int i = 0; i < buttons->size(); i++)
	{
		Button* btn					= buttons[0][i].first;
		GUIManager::Action action	= buttons[0][i].second;
		if (btn->getPressed())
		{
			switch (action)
			{
			case GUIManager::Action::OK:		Pause(); break;
			case GUIManager::Action::STARTMENY: soundManager->playModifiedSFX(SoundManager::SFX::SFX_BTN, 50, 0.2f); *state = State::StartMeny; break;
			case GUIManager::Action::EXIT:		soundManager->playModifiedSFX(SoundManager::SFX::SFX_BTN, 50, 0.2f); *state = State::Exit; break;
			}
			btn->setPressed(false);
		}
	}

	// Unpause
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) Pause();
}

void ScreenGame::UpdatePlaying(GLint deltaT)
{
	// Particle Managare Testing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U))
		particleManager->EffectExplosionLights(levelManager->getPlayer()->getPosition(), 10, glm::vec4(randBetweenF(0.1f, 0.25f), randBetweenF(0.60f, 0.80f), randBetweenF(0.60f, 1.f), randBetweenF(0.80f, 1)));
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I))
		particleManager->EffectSmokeCloud(levelManager->getPlayer()->getPosition(), materialManager->getMaterial("smokematerial")->getTextureID(), 8);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
		particleManager->EffectConstantSmoke(levelManager->getPlayer()->getPosition(), materialManager->getMaterial("smokematerial")->getTextureID(), 5);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K))
		particleManager->EffectSmokeSignal(levelManager->getPlayer()->getPosition(), materialManager->getMaterial("smokematerial")->getTextureID(), 0);

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
	std::vector<std::pair<Button*, GUIManager::Action>>* buttons = uiManager->getButtonList();
	for (int i = 0; i < buttons->size(); i++)
	{
		Button* btn = buttons[0][i].first;
		GUIManager::Action action = buttons[0][i].second;
		if (btn->getPressed())
		{
			switch (action)
			{
			case GUIManager::Action::PAUSE: Pause();
				break; 
			}
			btn->setPressed(false);
		}
	}
	std::vector<Bar*>* bars = uiManager->getBarList();
	for (int i = 0; i < bars->size(); i++)
		bars[0][i]->Update(deltaT);

	// Check if user is pausing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) Pause();
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
	guiManager->Update(deltaT);
	uiManager->Update(deltaT);
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
	guiManager->Update(deltaT);
	uiManager->Update(deltaT);
}

void ScreenGame::UpdateScreenProperties(glm::vec2 screenSize, glm::vec2 screenPos)
{
	Screen::UpdateScreenProperties(screenSize, screenPos);

	// Updating guimanager
	guiManager->setScreenPosition(screenPos);
	guiManager->setScreenSize(screenSize);
	uiManager->setScreenPosition(screenPos);
	uiManager->setScreenSize(screenSize);
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

	if (meshManager != nullptr)
	{
		meshManager->Clear();
		delete meshManager;
		meshManager = nullptr;
	}

	// Stoping Deferred rendering
	drRendering.Stop();

	// Stoping Shadowmaps
	shadowManager.Stop();

	// Removes Camera & openGL ptr
	Screen::Stop();
}