#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "ParticleEmitter.h"

// LIGHT PARTICLES DEFAULTS
#define LIGHT_DEFAULT_COLOR		glm::vec4(1.f, 0.1f, 0.05f, 1.f)
#define LIGHT_DEFAULT_AMOUNT	25
#define LIGHT_SIZE				glm::vec2(2.f, 2.f)

// BLOOD PARTICLES DEFAULTS
#define BLOOD_DEFAULT_COLOR		glm::vec4(1.f, 0.1f, 0.05f, 1.f)
#define BLOOD_DEFAULT_AMOUNT	25
#define BLOOD_DEFAULT_STRENGTH	0.08f
#define BLOOD_SIZE				glm::vec2(2.f, 2.f)

class ParticleManager
{
public:
	ParticleManager();
	ParticleManager(const ParticleManager& other);
	~ParticleManager();

	bool Start();
	void Stop();

	void MakeVertices();

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

	void Update(GLfloat deltaT);
	void Draw();

	GLuint getShader();
	void setShader(GLuint shader);

private:

	GLuint shader;
	std::vector<Vertex> vertices;
	std::vector<ParticleEmitter*> emitters;
	unsigned int vertexArray;
	unsigned int vertexBuffer;
	int vertexCount;
};

#endif // !PARTICLEMANAGER_H
