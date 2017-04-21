#include "ScreenGame.h"

ScreenGame::ScreenGame() : Screen()
{
	particleManager = nullptr;
	shaderManager = nullptr;
	levelManager = nullptr;
	player = nullptr;
}

ScreenGame::ScreenGame(const ScreenGame& other) { }

ScreenGame::~ScreenGame() { }

bool ScreenGame::Start(glm::vec2 screenSize)
{
	// Starting Camera & getting openGL pointer
	Screen::Start(screenSize);

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
	shaderManager->AddShader("particle", shaderPath + "particle_vs.glsl", shaderPath + "particle_gs.glsl", shaderPath + "particle_fs.glsl");

	////////////////////////////////////////////////////////////
	// Creating Particle Manager
	////////////////////////////////////////////////////////////
	particleManager = new ParticleManager();
	if (particleManager == nullptr) return false;
	if (!particleManager->Start())
		return false;
	particleManager->setShader(shaderManager->getShader("particle"));

	////////////////////////////////////////////////////////////
	// Creating Models
	////////////////////////////////////////////////////////////
	std::string modelPath = MODEL_PATH;
	std::string texturePath = TEXTURE_PATH;
	std::string animationPath = ANIMATION_PATH;

	// Creating the player object
	player = new Player();
	if (player == nullptr) return false;
	if (!player->Start(modelPath + "model.m", texturePath + "testanimation.png"))
		return false;
	player->setShader(shaderManager->getShader("texture_animation"));
	player->AddAnimation(player->getTexture(), animationPath + "testanimation.txt");

	// Creating a simple level
	levelManager = new LevelManager();
	if (levelManager == nullptr) return false;
	if (!levelManager->Start())
		return false;

	// Setting startvariables
	SetStartVariables();

	return true;
}

void ScreenGame::SetStartVariables()
{
	// Backing the camera a little bit backwards
	camera->setPosition(glm::vec3(0, 0, 20));

	// Backing the player up a little to the screen
	player->setPosition(glm::vec3(0, 0, 18.f));

	// Making wall & floor bigger
	levelManager->LoadLevel(shaderManager->getShader("texture"), "0.lvl");
}

void ScreenGame::Update(GLint deltaT)
{
	// Temporary for testing
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U))
		particleManager->Effect(ParticleEmitter::TRIANGLE, player->getPosition(), glm::vec4(randBetweenF(0, 1), randBetweenF(0, 1), randBetweenF(0, 1), randBetweenF(0, 1)), 100);

	// Updating particles effects
	particleManager->Update(deltaT);
					 
	// Updating player
	player->Update(deltaT);

	// Updating map objects
	levelManager->Update(deltaT);

	// Moving the camera to follow player object
	camera->smoothToPosition(glm::vec3(player->getPosition().x, player->getPosition().y, camera->getPosition().z));

	// Building a new camera view matrix
	camera->buildViewMatrix();
}

void ScreenGame::Draw()
{
	// Drawing map
	for (Object* object : levelManager->getMap())
		DrawObject(object, shaderManager);

	// Drawing player
	DrawObject(player, shaderManager);

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

	// Deleting player
	if (player != nullptr)
	{
		player->Stop();
		delete player;
		player = nullptr;
	}

	// Removes Camera & openGL ptr
	Screen::Stop();
}