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

		GLfloat constant;
		GLfloat linear;
		GLfloat quadratic;

		PointLight() : position(glm::vec4()), diffuse(glm::vec4()), specular(glm::vec4()), constant(0.f), linear(0.f), quadratic(0.f) {}
		PointLight(glm::vec4 position, glm::vec4 diffuse, glm::vec4 specular, GLfloat constant, GLfloat linear, GLfloat quadratic) : position(position), diffuse(diffuse), specular(specular), constant(constant), linear(linear), quadratic(quadratic) {}
		PointLight(const PointLight& light) : position(light.position), diffuse(light.diffuse), specular(light.specular), constant(light.constant), linear(light.linear), quadratic(light.quadratic) {}
	};

	struct DirectionalLight
	{
		//std::string name; maybe?
		glm::vec4 direction;

		glm::vec4 diffuse;
		glm::vec4 specular;

		DirectionalLight() : direction(glm::vec4()), diffuse(glm::vec4()), specular(glm::vec4()) {}
		DirectionalLight(glm::vec4 direction, glm::vec4 diffuse, glm::vec4 specular) : direction(direction), diffuse(diffuse), specular(specular) {}
		DirectionalLight(const DirectionalLight& light) : direction(light.direction), diffuse(light.diffuse), specular(light.specular) {}
	};

	LightManager();
	LightManager(const LightManager& other);
	~LightManager();

	void Clear();

	void AddPointLight(glm::vec4 position, glm::vec4 diffuse, glm::vec4 specular, GLfloat constant, GLfloat linear, GLfloat quadratic);
	void AddDirectionalLight(glm::vec4 direction, glm::vec4 diffuse, glm::vec4 specular);
	//void RemoveLight(); maybe?

	std::vector<PointLight*> getPointLightList() const;
	std::vector<DirectionalLight*> getDirectionalLightList() const;

private:
	std::vector<PointLight*> pointLightList;
	std::vector<DirectionalLight*> directionalLightList;
};

#endif // !LIGHTMANAGER_H

