#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter() { }

ParticleEmitter::ParticleEmitter(const ParticleEmitter & other) { }

ParticleEmitter::~ParticleEmitter() { }

void ParticleEmitter::CreateParticles(glm::vec3 position, glm::vec3 color, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		Particle particle(position, color);
		particles.push_back(particle);
	}
}

void ParticleEmitter::Update(GLfloat delta)
{
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i].update(delta);
		if (particles[i].isDead)
			particles.erase(particles.begin() + i);
	}
}

std::vector<Vertex> ParticleEmitter::getParticlesAsVertices() 
{
	std::vector<Vertex> vertices;

	Vertex v;
	for (Particle& p : particles)
	{
		v.setColor(p.color);
		v.setPosition(p.position);
		vertices.push_back(v);
	}

	return vertices;
}

void ParticleEmitter::setType(ParticleType type) { this->type = type; }
ParticleEmitter::ParticleType ParticleEmitter::getType() { return type; }
int ParticleEmitter::getNumberOfParticles() { return particles.size(); }
