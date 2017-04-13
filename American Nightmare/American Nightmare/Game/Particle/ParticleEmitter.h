#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "../../Accessories.h"

#define VELOCITY		randBetweenF(-0.25f, 0.25f)
#define VELOCITY_FALL_OFF	randBetweenF(0.35f, 0.50f)
#define PARTICLE_LIFETIME	randBetweenF(500.f, 900.f)

class ParticleEmitter
{
public:
	enum ParticleType
	{
		PIXEL
	};

	struct Particle
	{
		Particle(glm::vec3 position, glm::vec3 color)
		{
			vertex.setPosition(position);
			vertex.setColor(color);
			lifeTime = PARTICLE_LIFETIME;
			isDead = false;
			velocity = glm::vec3(VELOCITY, VELOCITY, VELOCITY);
		}

		virtual void update(GLfloat deltaT) 
		{
			lifeTime -= deltaT;
			if (lifeTime < NULL)
				isDead = true;

			velocity += (glm::vec3(0, 0, 0) - velocity) * VELOCITY_FALL_OFF;
			vertex.setPosition(glm::vec3(vertex.x, vertex.y, vertex.z) + velocity * deltaT);
		}

		Vertex getAsVertex() { return vertex; }

		bool isDead;
		GLfloat lifeTime;
		Vertex vertex;
		glm::vec3 velocity;
	};

	ParticleEmitter();
	ParticleEmitter(const ParticleEmitter& other);
	~ParticleEmitter();

	void CreateParticles(glm::vec3 position, glm::vec3 color, int amount);

	void Update(GLfloat deltaT);

	void setType(ParticleType type);
	ParticleType getType();
	int getNumberOfParticles();
	

	std::vector<Vertex> getParticlesAsVertices();



private:
	ParticleType type;
	std::vector<Particle> particles;
};

#endif // !PARTICLEEMITTER_H
