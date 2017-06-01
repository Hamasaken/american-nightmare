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
		glm::vec4 color = LIGHT_DEFAULT_COLOR,
		float size = LIGHT_SIZE);

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
		glm::vec4 color = BLOOD_DEFAULT_COLOR,
		float size = BLOOD_SIZE);

	////////////////////////////////////////////////////////////
	// \brief Creates an explosion with given texture
	// \param position The position of explosion
	// \param texture The texture of each pixels (smoke/blood/whatevs)
	// \optional amount The amount of spawned blood particles
	// \optional color The color of the most blood
	////////////////////////////////////////////////////////////
	void EffectSmokeCloud(glm::vec3 position, GLuint texture,
		int amount = TEXTURE_DEFAULT_AMOUNT,
		glm::vec4 color = TEXTURE_DEFAULT_COLOR,
		float size = TEXTURE_SIZE);

	////////////////////////////////////////////////////////////
	// \brief Creates an explosion with given texture and in a direction
	// \param position The position of impact
	// \param texture The texture of each pixels (smoke/blood/whatevs)
	// \param angle The direction of the most blood splatter
	// \optional strength The power of the impact (defaults as 0.5f)
	// \optional amount The amount of spawned blood particles
	// \optional color The color of the most blood
	////////////////////////////////////////////////////////////
	void EffectSmokeInDirection(glm::vec3 position, GLuint texture, float angle,
		float strength = 0.01,
		int amount = BLOOD_DEFAULT_AMOUNT,
		glm::vec4 color = TEXTURE_DEFAULT_COLOR,
		float size = TEXTURE_SIZE);

	////////////////////////////////////////////////////////////
	// \brief Creates an explosion with blood
	// \param position The position of explosion
	// \optional amount The amount of spawned blood particles
	// \optional color The color of the most blood
	//  - \note Only works if you've used the setDefaultTextures() func
	////////////////////////////////////////////////////////////
	void EffectBloodCloud(glm::vec3 position,
		int amount = TEXTURE_DEFAULT_AMOUNT,
		glm::vec4 color = TEXTURE_DEFAULT_COLOR,
		float size = TEXTURE_SIZE);

	////////////////////////////////////////////////////////////
	// \brief Creates an explosion with small lines (for the radio)
	// \param position The position of impact
	// \param angle The direction of the most blood splatter
	// \optional strength The power of the impact (defaults as 0.5f)
	// \optional amount The amount of spawned blood particles
	// \optional color The color of the most blood
	////////////////////////////////////////////////////////////
	void EffectMusicLines(glm::vec3 position, float angle,
		float strength = MUSIC_DEFAULT_STRENGTH,
		int amount = MUSIC_DEFAULT_AMOUNT,
		glm::vec4 color = MUSIC_DEFAULT_COLOR,
		float size = MUSIC_SIZE);

	////////////////////////////////////////////////////////////
	// \brief Creates an explosion of nuts and bolts with given texture (gravity is really high)
	// \param position The position of explosion
	// \param texture The texture of each bolt
	// \optional amount The amount of spawned blood particles
	////////////////////////////////////////////////////////////
	void EffectNutsAndBolts(glm::vec3 position, GLuint texture,
		int amount = TEXTURE_DEFAULT_AMOUNT,
		float size = NUTS_SIZE);

	////////////////////////////////////////////////////////////
	// \brief Creates an explosion with given texture
	// \param position The position of explosion
	// \param texture The texture of each pixels (smoke/blood/whatevs)
	// \optional amount The amount of spawned blood particles
	// \optional color The color of the most blood
	////////////////////////////////////////////////////////////
	void EffectConstantSmoke(glm::vec3 position, GLuint texture,
		int amount = TEXTURE_DEFAULT_AMOUNT,
		glm::vec4 color = TEXTURE_DEFAULT_COLOR,
		float size = TEXTURE_SIZE);

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
		glm::vec4 color = LIGHT_DUST_DEFAULT_COLOR,
		float size = LIGHT_DUST_SIZE);

	////////////////////////////////////////////////////////////
	// \brief Creates an smoke signal which always is active until level switch
	// \param position The starting position of every smoke particle
	// \param texture The smoke texture
	// \param angle The angle of which the signal is
	// \optional amount The maximum amount of smoke particle to be active at once
	// \optional color The blending color on the texture
	////////////////////////////////////////////////////////////
	void EffectSmokeSignal(glm::vec3 position, GLuint texture, float angle,
		int amount = SIGNAL_DEFAULT_AMOUNT,
		glm::vec4 color = TEXTURE_DEFAULT_COLOR,
		float size = SIGNAL_DEFAULT_SIZE);

	void ShaderPair(GLuint shader, ParticleType type);
	void setDefaultTextures(GLuint smokeTexture, GLuint bloodTexture);
	GLuint getShaderFromPair(ParticleType type);
	void Update(GLfloat deltaT, glm::vec2 playerPos = glm::vec2(0, 0));

	std::vector<ParticleEmitter*>* getEmitters();

private:
	GLuint shader;

	// temps, if you leave texture as 0 it will default to either
	GLuint smokeTexture;
	GLuint bloodTexture;

	std::vector<std::pair<ParticleType, GLuint>> shaderPairs;
	std::vector<Vertex> vertices;
	std::vector<ParticleEmitter*> emitters;
};

#endif // !PARTICLEMANAGER_H
