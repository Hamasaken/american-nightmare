#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter() 
{
	isComplete = false;
}

ParticleEmitter::ParticleEmitter(const ParticleEmitter & other) { }

ParticleEmitter::~ParticleEmitter() { }

void ParticleEmitter::LightExplosion(glm::vec3 position, glm::vec4 color, glm::vec2 size, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		Particle* particle = new Particle;
		particle->Start(position, color, size);
		particles.push_back(particle);
	}
}

void ParticleEmitter::BloodSplatter(glm::vec3 position, float angle, float strength, glm::vec4 color, glm::vec2 size, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		BloodParticle* particle = new BloodParticle;
		particle->Start(position, color, size, angle, strength);
		particles.push_back(particle);
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

std::vector<Vertex*>* ParticleEmitter::getParticlesAsVertices() 
{
	vertices.clear();

	for (Particle* p : particles)
		vertices.push_back(p->getAsVertex());

	return &vertices;
}

void ParticleEmitter::setPosition(glm::vec3 position) { this->position = position; }
glm::vec3 ParticleEmitter::getPosition() { return position; }
bool ParticleEmitter::getIsComplete() { return isComplete; }
void ParticleEmitter::setType(ParticleType type) { this->type = type; }
ParticleEmitter::ParticleType ParticleEmitter::getType() { return type; }
int ParticleEmitter::getNumberOfParticles() { return particles.size(); }
