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

bool ScreenGame::Start()
{
	// Starting Camera & getting openGL pointer
	Screen::Start();

	////////////////////////////////////////////////////////////
	// Creating Particle Manager
	////////////////////////////////////////////////////////////
	particleManager = new ParticleManager();
	if (particleManager == nullptr) return false;
	if (!particleManager->Start())
		return false;
	particleManager->Explosion(ParticleEmitter::PIXEL, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 1000);

	////////////////////////////////////////////////////////////
	// Creating Shader Manager
	////////////////////////////////////////////////////////////
	std::string shaderPath = SHADER_PATH;
	shaderManager = new ShaderManager();
	if (shaderManager == nullptr) return false;

	// Adding Shader Programs
	shaderManager->AddShader("solid", shaderPath + "solid_vs.glsl", shaderPath + "solid_fs.glsl");
	shaderManager->AddShader("texture", shaderPath + "texture_vs.glsl", shaderPath + "texture_fs.glsl");
	shaderManager->AddShader("particle", shaderPath + "particle_vs.glsl", shaderPath + "particle_gs.glsl", shaderPath + "particle_fs.glsl");

	////////////////////////////////////////////////////////////
	// Creating Models
	////////////////////////////////////////////////////////////
	std::string modelPath = MODEL_PATH;
	std::string texturePath = TEXTURE_PATH;

	// Creating the player object
	player = new Player();
	if (player == nullptr) return false;
	if (!player->Start(modelPath + "model.m", texturePath + "gammal-dammsugare.jpg"))
		return false;
	player->setShader(shaderManager->GetShader("texture"));

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
	camera->setPosition(glm::vec3(0, 0, 10));

	// Making wall & floor bigger
	levelManager->LoadLevel(shaderManager->GetShader("texture"), "0.lvl");
}

void ScreenGame::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::U))
		particleManager->Explosion(ParticleEmitter::PIXEL, player->getPosition(), glm::vec3((rand() % 1000) / 1000.f, (rand() % 1000) / 1000.f, (rand() % 1000) / 1000.f), 100);

	// Updating particles effects
	GLfloat delta = 0.1f;
	particleManager->Update(delta);
					 
	// Updating player
	player->Update();

	// Updating map objects
	levelManager->Update(delta);

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
	shaderManager->SetParameters(worldMatrix, camera->getViewMatrix(), projectionMatrix);
	shaderManager->SetShader("particle");
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