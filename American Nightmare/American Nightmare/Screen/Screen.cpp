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
	if (!Start(screenSize))
		return false;

	return true;
}

bool Screen::Start(glm::vec2 screenSize)
{
	// Getting screensize
	this->screenSize = screenSize;

	// Building a world matrix (just identity matrix)
	worldMatrix = glm::mat4(1.f);

	// Building a projection matrix
	float fov = glm::pi<float>() / 0.40f;
	projectionMatrix = glm::perspective(fov, screenSize.x / screenSize.y, 0.1f, 50.f);

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

	// If object is animated, set additional parameters
	if (dynamic_cast<Animation*>(object))
	{
		Animation* tempCharacter = dynamic_cast<Animation*>(object);
		shaderManager->SetParametersAnimated(tempCharacter);
	}

	// Drawing object
	object->Draw();
}

void Screen::DrawObjectLightPass(DeferredRendering* drRendering, ShaderManager* shaderManager)
{
	glClear(GL_COLOR_BUFFER_BIT);

	Model* model = drRendering->getFinalRenderQuad();

	// Setting shader as active and setting parameters
	shaderManager->setShader(drRendering->getLightShader());

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, drRendering->getDRPosition());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, drRendering->getDRNormal());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, drRendering->getDRAmbient());
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, drRendering->getDRDiffuse());
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, drRendering->getDRSpecular());

	glUniform1i(glGetUniformLocation(drRendering->getLightShader(), "drPosition"), 0);
	glUniform1i(glGetUniformLocation(drRendering->getLightShader(), "drNormal"), 1);
	glUniform1i(glGetUniformLocation(drRendering->getLightShader(), "drAmbient"), 2);
	glUniform1i(glGetUniformLocation(drRendering->getLightShader(), "drDiffuse"), 3);
	glUniform1i(glGetUniformLocation(drRendering->getLightShader(), "drSpecular"), 4);

	glUniform4f(glGetUniformLocation(shaderManager->getShader("deferred_final"), "viewPos"), camera->getPosition().x, camera->getPosition().y, camera->getPosition().z, 1.f);

	glDisable(GL_DEPTH_TEST);

	// Drawing object
	model->Draw();

	glEnable(GL_DEPTH_TEST);
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
