#include "ShadowManager.h"

ShadowManager::ShadowManager() { }

ShadowManager::ShadowManager(const ShadowManager& other) { }

ShadowManager::~ShadowManager() { }

void ShadowManager::Start(GLuint directionalShadowShader, GLuint directionalShadowShaderTr)
{
	this->directionalShadowShader = directionalShadowShader;
	this->directionalShadowShaderTr = directionalShadowShaderTr;
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

	directionalShadowMapList.clear();
}

void ShadowManager::AddDirectional(LightManager::DirectionalLight* light, glm::vec2 resolution, GLfloat size, GLfloat nearPlane, GLfloat farPlane)
{
	glm::mat4 lightProjection = glm::ortho(-size, size, -size, size, nearPlane, farPlane);
	glm::mat4 lightView = glm::lookAt(glm::vec3(light->position), glm::vec3(light->position + light->direction), glm::vec3(0.f, 1.f, 0.f));
	glm::mat4 tempLightSpaceMatrix = lightProjection * lightView;

	GLuint tempShadowFBO = 0, tempShadowMap = 0;

	createShadowBuffer(tempShadowFBO, tempShadowMap, resolution);

	directionalShadowMapList.push_back(new DirectionalShadowMap(tempShadowMap, tempShadowFBO, tempLightSpaceMatrix, light->direction, resolution));
}

void ShadowManager::createShadowBuffer(GLuint &shadowFBO, GLuint &shadowMap, glm::vec2 resolution)
{
	glGenFramebuffers(1, &shadowFBO);

	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, resolution.x, resolution.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// Check if FBO is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("Framebuffer not complete!\n");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

std::vector<ShadowManager::DirectionalShadowMap*> ShadowManager::getDirectionalShadowMapList() const { return directionalShadowMapList; }
void ShadowManager::setUseShadows(bool useShadows) { this->useShadows = useShadows; }
bool ShadowManager::getUseShadows() const { return useShadows; }
GLuint ShadowManager::getDirectionalShadowShader() const { return directionalShadowShader; }
GLuint ShadowManager::getDirectionalShadowShaderTr() const { return directionalShadowShaderTr; }