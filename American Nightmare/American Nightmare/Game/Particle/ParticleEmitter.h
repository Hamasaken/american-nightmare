#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Particle.h"
#include "BloodParticle.h"

class ParticleEmitter
{
public:
	// Different particle types
	enum ParticleType
	{
		LIGHT, 
		BLOOD
	};

	ParticleEmitter();
	ParticleEmitter(const ParticleEmitter& other);
	~ParticleEmitter();

	void LightExplosion(glm::vec3 position, glm::vec4 color, glm::vec2 size, int amount);
	void BloodSplatter(glm::vec3 position, float angle, float strength, glm::vec4 color, glm::vec2 size, int amount);

	////////////////////////////////////////////////////////////
	// \brief Unloads every particle in this vector
	////////////////////////////////////////////////////////////
	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Updates every particle in this emitter
	// \param deltaT Time between each frame in milliseconds
	////////////////////////////////////////////////////////////
	void Update(GLfloat deltaT);

	////////////////////////////////////////////////////////////
	// \brief Returns every particle as a vector in this emitter
	////////////////////////////////////////////////////////////
	std::vector<Vertex*>* getParticlesAsVertices();

	// Get & Set functions
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	bool getIsComplete();
	void setType(ParticleType type);
	ParticleType getType();
	int getNumberOfParticles();

private:
	bool isComplete;					//< If this emitter is finished or not
	glm::vec3 position;					//< The starting position of this emitter (will use for optimaztion later on)
	ParticleType type;					//< The type of particles inside this emitter
	std::vector<Vertex*> vertices;		//< The vertices in this emitter in a vector
	std::vector<Particle*> particles;	//< The particles in this emitter in a vector
};

#endif // !PARTICLEEMITTER_H
