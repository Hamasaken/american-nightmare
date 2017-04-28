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
		glm::vec4 position;

		glm::vec4 diffuse;
		glm::vec4 specular;

		GLfloat strength;
		GLfloat constant;
		GLfloat linear;
		GLfloat quadratic;
		GLfloat radius;

		PointLight() : position(glm::vec4()), diffuse(glm::vec4()), specular(glm::vec4()), strength(0.f), constant(0.f), linear(0.f), quadratic(0.f), radius(0.f) {}
		PointLight(glm::vec4 position, glm::vec4 diffuse, glm::vec4 specular, GLfloat strength, GLfloat constant, GLfloat linear, GLfloat quadratic, GLfloat radius) : position(position), diffuse(diffuse), specular(specular), strength(strength), constant(constant), linear(linear), quadratic(quadratic), radius(radius) {}
		PointLight(const PointLight& light) : position(light.position), diffuse(light.diffuse), specular(light.specular), strength(light.strength), constant(light.constant), linear(light.linear), quadratic(light.quadratic), radius(light.radius) {}
	};

	struct DirectionalLight
	{
		//std::string name; maybe?
		glm::vec4 direction;

		glm::vec4 diffuse;
		glm::vec4 specular;

		GLfloat strength;

		DirectionalLight() : direction(glm::vec4()), diffuse(glm::vec4()), specular(glm::vec4()), strength(0.f) {}
		DirectionalLight(glm::vec4 direction, glm::vec4 diffuse, glm::vec4 specular, GLfloat strength) : direction(direction), diffuse(diffuse), specular(specular), strength(strength) {}
		DirectionalLight(const DirectionalLight& light) : direction(light.direction), diffuse(light.diffuse), specular(light.specular), strength(light.strength) {}
	};

	LightManager();
	LightManager(const LightManager& other);
	~LightManager();

	void Clear();

	void AddPointLight(glm::vec4 position, glm::vec4 diffuse, glm::vec4 specular, GLfloat strength, GLfloat constant, GLfloat linear, GLfloat quadratic);
	void AddDirectionalLight(glm::vec4 direction, glm::vec4 diffuse, glm::vec4 specular, GLfloat strength);
	//void RemoveLight(); maybe?

	std::vector<PointLight*> getPointLightList() const;
	std::vector<DirectionalLight*> getDirectionalLightList() const;

private:

	std::vector<PointLight*> pointLightList;
	std::vector<DirectionalLight*> directionalLightList;
};

#endif // !LIGHTMANAGER_H

