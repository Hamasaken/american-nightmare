#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter() { }

ParticleEmitter::ParticleEmitter(const ParticleEmitter & other) { }

ParticleEmitter::~ParticleEmitter() { }

void ParticleEmitter::CreateParticles(glm::vec3 position, glm::vec3 color, int amount)
{

}

void ParticleEmitter::setType(ParticleType type) { this->type = type; }

ParticleEmitter::ParticleType ParticleEmitter::getType() { return type; }

int ParticleEmitter::getNumberOfParticles() { return particles.size(); }

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
