#include "LightManager.h"

LightManager::LightManager() { }

LightManager::LightManager(const LightManager& other) { }

LightManager::~LightManager() { }

void LightManager::Clear()
{
	pointLightList.clear();
	directionalLightList.clear();
}

void LightManager::AddPointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat constant, GLfloat linear, GLfloat quadratic)
{
	pointLightList.push_back(PointLight(position, ambient, diffuse, specular, constant, linear, quadratic));
}

void LightManager::AddDirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	directionalLightList.push_back(DirectionalLight(direction, ambient, diffuse, specular));
}