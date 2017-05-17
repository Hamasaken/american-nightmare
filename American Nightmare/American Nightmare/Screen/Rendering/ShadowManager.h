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

	struct PointShadowMap
	{
		GLuint shadowCubeMap;
		GLuint shadowFBO;
		glm::vec4 lightPosition;
		GLfloat lightFarPlane;
		std::vector<glm::mat4> lightSpaceMatrices;
		glm::vec2 resolution;

		PointShadowMap() : shadowCubeMap(-1), shadowFBO(-1), lightPosition(glm::vec4()), lightFarPlane(0), lightSpaceMatrices(std::vector<glm::mat4>()), resolution(glm::vec2()) {}
		PointShadowMap(GLuint shadowCubeMap, GLuint shadowFBO, glm::vec4 lightPosition, GLfloat lightFarPlane, std::vector<glm::mat4> lightSpaceMatrices, glm::vec2 resolution) : shadowCubeMap(shadowCubeMap), shadowFBO(shadowFBO), lightPosition(lightPosition), lightFarPlane(lightFarPlane), lightSpaceMatrices(lightSpaceMatrices), resolution(resolution) {}
		PointShadowMap(const PointShadowMap& pointShadowMap) : shadowCubeMap(pointShadowMap.shadowCubeMap), shadowFBO(pointShadowMap.shadowFBO), lightPosition(pointShadowMap.lightPosition), lightFarPlane(pointShadowMap.lightFarPlane), lightSpaceMatrices(pointShadowMap.lightSpaceMatrices), resolution(pointShadowMap.resolution) {}
	};

	ShadowManager();
	ShadowManager(const ShadowManager& other);
	~ShadowManager();

	void Start(GLuint directionalShadowShader, GLuint directionalShadowShaderTr, GLuint pointShadowShader, GLuint pointShadowShaderTr);
	void Stop();

	void AddDirectional(LightManager::DirectionalLight* light, glm::vec2 resolution, glm::vec2 size, GLfloat nearPlane, GLfloat farPlane);
	void AddPoint(LightManager::PointLight* light, glm::vec2 resolution, GLfloat fov, GLfloat nearPlane);

	std::vector<ShadowManager::DirectionalShadowMap*> getDirectionalShadowMapList() const;
	std::vector<ShadowManager::PointShadowMap*> getPointShadowMapList() const;
	void setUseShadows(bool useShadows);
	bool getUseShadows() const;
	GLuint getDirectionalShadowShader() const;
	GLuint getDirectionalShadowShaderTr() const;
	GLuint getPointShadowShader() const;
	GLuint getPointShadowShaderTr() const;

private:

	void createDirectionalShadowBuffer(GLuint &shadowFBO, GLuint &shadowMap, glm::vec2 resolution);
	void createPointShadowBuffer(GLuint &shadowFBO, GLuint &shadowCubeMap, glm::vec2 resolution);

	std::vector<DirectionalShadowMap*> directionalShadowMapList;
	GLuint directionalShadowShader;
	GLuint directionalShadowShaderTr;

	std::vector<PointShadowMap*> pointShadowMapList;
	GLuint pointShadowShader;
	GLuint pointShadowShaderTr;

	bool useShadows;
};

#endif // !SHADOWMANAGER_H

