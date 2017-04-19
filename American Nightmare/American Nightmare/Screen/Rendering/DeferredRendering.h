#ifndef DEFERREDRENDERING_H
#define DEFERREDRENDERING_H

#include "../../Accessories.h"
#include "../../Game\Model.h"

class DeferredRendering
{
public:
	DeferredRendering();
	DeferredRendering(const DeferredRendering& other);
	~DeferredRendering();

	bool Start(glm::vec2 screenSize, GLuint lightShader);
	void Stop();

	GLuint getDRFBO() const;
	GLuint getDRPosition() const;
	GLuint getDRNormal() const;
	GLuint getDRAmbient() const;
	GLuint getDRDiffuse() const;
	GLuint getDRSpecular() const;
	GLuint getLightShader() const;

	Model* getFinalRenderQuad();

private:

	void createDRBuffer(glm::vec2 screenSize); //< Setup for framebuffer

	GLuint drFBO;				//< Frame Buffer Object for deferred rendering

	// Textures for framebuffer
	GLuint drPosition;
	GLuint drNormal;
	GLuint drAmbient;
	GLuint drDiffuse;
	GLuint drSpecular;

	GLuint drDepth;

	Model finalRenderQuad;
	GLuint lightShader;
};

#endif // !DEFERREDRENDERING_H

