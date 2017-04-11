#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H


class ParticleEmitter
{
public:
	struct Particle
	{
		Particle(glm::vec3 position, glm::vec3 color)
		{
			this->position = position;
			this->color = color;

			velocity = glm::vec3((rand() % 1000) / 1000.f, (rand() % 1000) / 1000.f, (rand() % 1000) / 1000.f);
		}

		virtual void update(sf::Time delta) 
		{
			position += velocity * delta.asSeconds();
		}

		Vertex getAsVertex()
		{
			Vertex v;
			v.setColor(color);
			v.setPosition(position);
			return v;
		}

		glm::vec3 color;
		glm::vec3 position;
		glm::vec3 velocity;
	};

	ParticleEmitter();
	ParticleEmitter(const ParticleEmitter& other);
	~ParticleEmitter();

	void CreateParticles

	void Update(sf::Time delta)
	{
		for (Particle& particle : particles)
			particle.update(delta);
	}

private:

	ParticleType type;
	std::vector<Particle> particles;
};

#endif // !PARTICLEEMITTER_H
