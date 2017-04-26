#include "LightManager.h"

LightManager::LightManager() { }

LightManager::LightManager(const LightManager& other) { }

LightManager::~LightManager() { Clear(); }

void LightManager::Clear()
{
	for (PointLight* pointLight : pointLightList)
		delete pointLight;

	for (DirectionalLight* directionalLight : directionalLightList)
		delete directionalLight;

	pointLightList.clear();
	directionalLightList.clear();
}

void LightManager::AddPointLight(glm::vec4 position, glm::vec4 diffuse, glm::vec4 specular, GLfloat constant, GLfloat linear, GLfloat quadratic)
{
	pointLightList.push_back(new PointLight(position, diffuse, specular, constant, linear, quadratic));
}

void LightManager::AddDirectionalLight(glm::vec4 direction, glm::vec4 diffuse, glm::vec4 specular)
{
	directionalLightList.push_back(new DirectionalLight(direction, diffuse, specular));
}

std::vector<LightManager::PointLight*> LightManager::getPointLightList() const { return pointLightList; }

std::vector<LightManager::DirectionalLight*> LightManager::getDirectionalLightList() const { return directionalLightList; }



