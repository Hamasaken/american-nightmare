#include "ScreenGame.h"

ScreenGame::ScreenGame() : Screen()
{
	particleManager = nullptr;
	shaderManager = nullptr;
	levelManager = nullptr;
}

ScreenGame::ScreenGame(const ScreenGame& other) { }

ScreenGame::~ScreenGame() { }

bool ScreenGame::Start(glm::vec2 screenSize, SoundManager* soundManager)
{
	// Starting Camera & getting openGL pointer
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
	shaderManager->AddShader("texture_animation", shaderPath + "texture_animation_vs.glsl", shaderPath + "texture_fs.glsl");
	shaderManager->AddShader("texture_animation_normal", shaderPath + "texture_animation_vs.glsl", shaderPath + "texture_animation_fs.glsl");
	shaderManager->AddShader("particle", shaderPath + "particle_vs.glsl", shaderPath + "particle_gs.glsl", shaderPath + "particle_fs.glsl");
	shaderManager->AddShader("particle_light", shaderPath + "particle_light_vs.glsl", shaderPath + "particle_light_gs.glsl", shaderPath + "particle_light_fs.glsl");
	shaderManager->AddShader("deferred", shaderPath + "dr_vs.glsl", shaderPath + "dr_fs.glsl");
	shaderManager->AddShader("deferred_final", shaderPath + "drfinal_vs.glsl", shaderPath + "drfinal_fs.glsl");

	// Initialize Deferred Rendering
	drRendering.Start(screenSize, shaderManager->getShader("deferred_final"));

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
	if (!levelManager->Start(shaderManager->getShader("texture_animation_normal")))
		return false;

	// Setting startvariables
	SetStartVariables();

	return true;
}

void ScreenGame::SetStartVariables()
{
	// Backing the camera a little bit backwards
	camera->setPosition(glm::vec3(0, 0, 15));

	// Making wall & floor bigger
	levelManager->LoadLevel(shaderManager->getShader("deferred"), "0.lvl");
}

void ScreenGame::Update(GLint deltaT)
{
	// Temporary for testing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U))
		particleManager->Effect(ParticleEmitter::TRIANGLE, levelManager->getPlayer()->getPosition(), glm::vec4(randBetweenF(0, 1), randBetweenF(0, 1), randBetweenF(0, 1), randBetweenF(0, 1)), 100);

	// Updating particles effects
	particleManager->Update(deltaT);

	// Updating map objects
	levelManager->Update(deltaT);

	// Moving the camera to follow player object
	camera->smoothToPosition(glm::vec3(levelManager->getPlayer()->getPosition().x, levelManager->getPlayer()->getPosition().y, camera->getPosition().z));

	// Building a new camera view matrix
	camera->buildViewMatrix();
}

void ScreenGame::Draw()
{
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
	DrawObject(levelManager->getProjectile(), shaderManager);


	// Transfer deferred rendering depth buffer to forward rendering
	glBindFramebuffer(GL_READ_FRAMEBUFFER, drRendering.getDRFBO());
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, screenSize.x, screenSize.y, 0, 0, screenSize.x, screenSize.y, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	// Unbind DR frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Reenable Blend
	glEnable(GL_BLEND);

	// DR: Light pass
	for (LightManager::PointLight* light : levelManager->getLightManager()->getPointLightList())
		DrawObjectLightPass(&drRendering, shaderManager, light);


	// Drawing player
	for (LightManager::PointLight* light : levelManager->getLightManager()->getPointLightList())
		DrawObjectAnimation(levelManager->getPlayer(), shaderManager, light);
	//DrawObjectAnimation(player, shaderManager, levelManager->getLightManager()->getPointLightList()[0]);


	// Draw Enemy
	for (LightManager::PointLight* light : levelManager->getLightManager()->getPointLightList())
		DrawObjectAnimation(levelManager->getEnemy(), shaderManager, light);

	// Drawing vertices
	shaderManager->setShader(particleManager->getShader());
	shaderManager->SetParameters(worldMatrix, camera->getViewMatrix(), projectionMatrix);
	particleManager->Draw();
}

void ScreenGame::Stop()
{
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

	// Removes Camera & openGL ptr
	Screen::Stop();
}