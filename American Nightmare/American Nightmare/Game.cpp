#include "Game.h"

Game::Game()
{
	m_openGL = nullptr;
	m_solidShader = nullptr;
	m_model = nullptr;
	m_camera = nullptr;
}

Game::Game(const Game& other) { }

Game::~Game() { }


bool Game::Start(OpenGL* openGL, HWND hwnd)
{
	m_openGL = openGL;

	////////////////////////////////////////////////////////////
	// Creating Camera
	////////////////////////////////////////////////////////////
	m_camera = new Camera();
	if (m_camera == nullptr) return false;

	////////////////////////////////////////////////////////////
	// Creating Models
	////////////////////////////////////////////////////////////
	m_model = new Model();
	if (m_model == nullptr) return false;
	if (!m_model->Start(openGL)) return false;

	////////////////////////////////////////////////////////////
	// Creating Shaders
	////////////////////////////////////////////////////////////
	std::string shaderPath = SHADER_PATH; 
	m_solidShader = new SolidShader();
	if (m_solidShader == nullptr) return false;
	m_solidShader->Start(openGL, hwnd, shaderPath + "solid_vs.glsl", shaderPath + "solid_fs.glsl");
	
	SetStartVariables();

	return true;
}

void Game::SetStartVariables()
{
	m_camera->setPosition(glm::vec3(0, 0, 10.f));
	m_camera->setRotation(glm::vec3(0, 0, 0));
}

void Game::Stop()
{
	// Deleting Camera
	if (m_camera != nullptr) 
	{
		delete m_camera;
		m_camera = nullptr;
	}

	// Deleting models
	if (m_model != nullptr) 
	{
		m_model->Stop(m_openGL);
		m_model = nullptr;
	}

	// Deleting shaders
	if (m_solidShader != nullptr) 
	{
		m_solidShader->Stop(m_openGL);
		m_solidShader = nullptr;
	}

	m_openGL = nullptr;
}

bool Game::Update()
{
	if (!Draw())
		return false;

	return true;
}

bool Game::Draw()
{
	// Starting draw section
	m_openGL->StartDraw(CLEAR_COLOR);

	m_camera->buildViewMatrix();

	glm::mat4 world = m_openGL->getWorldMatrix();
	glm::mat4 view = m_camera->getViewMatrix();
	glm::mat4 projection = m_openGL->getProjectionMatrix();

	m_solidShader->SetShader(m_openGL);
	m_solidShader->SetParameters(m_openGL, world, view, projection);

	m_model->Draw(m_openGL);

	// Ending Draw section
	m_openGL->EndDraw();

	return true;
}