#include "DeferredRendering.h"

DeferredRendering::DeferredRendering() { }

DeferredRendering::DeferredRendering(const DeferredRendering & other) { }

DeferredRendering::~DeferredRendering() { Stop(); }

bool DeferredRendering::Start(glm::vec2 screenSize, GLuint lightShader, GLuint shadowShader)
{
	this->lightShader = lightShader;
	this->shadowShader = shadowShader;
	this->useShadow = false;
	createDRBuffer(screenSize);
	createShadowBuffer(screenSize);
	finalRenderQuad.BuildQuadTexture();
	return true;
}

void DeferredRendering::Stop()
{
	GLuint* textureList = new GLuint[6];
	textureList[0] = drPosition;
	textureList[1] = drNormal;
	textureList[2] = drAmbient;
	textureList[3] = drDiffuse;
	textureList[4] = drSpecular;
	textureList[5] = shadowMap;

	glDeleteTextures(6, textureList);

	delete[] textureList;

	glDeleteFramebuffers(1, &drFBO);
	glDeleteFramebuffers(1, &shadowFBO);
}

void DeferredRendering::createDRBuffer(glm::vec2 screenSize)
{
	glGenFramebuffers(1, &drFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, drFBO);

	// Position
	glGenTextures(1, &drPosition);
	glBindTexture(GL_TEXTURE_2D, drPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, screenSize.x, screenSize.y, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, drPosition, 0);

	// Normal
	glGenTextures(1, &drNormal);
	glBindTexture(GL_TEXTURE_2D, drNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, screenSize.x, screenSize.y, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, drNormal, 0);

	// Ambient
	glGenTextures(1, &drAmbient);
	glBindTexture(GL_TEXTURE_2D, drAmbient);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenSize.x, screenSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, drAmbient, 0);

	// Diffuse
	glGenTextures(1, &drDiffuse);
	glBindTexture(GL_TEXTURE_2D, drDiffuse);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenSize.x, screenSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, drDiffuse, 0);

	// Specular
	glGenTextures(1, &drSpecular);
	glBindTexture(GL_TEXTURE_2D, drSpecular);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenSize.x, screenSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, drSpecular, 0);

	// Bind Attachments to FBO
	GLuint attachments[5] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4 };
	glDrawBuffers(5, attachments);

	// Depth buffer
	glGenRenderbuffers(1, &drDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, drDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, screenSize.x, screenSize.y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, drDepth);

	// Check if FBO is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("Framebuffer not complete!\n");

	// Unbind
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DeferredRendering::createShadowBuffer(glm::vec2 screenSize)
{
	glGenFramebuffers(1, &shadowFBO);

	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, screenSize.x, screenSize.y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
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

void DeferredRendering::setShadowLight(LightManager::DirectionalLight* light)
{
	glm::mat4 lightProjection = glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, 0.1f, 100.f);
	glm::mat4 lightView = glm::lookAt(glm::vec3(light->position), glm::vec3(light->position + light->direction), glm::vec3(0.f, 1.f, 0.f));
	lightSpaceMatrix = lightProjection * lightView;
	useShadow = true;
}

GLuint DeferredRendering::getDRFBO() const { return drFBO; }
GLuint DeferredRendering::getShadowFBO() const { return shadowFBO; }
GLuint DeferredRendering::getDRPosition() const { return drPosition; }
GLuint DeferredRendering::getDRNormal() const { return drNormal; }
GLuint DeferredRendering::getDRAmbient() const { return drAmbient; }
GLuint DeferredRendering::getDRDiffuse() const { return drDiffuse; }
GLuint DeferredRendering::getDRSpecular() const { return drSpecular; }
GLuint DeferredRendering::getShadowMap() const { return shadowMap; }
GLuint DeferredRendering::getLightShader() const { return lightShader; }
GLuint DeferredRendering::getShadowShader() const { return shadowShader; }
glm::mat4 DeferredRendering::getLightSpaceMatrix() const { return lightSpaceMatrix; }
Model* DeferredRendering::getFinalRenderQuad() { return &finalRenderQuad; }
bool DeferredRendering::useShadows() const { return useShadow; }