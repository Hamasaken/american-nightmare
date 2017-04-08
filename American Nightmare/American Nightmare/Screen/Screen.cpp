#include "Screen.h"

Screen::Screen() 
{	
	// Setting ptr's to nullptr
	camera = nullptr;
	openGL = nullptr;
}

Screen::Screen(const Screen & other) { }

Screen::~Screen() { }

bool Screen::Restart()
{
	// Saving pointer to openGL
	OpenGL* ptr = openGL;

	// Unload everything
	Stop();

	// Trying to restart
	if (!Start(ptr))
		return false;

	return true;
}

bool Screen::Start(OpenGL* openGL)
{
	// Saving OpenGL ptr
	this->openGL = openGL;

	// Creating Camera Object
	camera = new Camera();
	if (camera == nullptr) return false;

	return true;
}

void Screen::DrawObject(Object* object, ShaderManager* shaderManager)
{
	// Getting matrices
	glm::mat4 world = openGL->getWorldMatrix();
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 projection = openGL->getProjectionMatrix();

	// Positioning object
	glm::vec3 pos = object->getPosition();
	world = glm::translate(world, pos);

	// Rotating object
	glm::vec3 rot = object->getRotationInRadians();
	world = glm::rotate(world, rot.x, glm::vec3(0, 0, 1));
	world = glm::rotate(world, rot.y, glm::vec3(1, 0, 0));
	world = glm::rotate(world, rot.z, glm::vec3(0, 1, 0));

	// Scaling object
	glm::vec3 scale = object->getScale();
	world = glm::scale(world, scale);

	// Setting shader as active and setting parameters
	shaderManager->SetShader(openGL, object->getShader());
	shaderManager->SetParameters(openGL, world, view, projection);

	// Drawing object
	object->Draw();
}

void Screen::Stop()
{
	// Deleting camera
	if (camera != nullptr)
	{
		delete camera;
		camera = nullptr;
	}

	// Removing our openGL ptr
	openGL = nullptr;
}
