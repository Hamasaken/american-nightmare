#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "../../Accessories.h"
#include "ParticleEmitter.h"
#include "../Shader/ShaderManager.h"

class ParticleManager
{
public:
	ParticleManager();
	ParticleManager(const ParticleManager& other);
	~ParticleManager();

	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Creates an explosion with light particles
	// \param position The position of impact
	// \optional amount The amount of spawned light particles
	// \optional color The color of the most lights
	////////////////////////////////////////////////////////////
	void EffectExplosionLights(glm::vec3 position, 
		int amount = LIGHT_DEFAULT_AMOUNT,
		glm::vec4 color = LIGHT_DEFAULT_COLOR);

	////////////////////////////////////////////////////////////
	// \brief Creates a blood splatter effect
	// \param position The position of impact
	// \param angle The direction of the most blood splatter
	// \optional strength The power of the impact (defaults as 0.5f)
	// \optional amount The amount of spawned blood particles
	// \optional color The color of the most blood
	////////////////////////////////////////////////////////////
	void EffectBloodSplatter(glm::vec3 position, float angle, 
		float strength = BLOOD_DEFAULT_STRENGTH,
		int amount = BLOOD_DEFAULT_AMOUNT,
		glm::vec4 color = BLOOD_DEFAULT_COLOR);

	////////////////////////////////////////////////////////////
	// \brief Creates an explosion with given texture
	// \param position The position of explosion
	// \param texture The texture of each pixels (smoke/blood/whatevs)
	// \optional amount The amount of spawned blood particles
	// \optional color The color of the most blood
	////////////////////////////////////////////////////////////
	void EffectSmokeCloud(glm::vec3 position, GLuint texture,
		int amount = TEXTURE_DEFAULT_AMOUNT,
		glm::vec4 color = TEXTURE_DEFAULT_COLOR);

	////////////////////////////////////////////////////////////
	// \brief Creates an explosion with given texture
	// \param position The position of explosion
	// \param texture The texture of each pixels (smoke/blood/whatevs)
	// \optional amount The amount of spawned blood particles
	// \optional color The color of the most blood
	////////////////////////////////////////////////////////////
	void EffectConstantSmoke(glm::vec3 position, GLuint texture,
		int amount = TEXTURE_DEFAULT_AMOUNT,
		glm::vec4 color = TEXTURE_DEFAULT_COLOR);

	////////////////////////////////////////////////////////////
	// \brief Creates an explosion with given texture
	// \optional center The Center position of the dust effect
	// \optional dimensions The spawn area of light dust particles
	// \optional amount The amount of spawned blood particles
	// \optional color The color of the most blood
	////////////////////////////////////////////////////////////
	void EffectLightDust(glm::vec3 center = LIGHT_DUST_DEFAULT_CENTER, 
		glm::vec3 dimensions = LIGHT_DUST_DEFAULT_DIMENSIONS,
		int amount = LIGHT_DUST_DEFAULT_AMOUNT,
		glm::vec4 color = LIGHT_DUST_DEFAULT_COLOR);

	void ShaderPair(GLuint shader, ParticleType type);
	GLuint getShaderFromPair(ParticleType type);
	void Update(GLfloat deltaT);

	std::vector<ParticleEmitter*>* getEmitters();

private:
	GLuint shader;
	std::vector<std::pair<ParticleType, GLuint>> shaderPairs;
	std::vector<Vertex> vertices;
	std::vector<ParticleEmitter*> emitters;
};

#endif // !PARTICLEMANAGER_H
