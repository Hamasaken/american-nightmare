#ifndef DEFERREDRENDERING_H
#define DEFERREDRENDERING_H

#include "../../Accessories.h"
#include "../../Game\Model.h"
#include "../../Game/LightManager.h"

class DeferredRendering
{
public:
	DeferredRendering();
	DeferredRendering(const DeferredRendering& other);
	~DeferredRendering();

	bool Start(glm::vec2 screenSize, GLuint lightShader, GLuint shadowShader);
	void Stop();

	void setShadowLight(LightManager::DirectionalLight* light);

	GLuint getDRFBO() const;
	GLuint getShadowFBO() const;

	GLuint getDRPosition() const;
	GLuint getDRNormal() const;
	GLuint getDRAmbient() const;
	GLuint getDRDiffuse() const;
	GLuint getDRSpecular() const;

	GLuint getShadowMap() const;

	GLuint getLightShader() const;
	GLuint getShadowShader() const;

	glm::mat4 getLightSpaceMatrix() const;

	Model* getFinalRenderQuad();

	bool useShadows() const;

private:

	void createDRBuffer(glm::vec2 screenSize); //< Setup for framebuffer
	void createShadowBuffer(glm::vec2 screenSize);

	GLuint drFBO;				//< Frame Buffer Object for deferred rendering
	GLuint shadowFBO;

	// Textures for framebuffer
	GLuint drPosition;
	GLuint drNormal;
	GLuint drAmbient;
	GLuint drDiffuse;
	GLuint drSpecular;

	GLuint drDepth;

	bool useShadow;
	GLuint shadowMap;
	glm::mat4 lightSpaceMatrix;

	Model finalRenderQuad;
	GLuint lightShader;
	GLuint shadowShader;
};

#endif // !DEFERREDRENDERING_H

