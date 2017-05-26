#include "ShadowManager.h"

ShadowManager::ShadowManager() { }

ShadowManager::ShadowManager(const ShadowManager& other) { }

ShadowManager::~ShadowManager() { }

void ShadowManager::Start(GLuint directionalShadowShader, GLuint directionalShadowShaderTr, GLuint pointShadowShader, GLuint pointShadowShaderTr)
{
	this->directionalShadowShader = directionalShadowShader;
	this->directionalShadowShaderTr = directionalShadowShaderTr;
	this->pointShadowShader = pointShadowShader;
	this->pointShadowShaderTr = pointShadowShaderTr;
	useShadows = false;
}

void ShadowManager::Stop()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Shadow map cleanup
	for (DirectionalShadowMap* shadowMap : directionalShadowMapList)
	{
		glDeleteFramebuffers(1, &shadowMap->shadowFBO);
		glDeleteTextures(1, &shadowMap->shadowMap);
		delete shadowMap;
	}

	for (PointShadowMap* shadowMap : pointShadowMapList)
	{
		glDeleteFramebuffers(1, &shadowMap->shadowFBO);
		glDeleteTextures(1, &shadowMap->shadowCubeMap);
		delete shadowMap;
	}

	directionalShadowMapList.clear();
	pointShadowMapList.clear();
}

void ShadowManager::AddDirectional(LightManager::DirectionalLight* light, glm::vec3 offset, glm::vec2 resolution, glm::vec2 size, GLfloat nearPlane, GLfloat farPlane)
{
	glm::mat4 lightProjection = glm::ortho(-size.x, size.x, -size.y, size.y, nearPlane, farPlane);
	glm::mat4 lightView = glm::lookAt(glm::vec3(light->position), glm::vec3(light->position + light->direction), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 tempLightSpaceMatrix = lightProjection * lightView;

	GLuint tempShadowFBO = 0, tempShadowMap = 0;

	createDirectionalShadowBuffer(tempShadowFBO, tempShadowMap, resolution);

	directionalShadowMapList.push_back(new DirectionalShadowMap(tempShadowMap, tempShadowFBO, tempLightSpaceMatrix, offset, light->direction, resolution));
}

void ShadowManager::createDirectionalShadowBuffer(GLuint &shadowFBO, GLuint &shadowMap, glm::vec2 resolution)
{
	glGenFramebuffers(1, &shadowFBO);

	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, resolution.x, resolution.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float* color = new float[4]{ 1, 1, 1, 1 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
	delete color;

	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// Check if FBO is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("Dir Framebuffer not complete!\n");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowManager::AddPoint(LightManager::PointLight* light, glm::vec2 resolution, GLfloat fov, GLfloat nearPlane)
{
	PointShadowMap* tempShadowMap = new PointShadowMap();

	tempShadowMap->lightPosition = light->position;
	tempShadowMap->lightFarPlane = light->radius;

	glm::mat4 lightProjection = glm::perspective(glm::radians(fov), resolution.x / resolution.y, nearPlane, light->radius);

	tempShadowMap->lightSpaceMatrices.push_back(lightProjection * 
		glm::lookAt(glm::vec3(light->position.x, light->position.y, light->position.z), glm::vec3(light->position.x, light->position.y, light->position.z) + glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, -1.f, 0.f)));
	tempShadowMap->lightSpaceMatrices.push_back(lightProjection *
		glm::lookAt(glm::vec3(light->position.x, light->position.y, light->position.z), glm::vec3(light->position.x, light->position.y, light->position.z) + glm::vec3(-1.f, 0.f, 0.f), glm::vec3(0.f, -1.f, 0.f)));
	tempShadowMap->lightSpaceMatrices.push_back(lightProjection *
		glm::lookAt(glm::vec3(light->position.x, light->position.y, light->position.z), glm::vec3(light->position.x, light->position.y, light->position.z) + glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 1.f)));
	tempShadowMap->lightSpaceMatrices.push_back(lightProjection *
		glm::lookAt(glm::vec3(light->position.x, light->position.y, light->position.z), glm::vec3(light->position.x, light->position.y, light->position.z) + glm::vec3(0.f, -1.f, 0.f), glm::vec3(0.f, 0.f, -1.f)));
	tempShadowMap->lightSpaceMatrices.push_back(lightProjection *
		glm::lookAt(glm::vec3(light->position.x, light->position.y, light->position.z), glm::vec3(light->position.x, light->position.y, light->position.z) + glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, -1.f, 0.f)));
	tempShadowMap->lightSpaceMatrices.push_back(lightProjection *
		glm::lookAt(glm::vec3(light->position.x, light->position.y, light->position.z), glm::vec3(light->position.x, light->position.y, light->position.z) + glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, -1.f, 0.f)));

	createPointShadowBuffer(tempShadowMap->shadowFBO, tempShadowMap->shadowCubeMap, resolution);

	pointShadowMapList.push_back(tempShadowMap);
}

void ShadowManager::createPointShadowBuffer(GLuint &shadowFBO, GLuint &shadowCubeMap, glm::vec2 resolution)
{
	glGenFramebuffers(1, &shadowFBO);

	glGenTextures(1, &shadowCubeMap);

	glBindTexture(GL_TEXTURE_CUBE_MAP, shadowCubeMap);
	for (GLuint i = 0; i < 6; i++)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, resolution.x, resolution.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowCubeMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// Check if FBO is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("Point Framebuffer not complete!\n");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


std::vector<ShadowManager::DirectionalShadowMap*> ShadowManager::getDirectionalShadowMapList() const { return directionalShadowMapList; }
std::vector<ShadowManager::PointShadowMap*> ShadowManager::getPointShadowMapList() const { return pointShadowMapList; }
void ShadowManager::setUseShadows(bool useShadows) { this->useShadows = useShadows; }
bool ShadowManager::getUseShadows() const { return useShadows; }
GLuint ShadowManager::getDirectionalShadowShader() const { return directionalShadowShader; }
GLuint ShadowManager::getDirectionalShadowShaderTr() const { return directionalShadowShaderTr; }
GLuint ShadowManager::getPointShadowShader() const { return pointShadowShader; }
GLuint ShadowManager::getPointShadowShaderTr() const { return pointShadowShaderTr; }