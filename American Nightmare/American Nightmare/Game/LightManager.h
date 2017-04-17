#ifndef LIGHTMANAGER_H
#define LIGHTMANAGER_H

#include "..\Accessories.h"
#include <vector>

class LightManager
{
public:
	struct PointLight
	{
		//std::string name; maybe?
		glm::vec3 position;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		GLfloat constant;
		GLfloat linear;
		GLfloat quadratic;

		PointLight() : position(glm::vec3()), ambient(glm::vec3()), diffuse(glm::vec3()), specular(glm::vec3()), constant(0.f), linear(0.f), quadratic(0.f) {}
		PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat constant, GLfloat linear, GLfloat quadratic) : position(position), ambient(ambient), diffuse(diffuse), specular(specular), constant(constant), linear(linear), quadratic(quadratic) {}
		PointLight(const PointLight& light) : position(light.position), ambient(light.ambient), diffuse(light.diffuse), specular(light.specular), constant(light.constant), linear(light.linear), quadratic(light.quadratic) {}
	};

	struct DirectionalLight
	{
		//std::string name; maybe?
		glm::vec3 direction;

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		DirectionalLight() : direction(glm::vec3()), ambient(glm::vec3()), diffuse(glm::vec3()), specular(glm::vec3()) {}
		DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : direction(direction), ambient(ambient), diffuse(diffuse), specular(specular) {}
		DirectionalLight(const DirectionalLight& light) : direction(light.direction), ambient(light.ambient), diffuse(light.diffuse), specular(light.specular) {}
	};

	LightManager();
	LightManager(const LightManager& other);
	~LightManager();

	void Clear();

	void AddPointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat constant, GLfloat linear, GLfloat quadratic);
	void AddDirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
	//void RemoveLight(); maybe?

private:
	std::vector<PointLight> pointLightList;
	std::vector<DirectionalLight> directionalLightList;
};

#endif // !LIGHTMANAGER_H

