#include "Screen.h"

Screen::Screen() 
{	
	// Setting ptr's to nullptr
	camera = nullptr;
}

Screen::Screen(const Screen & other) { }

Screen::~Screen() { }

bool Screen::Restart()
{
	// Unload everything
	Stop();

	// Trying to restart
	if (!Start())
		return false;

	return true;
}

bool Screen::Start()
{
	// Building a world matrix (just identity matrix)
	worldMatrix = glm::mat4(1.f);

	// Building a projection matrix
	float fov = glm::pi<float>() / 0.40f;
	projectionMatrix = glm::perspective(fov, 1920.f / 1080.f, 0.1f, 50.f);

	// Creating Camera Object
	camera = new Camera();
	if (camera == nullptr) return false;

	return true;
}

void Screen::DrawObject(Object* object, ShaderManager* shaderManager)
{
	// Getting matrices
	glm::mat4 world = worldMatrix;
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 projection = projectionMatrix;

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
	shaderManager->setShader(object->getShader());
	shaderManager->SetParameters(world, view, projection);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, object->getTexture());

	glUniform1i(glGetUniformLocation(object->getShader(), "texture"), 0);

	if (dynamic_cast<Player*>(object))
	{
		Player* tempPlayer = dynamic_cast<Player*>(object);
		Animation::FrameUV* tempFrameUV = tempPlayer->GetCurrentFrameUV();
		glUniform2f(glGetUniformLocation(tempPlayer->getShader(), "uvTopLeft"), tempFrameUV->uvTopLeft.x, tempFrameUV->uvTopLeft.y);
		glUniform2f(glGetUniformLocation(tempPlayer->getShader(), "uvTopRight"), tempFrameUV->uvTopRight.x, tempFrameUV->uvTopRight.y);
		glUniform2f(glGetUniformLocation(tempPlayer->getShader(), "uvBotLeft"), tempFrameUV->uvBotLeft.x, tempFrameUV->uvBotLeft.y);
		glUniform2f(glGetUniformLocation(tempPlayer->getShader(), "uvBotRight"), tempFrameUV->uvBotRight.x, tempFrameUV->uvBotRight.y);

//		printf("TopLeft: %f %f\n", tempFrameUV->uvBotLeft.x, tempFrameUV->uvBotLeft.y);
	}
	
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
}
