#include "ScreenGame.h"

MeshManager* meshManager;			//< The mesh manager
MaterialManager* materialManager;	//< The material manager
ParticleManager* particleManager;	//< Manager for particle effects
ShaderManager* shaderManager;		//< Manager for shaderprograms

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

bool ScreenGame::Start(SDL_Window* window, glm::vec2 screenSize, glm::vec2 screenPosition, State* state, SoundManager* soundManager)
{
	// Starting Camera & getting openGL pointer
	Screen::Start(window, screenSize, screenPosition, state, soundManager);

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
	shaderManager->AddShader("particle_cube", SHADER_PATH "particle_cube_vs.glsl", SHADER_PATH "particle_cube_gs.glsl", SHADER_PATH "particle_cube_fs.glsl");
	shaderManager->AddShader("particle_lines", SHADER_PATH "particle_lines_vs.glsl", SHADER_PATH "particle_lines_gs.glsl", SHADER_PATH "particle_lines_fs.glsl");
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
	materialManager->AddMaterial("missingmaterial", glm::vec3(1.f), glm::vec3(1.f), glm::vec3(1.f), 1.f, "missingtexture", TEXTURE_PATH "MissingTexture.png");
	materialManager->AddMaterial("GUI_1_mat", glm::vec3(0.1f), glm::vec3(0.75, 0.75, 0.75), glm::vec3(1.f), 1.f, "GUI_1_tex", TEXTURE_PATH "GUI_btn_1.png");
	materialManager->AddMaterial("GUI_bar_blue", glm::vec3(0.1f), glm::vec3(0.4, 0.4, 0.7), glm::vec3(1.f), 1.f, "GUI_2_tex", TEXTURE_PATH "GUI_bar_1.jpg");
	materialManager->AddMaterial("GUI_bar_red", glm::vec3(0.1f), glm::vec3(0.8, 0.2, 0.2), glm::vec3(1.f), 1.f, "GUI_2_tex", TEXTURE_PATH "GUI_bar_1.png");
	materialManager->AddMaterial("GUI_bar_green", glm::vec3(0.1f), glm::vec3(0.2, 1.f, 0.2), glm::vec3(1.f), 1.f, "GUI_2_tex", TEXTURE_PATH "GUI_bar_1.png");
	materialManager->AddMaterial("GUI_bar_white", glm::vec3(0.1f), glm::vec3(0.8, 0.8, 0.8), glm::vec3(1.f), 1.f, "GUI_2_tex", TEXTURE_PATH "GUI_bar_1.png");
	materialManager->AddMaterial("playermaterial", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(0.10f), 0.01f, "playertexture", TEXTURE_PATH "Walk01.png");
	materialManager->AddMaterial("skatermaterial", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(0.10f), 0.01f, "skatertexture", TEXTURE_PATH "skater_L.png");
	materialManager->AddMaterial("zombie1material", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(0.10f), 0.01f, "zombie1walk", TEXTURE_PATH "Zombie1Walk.png");
	materialManager->AddMaterial("zombieheadmaterial", glm::vec3(0.25f), glm::vec3(0.5f), glm::vec3(0.f), 0.01f, "zombieheadtexture", TEXTURE_PATH "zombie_head.png");
	materialManager->AddMaterial("zombiehandmaterial", glm::vec3(0.25f), glm::vec3(0.5f), glm::vec3(0.f), 0.01f, "zombiehandtexture", TEXTURE_PATH "zombie_hand.png");
	materialManager->AddMaterial("zombiefootmaterial", glm::vec3(0.25f), glm::vec3(0.5f), glm::vec3(0.f), 0.01f, "zombiefoottexture", TEXTURE_PATH "zombie_foot.png");
	materialManager->AddMaterial("zombiebodymaterial", glm::vec3(0.25f), glm::vec3(0.5f), glm::vec3(0.f), 0.01f, "zombiebodytexture", TEXTURE_PATH "zombie_body.png");
	materialManager->AddMaterial("lightmaterial", glm::vec3(1.f), glm::vec3(1.f), glm::vec3(0.f), 0.01f, "lighttexture", TEXTURE_PATH "gammal-dammsugare.jpg");
	materialManager->AddMaterial("groundmaterial", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(0.f), 0.01f, "groundtexture", TEXTURE_PATH "temp_ground.jpg");
	materialManager->AddMaterial("backgroundmaterial", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(0.f), 0.01f, "backgroundtexture", TEXTURE_PATH "temp_background.jpg");
	materialManager->AddMaterial("smokematerial", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 1.f, "smoketexture", TEXTURE_PATH "smoke.png");
	materialManager->AddMaterial("bloodmaterial", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 1.f, "bloodtexture", TEXTURE_PATH "blood.png");
	materialManager->AddMaterial("firematerial", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 1.f, "firetexture", TEXTURE_PATH "fire.png");
	materialManager->AddMaterial("boltmaterial", glm::vec3(0.1f), glm::vec3(1.f), glm::vec3(1.f), 1.f, "bolttexture", TEXTURE_PATH "bolt.jpg");
	materialManager->AddMaterial("boxmaterial", glm::vec3(0.1f), glm::vec3(0.7f), glm::vec3(1.f), 1.f, "boxtexture", TEXTURE_PATH "box.jpg");
	materialManager->AddMaterial("garbagematerial", glm::vec3(0.2f), glm::vec3(0.5f), glm::vec3(1.f), 1.f, "garbagetexture", TEXTURE_PATH "garbage.png");
	for (int i = 1; i < 11; i++) materialManager->AddMaterial("postermaterial_" + std::to_string(i), glm::vec3(1.f), glm::vec3(1.f), glm::vec3(1.f), 1.f, "poster_" + std::to_string(i), (POSTER_PATH "poster_" + std::to_string(i) + ".jpg"));
	if (materialManager->getMaterial("GUI_1_mat") == nullptr) printf("Button Material not found\n");
	if (materialManager->getMaterial("GUI_bar_blue") == nullptr) printf("Button Material not found\n");
	if (materialManager->getMaterial("GUI_bar_red") == nullptr) printf("Button Material not found\n");
	if (materialManager->getMaterial("GUI_bar_white") == nullptr) printf("Button Material not found\n");
	if (materialManager->getMaterial("playermaterial") == nullptr) printf("Player Material not found\n");
	if (materialManager->getMaterial("lightmaterial") == nullptr) printf("Light Material not found\n");
	if (materialManager->getMaterial("groundmaterial") == nullptr) printf("Ground Material not found\n");
	if (materialManager->getMaterial("backgroundmaterial") == nullptr) printf("Background Material not found\n");
	if (materialManager->getMaterial("smokematerial") == nullptr) printf("Smoke Material not found\n");
	if (materialManager->getMaterial("boltmaterial") == nullptr) printf("Bolt Material not found\n");
	if (materialManager->getMaterial("boxmaterial") == nullptr) printf("Box Material not found\n");

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
	particleManager->ShaderPair(shaderManager->getShader("particle_cube"), ParticleType::NUTSBOLTS);
	particleManager->ShaderPair(shaderManager->getShader("particle_lines"), ParticleType::MUSIC);
	particleManager->setDefaultTextures(materialManager->getTextureID("smoketexture"), materialManager->getTextureID("bloodtexture"));

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
	guiManager->AddButton(GUIManager::STARTMENY, glm::vec3(0, 0.f, 0), glm::vec2(0.225f, 0.05955), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quadbig"), "Menu", FONT_PATH INGAME_FONT, 28.f, glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
	guiManager->AddButton(GUIManager::OK, glm::vec3(0, 0.20f, 0), glm::vec2(0.225f, 0.05955), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quadbig"), "Back", FONT_PATH INGAME_FONT, 28.f, glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
	guiManager->AddButton(GUIManager::EXIT, glm::vec3(0, -0.20f, 0), glm::vec2(0.225f, 0.05955), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quadbig"), "Exit to Desktop", FONT_PATH INGAME_FONT, 28.f, glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
	guiManager->AddText(glm::vec3(0.f, 0.70f, 0.f), 80.f, "Paused", FONT_PATH INGAME_FONT);
	guiManager->setAlpha(1.f);
	guiManager->setShader(shaderManager->getShader("texture"));
	guiManager->setInstantCenter(glm::vec2(0, 2));

	////////////////////////////////////////////////////////////
	// Level Manager
	////////////////////////////////////////////////////////////
	levelManager = new LevelManager();
	if (levelManager == nullptr) return false;
	if (!levelManager->Start(screenSize, screenPosition, shaderManager->getShader("texture_animation_normal"), shaderManager->getShader("deferred"), shaderManager->getShader("texture"), materialManager, meshManager, particleManager, soundManager, camera))
		return false;

	SetupUI();

	background = new Button();
	background->Start(screenSize, glm::vec3(0.f, 0.f, 0.f), glm::vec2(1), materialManager->getMaterial("backgroundmaterial"), meshManager->getMesh("quadbig"));
	background->setShader(shaderManager->getShader("texture"));

	// Setting startvariables
	SetStartVariables(FIRST_LEVELFILE, FIRST_ARCHIVEFILE);

	return true;
}

void ScreenGame::SetStartVariables(std::string levelPath, std::string archivePath)
{
	// Setting game state
	gameState = PLAYING;

	// Backing the camera a little bit backwards
	camera->setPosition(glm::vec3(0, 0, 16.0f));

	// Making wall & floor bigger
	levelManager->LoadLevel(LEVEL_PATH + levelPath, ARCHIVE_PATH + archivePath);

	// Adding shadow
	// flyttade upp till start functionen
	if (levelManager->getLightManager()->getDirectionalLightList().size() > 0)
	{
		shadowManager.AddDirectional(levelManager->getLightManager()->getDirectionalLightList()[0], glm::vec3(5.f, 5.f, -10.f), glm::vec2(screenSize.x * 4.f, screenSize.y * 4.f), glm::vec2(60, 30), 5.f, 40);
		//shadowManager.getDirectionalShadowMapList()[0]->UpdateLightSpace(glm::vec3(0.f, 40.f, 30.f), glm::vec2(100.f, 50.f), 1.f, 100.f);
		//shadowManager.AddDirectional(levelManager->getLightManager()->getDirectionalLightList()[1], screenSize, glm::vec2(60, 30), -30.f, 50);
		//shadowManager.AddDirectional(levelManager->getLightManager()->getDirectionalLightList()[2], screenSize, glm::vec2(60, 30), -30.f, 50);
		//shadowManager.AddPoint(levelManager->getLightManager()->getPointLightList()[1], glm::vec2(256, 256), 45, 0.1f);
		shadowManager.setUseShadows(true);
	}
	
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

	// Drawing background
	DrawObjectGUI(background, shaderManager);

	// Disable Blend for DR
	glDisable(GL_BLEND);

	// Bind DR frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, drRendering.getDRFBO());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Player* player = levelManager->getPlayer();

	float playerX = player->getPosition().x;

	// Drawing map
	for (Object* object : levelManager->getMap())
			DrawObjectGeometryPass(object, shaderManager);

	// Drawing movable entities
	for (Entity* entity : *levelManager->getEntityManager()->getEntityList())
		if (abs(entity->getPosition().x - playerX) < 35.f)
			DrawObjectGeometryPass(entity, shaderManager);

	////TEST
	//for(Projectile* proj : levelManager->getProj())
	//	DrawObjectGeometryPass(proj, shaderManager);

	for (Projectile* projectiles : *levelManager->getProjectiles())
		if (abs(projectiles->getPosition().x - playerX) < 35.f)
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

	// DR: Light pass
	DrawObjectLightPass(&drRendering, shaderManager, levelManager->getLightManager()->getPointLightList(), levelManager->getLightManager()->getDirectionalLightList(), shadowManager.getDirectionalShadowMapList(), shadowManager.getPointShadowMapList(), shadowManager.getUseShadows());

	// Bind lights and shadowmaps for all animated objects
	GLint textureCounter = bindLightsShadowsAnimation(player->getShader(), shaderManager, levelManager->getLightManager()->getPointLightList(), levelManager->getLightManager()->getDirectionalLightList(), shadowManager.getDirectionalShadowMapList(), shadowManager.getPointShadowMapList(), shadowManager.getUseShadows());

	// Drawing player
	if (!player->getIsDead())
	{
		if (player->getInvulTime() > 0.f)
		{
			if ((int)(player->getInvulTime() * 10.f) % 2 == 0)
				DrawObjectAnimation(player, shaderManager, textureCounter);
		}
		else
			DrawObjectAnimation(player, shaderManager, textureCounter);
	}

	// Draw Enemies
	for (Enemy* enemy : *levelManager->getEntityManager()->getEnemyList())
		DrawObjectAnimation(enemy, shaderManager, textureCounter);

	// Drawing particles
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	for (ParticleEmitter* emitter : *particleManager->getEmitters())
		DrawParticles(emitter, shaderManager);
	glDisable(GL_BLEND);

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

	// Drawing popup
	DrawObjectGUI(levelManager->getPopup(), shaderManager);

	// Temp shadow map debug
/*	if (shadowManager.getUseShadows())
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
	} */
}

bool ScreenGame::SetupUI()
{
	if (levelManager == nullptr) return false;
	if (levelManager->getPlayer() == nullptr) return false;

	// STarting UI manager
	uiManager = new GUIManager();
	if (uiManager == nullptr) return false;
	if (!uiManager->Start(screenSize, screenPosition)) return false;
	uiManager->AddButton(GUIManager::PAUSE, glm::vec3(0.89f, -0.97, 0), glm::vec2(0.1125, 0.0297777778), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quadbig"), "Pause", FONT_PATH INGAME_FONT, 17.5f, glm::vec4(0.1f, 0.1f, 0.1f, 1.f));

	// Bars
	uiManager->AddBar(levelManager->getPlayer()->getHP(), levelManager->getPlayer()->getHP(), glm::vec3(-0.3f, -0.95, 0), glm::vec2(0.15, 0.05), materialManager->getMaterial("GUI_bar_red"), meshManager->getMesh("quadbig"));
	uiManager->AddBar(levelManager->getPlayer()->getPower(), levelManager->getPlayer()->getPower(), glm::vec3(0.3, -0.95, 0), glm::vec2(0.15, 0.05), materialManager->getMaterial("GUI_bar_green"), meshManager->getMesh("quadbig"));
	uiManager->AddBar((float&)(levelManager->getPlayer()->getNrOfProjectiles()), PLAYER_AMMO_CAP, glm::vec3(0.0, -0.95, 0), glm::vec2(0.15, 0.05), materialManager->getMaterial("GUI_bar_blue"), meshManager->getMesh("quadbig"));
	uiManager->AddText(glm::vec3(-0.3, -0.95, 0.f), 30.f, "Health", FONT_PATH INGAME_FONT);
	uiManager->AddText(glm::vec3(0.3, -0.95, 0.f), 30.f, "Power", FONT_PATH INGAME_FONT);
	uiManager->AddText(glm::vec3(0.0, -0.95, 0.f), 30.f, "Scrap", FONT_PATH INGAME_FONT);

	// Death Screen
	uiManager->AddText(glm::vec3(0.f, 2.5, 0.f), 50.f, "You died", FONT_PATH INGAME_FONT);
	uiManager->AddButton(GUIManager::PLAY, glm::vec3(0.0, 2.0f, 0), glm::vec2(0.225f, 0.05955), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quadbig"), "Try again", FONT_PATH INGAME_FONT, 28.f, glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
	uiManager->AddButton(GUIManager::STARTMENY, glm::vec3(0.0, 1.8f, 0), glm::vec2(0.225f, 0.05955), materialManager->getMaterial("GUI_1_mat"), meshManager->getMesh("quadbig"), "Meny", FONT_PATH INGAME_FONT, 28.f, glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
	uiManager->setAlpha(1.f);

	// Bar modifications
	uiManager->getBar(0)->setAlpha(1.f);
	uiManager->getBar(1)->setAlpha(1.f);
	uiManager->getBar(2)->setAlpha(1.f);

	uiManager->setShader(shaderManager->getShader("texture"));
	uiManager->setInstantCenter(glm::vec2(0, 0));

	return true;
}

bool ScreenGame::ResetLevel()
{
	// Saving next level paths
	std::string level = levelManager->getNextLevelPath();
	std::string archive = levelManager->getNextArchivePath();

	// Stopping level manager
	levelManager->Stop();
	delete levelManager;
	levelManager = nullptr;

	// Stopping ui
	if (uiManager != nullptr)
	{
		uiManager->Stop();
		delete uiManager;
		uiManager = nullptr;
	}

	// Removing current shadowmap
	shadowManager.Stop();

	// Restarting levelManager
	levelManager = new LevelManager();
	if (levelManager == nullptr) return false;
	if (!levelManager->Start(screenSize, screenPosition, shaderManager->getShader("texture_animation_normal"), shaderManager->getShader("deferred"), shaderManager->getShader("texture"), materialManager, meshManager, particleManager, soundManager, camera))
		return false;

	// Creating a new UI with new adresses
	if (!SetupUI()) 
		return false;

	SetStartVariables(level + ".anl", archive + ".ana");

	return true;
}

void ScreenGame::DrawShadowMaps()
{
	// Directional
	for (int i = 0; i < shadowManager.getDirectionalShadowMapList().size(); i++)
	{
		// Set Viewport to resolution of shadow map
		glViewport(0, 0, shadowManager.getDirectionalShadowMapList()[i]->resolution.x, shadowManager.getDirectionalShadowMapList()[i]->resolution.y);

		shadowManager.getDirectionalShadowMapList()[i]->UpdateLightSpace(camera->getPosition(), glm::vec2(106, 60), -10.f, 60.f);
		// Bind depth FBO
		glBindFramebuffer(GL_FRAMEBUFFER, shadowManager.getDirectionalShadowMapList()[i]->shadowFBO);

		// Set shader
		shaderManager->setShader(shadowManager.getDirectionalShadowShader());

		glClear(GL_DEPTH_BUFFER_BIT);

		glCullFace(GL_FRONT);
		
		float playerX = levelManager->getPlayer()->getPosition().x;

		// Drawing shadowmap
		for (Object* object : levelManager->getMap())
				DrawObjectDirShadowMap(object, shaderManager, shadowManager.getDirectionalShadowMapList()[i]->lightSpaceMatrix);
	
		glCullFace(GL_BACK);

		// Drawing movable entities
		for (Entity* entity : *levelManager->getEntityManager()->getEntityList())
			if (abs(entity->getPosition().x - playerX) < 35.f)
				DrawObjectDirShadowMap(entity, shaderManager, shadowManager.getDirectionalShadowMapList()[i]->lightSpaceMatrix);

		for (Projectile* projectiles : *levelManager->getProjectiles())
			if (abs(projectiles->getPosition().x - playerX) < 35.f)
				DrawObjectDirShadowMap(projectiles, shaderManager, shadowManager.getDirectionalShadowMapList()[i]->lightSpaceMatrix);

		// Set shader for transparent objects
		shaderManager->setShader(shadowManager.getDirectionalShadowShaderTr());

		if (!levelManager->getPlayer()->getIsDead())
			DrawObjectDirShadowMapTransparent(levelManager->getPlayer(), shaderManager, shadowManager.getDirectionalShadowMapList()[i]->lightSpaceMatrix);

		// DRawing enemies
		for (Enemy* enemy : *levelManager->getEntityManager()->getEnemyList())
			DrawObjectDirShadowMapTransparent(enemy, shaderManager, shadowManager.getDirectionalShadowMapList()[i]->lightSpaceMatrix);


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

		// Drawing movable entities
		for (Entity* entity : *levelManager->getEntityManager()->getEntityList())
			DrawObjectPointShadowMap(entity, shaderManager, shadowManager.getPointShadowMapList()[i]);

		for (Projectile* projectiles : *levelManager->getProjectiles())
			DrawObjectPointShadowMap(projectiles, shaderManager, shadowManager.getPointShadowMapList()[i]);


		// Set shader for transparent objects
		//shaderManager->setShader(shadowManager.getDirectionalShadowShaderTr());

		//DrawObjectDirShadowMapTransparent(levelManager->getPlayer(), shaderManager, shadowManager.getDirectionalShadowMapList()[i]->lightSpaceMatrix);
//		for (Enemy* enemy : *levelManager->getEntityManager()->getEnemyList())
//			DrawObjectDirShadowMapTransparent(enemy, shaderManager, shadowManager.getDirectionalShadowMapList()[i]->lightSpaceMatrix);


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
	camera->smoothToPausePosition(levelManager->getPlayer()->getPosition());
	camera->buildViewMatrix();

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
			soundManager->playSFXOverDrive(SoundManager::SFX::SFX_BTN, 50, 0.2f);
			switch (action)
			{
			case GUIManager::Action::OK:		Pause(); break;
			case GUIManager::Action::STARTMENY:	*state = State::StartMeny; break;
			case GUIManager::Action::EXIT:		*state = State::Exit; break;
			}
			btn->setPressed(false);
		}
	}

	// Unpause
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || sf::Joystick::isButtonPressed(0,6)) Pause();
}

void ScreenGame::UpdatePlaying(GLint deltaT)
{
	// Moving the camera to follow player object
	camera->smoothToPosition(glm::vec3(levelManager->getPlayer()->getPosition().x, levelManager->getPlayer()->getPosition().y, camera->getPosition().z));
	camera->Update(deltaT);

	if (!camera->getUnlocked())
	{
		// Updating particles effects
		particleManager->Update(deltaT, levelManager->getPlayer()->getPosition());

		// Updating map objects
		levelManager->Update(deltaT);

		// Updating UI presses
		uiManager->Update(deltaT);
		
		// Check if player is dead, if so, move ui
		if (levelManager->getPlayer()->getIsDead())
			uiManager->setCenter(glm::vec2(0, 2));
		else 
			uiManager->setCenter(glm::vec2(0, 0));
		
		std::vector<std::pair<Button*, GUIManager::Action>>* buttons = uiManager->getButtonList();
		for (int i = 0; i < buttons->size(); i++)
		{
			Button* btn = buttons[0][i].first;
			GUIManager::Action action = buttons[0][i].second;
			if (btn->getPressed())
			{
				soundManager->playModifiedSFX(SoundManager::SFX::SFX_BTN, 50, 0.2f);
				switch (action)
				{
				case GUIManager::Action::PAUSE: Pause(); break;
				case GUIManager::Action::PLAY:
					uiManager->setCenter(glm::vec2(0, 0));
					levelManager->getPlayer()->Reset();
					break;
				case GUIManager::STARTMENY: *state = State::StartMeny;
					break;
				}
				btn->setPressed(false);
			}
		}
		std::vector<Bar*>* bars = uiManager->getBarList();
		for (int i = 0; i < bars->size(); i++)
			bars[0][i]->Update(deltaT);

		// Check if user is pausing

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) || sf::Joystick::isButtonPressed(0, 6)) Pause();

		// If we have finished the level or not
		if (levelManager->getNextLevelTrigger())
		{
			if (!ResetLevel())
				printf("Error in opeing next map");
			else
				printf("Next level loaded");
		}
	}
	else
	{
		uiManager->setInstantCenter(glm::vec2(0, 5));
	}
}

void ScreenGame::UpdatePausing(GLint deltaT)
{
	camera->smoothToPausePosition(levelManager->getPlayer()->getPosition());
	camera->buildViewMatrix();

	static GLint pausTimer = 0.f;
	pausTimer += deltaT;
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
	camera->smoothToPosition(levelManager->getPlayer()->getPosition());
	camera->buildViewMatrix();

	static GLint unpausTimer = PAUS_TIMER;
	unpausTimer -= deltaT;
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

	levelManager->getPlayer()->UpdateScreenProperties(screenSize, screenPos);
	//levelManager->getPH()->UpdateScreenProperties(screenSize, screenPos);
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

	if (background != nullptr)
	{
		background->Stop();
		delete background;
		background = nullptr;
	}

	// Stoping Deferred rendering
	drRendering.Stop();

	// Stoping Shadowmaps
	shadowManager.Stop();

	// Removes Camera & openGL ptr
	Screen::Stop();
}