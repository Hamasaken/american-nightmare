#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter() { }

ParticleEmitter::ParticleEmitter(const ParticleEmitter & other) { }

ParticleEmitter::~ParticleEmitter() { }

void ParticleEmitter::CreateParticles(glm::vec3 position, glm::vec4 color, int amount)
{
	this->position = position;
	this->isComplete = false;

	switch (type)
	{
	case TRIANGLE:
		for (int i = 0; i < amount; i++)
		{
			Particle* particle = new Particle;
			particle->Start(position, color);
			particles.push_back(particle);
		}
	break;
	}
}

void ParticleEmitter::Stop()
{
	// Erasing everything in vector
	for (int i = 0; i < particles.size(); i++)
	{
		if (particles[i] != nullptr)
		{
			particles[i]->Stop();
			delete particles[i];
			particles[i] = nullptr;
		}
	}
	particles.clear();
	isComplete = true;
}

void ParticleEmitter::Update(GLfloat deltaT)
{
	// Updating particles and checking if they are dead or not
	for (int i = 0; i < particles.size(); i++)
	{
		particles[i]->Update(deltaT);
		if (particles[i]->getIsDead())
		{
			particles[i]->Stop();
			delete particles[i];
			particles.erase(particles.begin() + i);
		}
	}

	// If this emitter is out of particles
	if (particles.size() == 0)
		isComplete = true;
}

std::vector<Vertex> ParticleEmitter::getParticlesAsVertices() 
{
	std::vector<Vertex> vertices;
	for (Particle* p : particles)
		vertices.push_back(p->getAsVertex());

	return vertices;
}

void ParticleEmitter::setPosition(glm::vec3 position) { this->position = position; }
glm::vec3 ParticleEmitter::getPosition() { return position; }
bool ParticleEmitter::getIsComplete() { return isComplete; }
void ParticleEmitter::setType(ParticleType type) { this->type = type; }
ParticleEmitter::ParticleType ParticleEmitter::getType() { return type; }
int ParticleEmitter::getNumberOfParticles() { return particles.size(); }
