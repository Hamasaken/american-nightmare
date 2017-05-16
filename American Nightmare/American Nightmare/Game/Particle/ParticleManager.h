#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "../../Accessories.h"
#include "ParticleEmitter.h"
#include "../Shader/ShaderManager.h"

// LIGHT PARTICLES DEFAULTS
#define LIGHT_DEFAULT_COLOR		glm::vec4(1.f, 0.1f, 0.05f, 1.f)
#define LIGHT_DEFAULT_AMOUNT	25
#define LIGHT_SIZE				glm::vec2(8.f, 8.f)

// BLOOD PARTICLES DEFAULTS
#define BLOOD_DEFAULT_COLOR		glm::vec4(1.f, 0.1f, 0.05f, 1.f)
#define BLOOD_DEFAULT_AMOUNT	25
#define BLOOD_DEFAULT_STRENGTH	0.08f
#define BLOOD_SIZE				glm::vec2(8.f, 8.f)

// TEXTURE PARTICLES DEFAULTS
#define TEXTURE_DEFAULT_COLOR	glm::vec4(1.f, 1.f, 1.f, 1.f)
#define TEXTURE_DEFAULT_AMOUNT	10
#define TEXTURE_SIZE			glm::vec2(1.f, 1.f)

// LIGHT DUST PARTICLES DEFAULTS
#define LIGHT_DUST_DEFAULT_AMOUNT	100
#define LIGHT_DUST_DEFAULT_COLOR	glm::vec4(1.f, 1.f, 1.f, 1.f)
#define LIGHT_DUST_SIZE				glm::vec2(5.f, 5.f)

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
	void EffectTextureExplosion(glm::vec3 position, GLuint texture,
		int amount = TEXTURE_DEFAULT_AMOUNT,
		glm::vec4 color = TEXTURE_DEFAULT_COLOR);

	////////////////////////////////////////////////////////////
	// \brief Creates an explosion with given texture
	// \param position The position of explosion
	// \optional amount The amount of spawned blood particles
	// \optional color The color of the most blood
	////////////////////////////////////////////////////////////
	void EffectLightDust(glm::vec3 position, 
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
