#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Particle.h"

class ParticleEmitter
{
public:
	enum ParticleType
	{
		PIXEL
	};

	ParticleEmitter();
	ParticleEmitter(const ParticleEmitter& other);
	~ParticleEmitter();

	void CreateParticles(glm::vec3 position, glm::vec4 color, int amount);

	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Updates every particle in this emitter
	// \param deltaT Time between each frame in milliseconds
	////////////////////////////////////////////////////////////
	void Update(GLfloat deltaT);

	// Get & Set functions
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	void setType(ParticleType type);
	ParticleType getType();
	int getNumberOfParticles();
	std::vector<Vertex> getParticlesAsVertices();

private:
	glm::vec3 position;
	ParticleType type;
	std::vector<Particle*> particles;
};

#endif // !PARTICLEEMITTER_H
