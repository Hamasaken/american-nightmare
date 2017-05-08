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
	if (!Start(screenSize, screenPosition, state, soundManager))
		return false;

	return true;
}

bool Screen::Start(glm::vec2 screenSize, glm::vec2 screenPosition, State* state, SoundManager* soundManager)
{
	// Getting screensize
	this->screenSize = screenSize;
	this->screenPosition = screenPosition;
	this->state = state;
	this->soundManager = soundManager;

	// Building a world matrix (just identity matrix)
	worldMatrix = glm::mat4(1.f);

	// Building a projection matrix
	float fov = glm::radians(80.f);
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
	glm::vec3 rot = object->getRotation();
	world = glm::rotate(world, rot.x, glm::vec3(1, 0, 0));
	world = glm::rotate(world, rot.y, glm::vec3(0, 1, 0));
	world = glm::rotate(world, rot.z, glm::vec3(0, 0, 1));

	// Scaling object
	glm::vec3 scale = object->getScale();
	world = glm::scale(world, scale);

	// Setting shader as active and setting parameters
	shaderManager->setShader(object->getShader());
	shaderManager->SetParameters(world, view, projection);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, object->getTextureID());

	glUniform1i(glGetUniformLocation(object->getShader(), "texture"), 0);

	// Drawing object
	object->Draw();
}

void Screen::DrawObjectShadowMap(Object* object, ShaderManager* shaderManager, glm::mat4 lightSpaceMatrix)
{
	// Getting matrices
	glm::mat4 world = worldMatrix;
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 projection = projectionMatrix;

	// Positioning object
	glm::vec3 pos = object->getPosition();
	world = glm::translate(world, pos);

	// Rotating object
	glm::vec3 rot = object->getRotation();
	world = glm::rotate(world, rot.x, glm::vec3(1, 0, 0));
	world = glm::rotate(world, rot.y, glm::vec3(0, 1, 0));
	world = glm::rotate(world, rot.z, glm::vec3(0, 0, 1));

	// Scaling object
	glm::vec3 scale = object->getScale();

	world = glm::scale(world, scale);

	// Setting shader as active and setting parameters
	shaderManager->SetParameters(world, view, projection);

	glUniformMatrix4fv(glGetUniformLocation(shaderManager->getShader(), "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

	// Drawing object
	object->Draw();
}

void Screen::DrawObjectShadowMapTransparent(Animation* animatedObj, ShaderManager* shaderManager, glm::mat4 lightSpaceMatrix)
{
	// Getting matrices
	glm::mat4 world = worldMatrix;
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 projection = projectionMatrix;

	// Positioning object
	glm::vec3 pos = animatedObj->getPosition();
	world = glm::translate(world, pos);

	// Rotating object
	glm::vec3 rot = animatedObj->getRotation();
	world = glm::rotate(world, rot.x, glm::vec3(1, 0, 0));
	world = glm::rotate(world, rot.y, glm::vec3(0, 1, 0));
	world = glm::rotate(world, rot.z, glm::vec3(0, 0, 1));

	// Scaling object
	glm::vec3 scale = animatedObj->getScale();
	world = glm::scale(world, scale);

	// Setting shader as active and setting parameters
	shaderManager->SetParameters(world, view, projection);
	shaderManager->SetParametersAnimated(animatedObj);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, animatedObj->getTextureID());

	glUniform1i(glGetUniformLocation(shaderManager->getShader(), "texture"), 0);

	glUniformMatrix4fv(glGetUniformLocation(shaderManager->getShader(), "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

	// Drawing object
	animatedObj->Draw();
}

void Screen::DrawObjectGUI(Object* object, ShaderManager * shaderManager)
{	
	// Getting matrices
	glm::mat4 world = worldMatrix;
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 projection = projectionMatrix;

	// Positioning object
	glm::vec3 pos = object->getPosition();
	world = glm::translate(world, pos);

	// Rotating object
	glm::vec3 rot = object->getRotation();
	world = glm::rotate(world, rot.x, glm::vec3(1, 0, 0));
	world = glm::rotate(world, rot.y, glm::vec3(0, 1, 0));
	world = glm::rotate(world, rot.z, glm::vec3(0, 0, 1));

	// Scaling object
	glm::vec3 scale = object->getScale();
	world = glm::scale(world, scale);

	// Setting shader as active and setting parameters
	shaderManager->setShader(object->getShader());
	shaderManager->SetParameters(world, view, projection);

	if (dynamic_cast<Button*>(object) != nullptr)
	{
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, object->getTextureID());

		glUniform1i(glGetUniformLocation(object->getShader(), "texture"), 0);
		glUniform1f(glGetUniformLocation(object->getShader(), "alpha"), dynamic_cast<Button*>(object)->getColor().a);
	}
	else if (dynamic_cast<Text*>(object) != nullptr)
	{
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, dynamic_cast<Text*>(object)->getTexture());

		glUniform1i(glGetUniformLocation(object->getShader(), "texture"), 0);
		glUniform1f(glGetUniformLocation(object->getShader(), "alpha"), 1.f);
	}

	glEnable(GL_BLEND);

	// Drawing object
	object->Draw();

	glDisable(GL_BLEND);
}

void Screen::DrawObjectAnimation(Animation* animatedObj, ShaderManager* shaderManager, std::vector<LightManager::PointLight*> pointLightList, std::vector<LightManager::DirectionalLight*> directionalLightList, glm::mat4 lightSpaceMatrix, glm::vec4 lightDirection, GLuint shadowMap, bool useShadow)
{
	// Getting matrices
	glm::mat4 world = worldMatrix;
	glm::mat4 view = camera->getViewMatrix();
	glm::mat4 projection = projectionMatrix;

	// Positioning object
	glm::vec3 pos = animatedObj->getPosition();
	world = glm::translate(world, pos);

	// Rotating object
	glm::vec3 rot = animatedObj->getRotation();
	world = glm::rotate(world, rot.x, glm::vec3(1, 0, 0));
	world = glm::rotate(world, rot.y, glm::vec3(0, 1, 0));
	world = glm::rotate(world, rot.z, glm::vec3(0, 0, 1));

	// Scaling object
	glm::vec3 scale = animatedObj->getScale();
	world = glm::scale(world, scale);

	// Setting shader as active and setting parameters
	shaderManager->setShader(animatedObj->getShader());
	shaderManager->SetParameters(world, view, projection);
	shaderManager->SetParametersAnimated(animatedObj);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, animatedObj->getTextureID());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, animatedObj->getAnimationNormal());
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, shadowMap);

	glUniform1i(glGetUniformLocation(animatedObj->getShader(), "texture"), 0);
	glUniform1i(glGetUniformLocation(animatedObj->getShader(), "normal"), 1);
	glUniform1i(glGetUniformLocation(animatedObj->getShader(), "shadowmap"), 2);

	glUniform4f(glGetUniformLocation(animatedObj->getShader(), "viewPos"), camera->getPosition().x, camera->getPosition().y, camera->getPosition().z, 1.f);
	glUniform1i(glGetUniformLocation(animatedObj->getShader(), "nrOfPointLights"), pointLightList.size());
	glUniform1i(glGetUniformLocation(animatedObj->getShader(), "nrOfDirectionalLights"), directionalLightList.size());

	glUniformMatrix4fv(glGetUniformLocation(animatedObj->getShader(), "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
	glUniform1i(glGetUniformLocation(animatedObj->getShader(), "useShadow"), useShadow);
	glUniform4f(glGetUniformLocation(animatedObj->getShader(), "lightDirection"), lightDirection.x, lightDirection.y, lightDirection.z, lightDirection.w);

	std::string index;

	for (int i = 0; i < pointLightList.size(); i++)
	{
		index = std::to_string(i);
		glUniform4f(glGetUniformLocation(animatedObj->getShader(), ("pointLights[" + index + "].position").c_str()), pointLightList[i]->position.x, pointLightList[i]->position.y, pointLightList[i]->position.z, pointLightList[i]->position.w);
		glUniform4f(glGetUniformLocation(animatedObj->getShader(), ("pointLights[" + index + "].diffuse").c_str()), pointLightList[i]->diffuse.x, pointLightList[i]->diffuse.y, pointLightList[i]->diffuse.z, pointLightList[i]->diffuse.w);
		glUniform4f(glGetUniformLocation(animatedObj->getShader(), ("pointLights[" + index + "].specular").c_str()), pointLightList[i]->specular.x, pointLightList[i]->specular.y, pointLightList[i]->specular.z, pointLightList[i]->specular.w);
		glUniform1f(glGetUniformLocation(animatedObj->getShader(), ("pointLights[" + index + "].strength").c_str()), pointLightList[i]->strength);
		glUniform1f(glGetUniformLocation(animatedObj->getShader(), ("pointLights[" + index + "].constant").c_str()), pointLightList[i]->constant);
		glUniform1f(glGetUniformLocation(animatedObj->getShader(), ("pointLights[" + index + "].linear").c_str()), pointLightList[i]->linear);
		glUniform1f(glGetUniformLocation(animatedObj->getShader(), ("pointLights[" + index + "].quadratic").c_str()), pointLightList[i]->quadratic);
		glUniform1f(glGetUniformLocation(animatedObj->getShader(), ("pointLights[" + index + "].radius").c_str()), pointLightList[i]->radius);
	}

	for (int i = 0; i < directionalLightList.size(); i++)
	{
		index = std::to_string(i);
		glUniform4f(glGetUniformLocation(animatedObj->getShader(), ("directionalLights[" + index + "].direction").c_str()), directionalLightList[i]->direction.x, directionalLightList[i]->direction.y, directionalLightList[i]->direction.z, directionalLightList[i]->direction.w);
		glUniform4f(glGetUniformLocation(animatedObj->getShader(), ("directionalLights[" + index + "].diffuse").c_str()), directionalLightList[i]->diffuse.x, directionalLightList[i]->diffuse.y, directionalLightList[i]->diffuse.z, directionalLightList[i]->diffuse.w);
		glUniform4f(glGetUniformLocation(animatedObj->getShader(), ("directionalLights[" + index + "].specular").c_str()), directionalLightList[i]->specular.x, directionalLightList[i]->specular.y, directionalLightList[i]->specular.z, directionalLightList[i]->specular.w);
		glUniform1f(glGetUniformLocation(animatedObj->getShader(), ("directionalLights[" + index + "].strength").c_str()), directionalLightList[i]->strength);
	}
	
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
	glm::vec3 rot = object->getRotation();
	world = glm::rotate(world, rot.x, glm::vec3(1, 0, 0));
	world = glm::rotate(world, rot.y, glm::vec3(0, 1, 0));
	world = glm::rotate(world, rot.z, glm::vec3(0, 0, 1));

	// Scaling object
	glm::vec3 scale = object->getScale();
	world = glm::scale(world, scale);

	// Setting shader as active and setting parameters
	shaderManager->setShader(object->getShader());
	shaderManager->SetParameters(world, view, projection);

	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, object->getTextureID());

	glUniform1i(glGetUniformLocation(object->getShader(), "texture"), 0);

	// Drawing object
	object->Draw();
}

void Screen::DrawObjectLightPass(DeferredRendering* drRendering, ShaderManager* shaderManager, std::vector<LightManager::PointLight*> pointLightList, std::vector<LightManager::DirectionalLight*> directionalLightList, glm::mat4 lightSpaceMatrix, glm::vec4 lightDirection, GLuint shadowMap, bool useShadow)
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
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, shadowMap);

	glUniform1i(glGetUniformLocation(drRendering->getLightShader(), "drPosition"), 0);
	glUniform1i(glGetUniformLocation(drRendering->getLightShader(), "drNormal"), 1);
	glUniform1i(glGetUniformLocation(drRendering->getLightShader(), "drAmbient"), 2);
	glUniform1i(glGetUniformLocation(drRendering->getLightShader(), "drDiffuse"), 3);
	glUniform1i(glGetUniformLocation(drRendering->getLightShader(), "drSpecular"), 4);
	glUniform1i(glGetUniformLocation(drRendering->getLightShader(), "shadowmap"), 5);

	glUniform1i(glGetUniformLocation(drRendering->getLightShader(), "nrOfPointLights"), pointLightList.size());
	glUniform1i(glGetUniformLocation(drRendering->getLightShader(), "nrOfDirectionalLights"), directionalLightList.size());

	glUniform4f(glGetUniformLocation(drRendering->getLightShader(), "lightDirection"), lightDirection.x, lightDirection.y, lightDirection.z, lightDirection.w);

	std::string index;

	for (int i = 0; i < pointLightList.size(); i++)
	{
		index = std::to_string(i);
		glUniform4f(glGetUniformLocation(drRendering->getLightShader(), ("pointLights[" + index + "].position").c_str()), pointLightList[i]->position.x, pointLightList[i]->position.y, pointLightList[i]->position.z, pointLightList[i]->position.w);
		glUniform4f(glGetUniformLocation(drRendering->getLightShader(), ("pointLights[" + index + "].diffuse").c_str()), pointLightList[i]->diffuse.x, pointLightList[i]->diffuse.y, pointLightList[i]->diffuse.z, pointLightList[i]->diffuse.w);
		glUniform4f(glGetUniformLocation(drRendering->getLightShader(), ("pointLights[" + index + "].specular").c_str()), pointLightList[i]->specular.x, pointLightList[i]->specular.y, pointLightList[i]->specular.z, pointLightList[i]->specular.w);
		glUniform1f(glGetUniformLocation(drRendering->getLightShader(), ("pointLights[" + index + "].strength").c_str()), pointLightList[i]->strength);
		glUniform1f(glGetUniformLocation(drRendering->getLightShader(), ("pointLights[" + index + "].constant").c_str()), pointLightList[i]->constant);
		glUniform1f(glGetUniformLocation(drRendering->getLightShader(), ("pointLights[" + index + "].linear").c_str()), pointLightList[i]->linear);
		glUniform1f(glGetUniformLocation(drRendering->getLightShader(), ("pointLights[" + index + "].quadratic").c_str()), pointLightList[i]->quadratic);
		glUniform1f(glGetUniformLocation(drRendering->getLightShader(), ("pointLights[" + index + "].radius").c_str()), pointLightList[i]->radius);
	}

	for (int i = 0; i < directionalLightList.size(); i++)
	{
		index = std::to_string(i);
		glUniform4f(glGetUniformLocation(drRendering->getLightShader(), ("directionalLights[" + index + "].direction").c_str()), directionalLightList[i]->direction.x, directionalLightList[i]->direction.y, directionalLightList[i]->direction.z, directionalLightList[i]->direction.w);
		glUniform4f(glGetUniformLocation(drRendering->getLightShader(), ("directionalLights[" + index + "].diffuse").c_str()), directionalLightList[i]->diffuse.x, directionalLightList[i]->diffuse.y, directionalLightList[i]->diffuse.z, directionalLightList[i]->diffuse.w);
		glUniform4f(glGetUniformLocation(drRendering->getLightShader(), ("directionalLights[" + index + "].specular").c_str()), directionalLightList[i]->specular.x, directionalLightList[i]->specular.y, directionalLightList[i]->specular.z, directionalLightList[i]->specular.w);
		glUniform1f(glGetUniformLocation(drRendering->getLightShader(), ("directionalLights[" + index + "].strength").c_str()), directionalLightList[i]->strength);
	}

	glUniformMatrix4fv(glGetUniformLocation(drRendering->getLightShader(), "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
	glUniform1i(glGetUniformLocation(drRendering->getLightShader(), "useShadow"), useShadow);

	glDisable(GL_DEPTH_TEST);

	// Drawing object
	model->Draw();

	glEnable(GL_DEPTH_TEST);
}

void Screen::DrawParticles(ParticleManager* particleManager, ShaderManager * shaderManager)
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shaderManager->setShader(particleManager->getShader());
	shaderManager->SetParameters(worldMatrix, camera->getViewMatrix(), projectionMatrix);

	glDisable(GL_DEPTH_TEST);
	particleManager->Draw();
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
