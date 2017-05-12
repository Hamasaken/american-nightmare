#ifndef SHADOWMANAGER_H
#define SHADOWMANAGER_H

#include "../../Accessories.h"
#include "../../Game/LightManager.h"
#include <vector>

class ShadowManager
{
public:
	struct DirectionalShadowMap
	{
		GLuint shadowMap;
		GLuint shadowFBO;
		glm::mat4 lightSpaceMatrix;
		glm::vec4 lightDirection;
		glm::vec2 resolution;

		DirectionalShadowMap() : shadowMap(-1), shadowFBO(-1), lightSpaceMatrix(glm::mat4()), lightDirection(glm::vec4()), resolution(glm::vec2()) {}
		DirectionalShadowMap(GLuint shadowMap, GLuint shadowFBO, glm::mat4 lightSpaceMatrix, glm::vec4 lightDirection, glm::vec2 resolution) : shadowMap(shadowMap), shadowFBO(shadowFBO), lightSpaceMatrix(lightSpaceMatrix), lightDirection(lightDirection), resolution(resolution) {}
		DirectionalShadowMap(const DirectionalShadowMap& shadowMap) : shadowMap(shadowMap.shadowMap), shadowFBO(shadowMap.shadowFBO), lightSpaceMatrix(shadowMap.lightSpaceMatrix), lightDirection(shadowMap.lightDirection), resolution(shadowMap.resolution) {}
	};

	ShadowManager();
	ShadowManager(const ShadowManager& other);
	~ShadowManager();

	void Start(GLuint directionalShadowShader, GLuint directionalShadowShaderTr);
	void Stop();

	void AddDirectional(LightManager::DirectionalLight* light, glm::vec2 resolution, GLfloat size, GLfloat nearPlane, GLfloat farPlane);

	std::vector<ShadowManager::DirectionalShadowMap*> getDirectionalShadowMapList() const;
	void setUseShadows(bool useShadows);
	bool getUseShadows() const;
	GLuint getDirectionalShadowShader() const;
	GLuint getDirectionalShadowShaderTr() const;

private:

	void createShadowBuffer(GLuint &shadowFBO, GLuint &shadowMap, glm::vec2 resolution);

	std::vector<DirectionalShadowMap*> directionalShadowMapList;
	GLuint directionalShadowShader;
	GLuint directionalShadowShaderTr;
	bool useShadows;
};

#endif // !SHADOWMANAGER_H

