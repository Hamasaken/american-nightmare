#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "../../Accessories.h"

#define VELOCITY (rand() % 16000 - 8000) / 10000.f
#define VELOCITY_FALL_OFF 0.08f
#define PARTICLE_LIFETIME (rand() % 50000) / 2500.f

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
			this->position = position;
			this->color = color;
			this->lifeTime = PARTICLE_LIFETIME;
			this->isDead = false;

			velocity = glm::vec3(VELOCITY, VELOCITY, VELOCITY);
		}

		virtual void update(GLfloat delta) 
		{
		//	lifeTime -= delta;
			lifeTime -= 0.1f;
			if (lifeTime < NULL)
				isDead = true;

			velocity += (glm::vec3(0, 0, 0) - velocity) * VELOCITY_FALL_OFF;
			position += velocity; // * delta.asSeconds();
		}

		Vertex getAsVertex()
		{
			Vertex v;
			v.setColor(color);
			v.setPosition(position);
			return v;
		}

		bool isDead;
		GLfloat lifeTime;
		glm::vec3 color;
		glm::vec3 position;
		glm::vec3 velocity;
	};

	ParticleEmitter();
	ParticleEmitter(const ParticleEmitter& other);
	~ParticleEmitter();

	void CreateParticles(glm::vec3 position, glm::vec3 color, int amount);

	void Update(GLfloat delta);

	void setType(ParticleType type);
	ParticleType getType();
	int getNumberOfParticles();
	

	std::vector<Vertex> getParticlesAsVertices();

private:
	ParticleType type;
	std::vector<Particle> particles;
};

#endif // !PARTICLEEMITTER_H
