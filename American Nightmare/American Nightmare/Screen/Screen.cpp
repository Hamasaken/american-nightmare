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

	// Drawing object
	object->Draw();
}

void Screen::DrawObjectAnimation(Animation* animatedObj, ShaderManager* shaderManager, LightManager::PointLight* light)
{
	// Getting matrices
	glm::mat4 world = worldMatrix;
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 projection = projectionMatrix;

	// Positioning object
	glm::vec3 pos = animatedObj->getPosition();
	world = glm::translate(world, pos);

	// Rotating object
	glm::vec3 rot = animatedObj->getRotationInRadians();
	world = glm::rotate(world, rot.x, glm::vec3(0, 0, 1));
	world = glm::rotate(world, rot.y, glm::vec3(1, 0, 0));
	world = glm::rotate(world, rot.z, glm::vec3(0, 1, 0));

	// Scaling object
	glm::vec3 scale = animatedObj->getScale();
	world = glm::scale(world, scale);

	// Setting shader as active and setting parameters
	shaderManager->setShader(animatedObj->getShader());
	shaderManager->SetParameters(world, view, projection);
	shaderManager->SetParametersAnimated(animatedObj);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, animatedObj->getTexture());

	glUniform1i(glGetUniformLocation(animatedObj->getShader(), "texture"), 0);

	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, object->getAnimationNormal());

	glUniform4f(glGetUniformLocation(animatedObj->getShader(), "viewPos"), camera->getPosition().x, camera->getPosition().y, camera->getPosition().z, 1.f);
	glUniform4f(glGetUniformLocation(animatedObj->getShader(), "lightPos"), light->position.x, light->position.y, light->position.z, light->position.z);
	glUniform4f(glGetUniformLocation(animatedObj->getShader(), "lightDiffuse"), light->diffuse.x, light->diffuse.y, light->diffuse.z, light->diffuse.w);
	glUniform4f(glGetUniformLocation(animatedObj->getShader(), "lightSpecular"), light->specular.x, light->specular.y, light->specular.z, light->specular.w);

	// Drawing object
	animatedObj->Draw();
}

void Screen::DrawObjectGeometryPass(Object* object, ShaderManager* shaderManager)
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

	// Drawing object
	object->Draw();
}

void Screen::DrawObjectLightPass(DeferredRendering* drRendering, ShaderManager* shaderManager, LightManager::PointLight* light)
{

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

	glUniform4f(glGetUniformLocation(drRendering->getLightShader(), "viewPos"), camera->getPosition().x, camera->getPosition().y, camera->getPosition().z, 1.f);
	glUniform4f(glGetUniformLocation(drRendering->getLightShader(), "lightPos"), light->position.x, light->position.y, light->position.z, light->position.z);
	glUniform4f(glGetUniformLocation(drRendering->getLightShader(), "lightDiffuse"), light->diffuse.x, light->diffuse.y, light->diffuse.z, light->diffuse.w);
	glUniform4f(glGetUniformLocation(drRendering->getLightShader(), "lightSpecular"), light->specular.x, light->specular.y, light->specular.z, light->specular.w);


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
