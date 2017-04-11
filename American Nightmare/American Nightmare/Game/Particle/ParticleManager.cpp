#include "ParticleManager.h"

ParticleManager::ParticleManager() { }

ParticleManager::ParticleManager(const ParticleManager & other) { }

ParticleManager::~ParticleManager() { }

bool ParticleManager::Start()
{
	Explosion(ParticleEmitter::PIXEL, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 1000);

	return true;
}

void ParticleManager::Stop() { }

void ParticleManager::Explosion(ParticleEmitter::ParticleType type, glm::vec3 position, glm::vec3 color, int amount)
{
	ParticleEmitter emitter;
	emitter.type = type;

//	for (int i = 0; i < amount; i++)
//		emitter.push_back(ParticleEmitter());

	emitters.push_back(emitter);
}

void ParticleManager::Update(sf::Time delta)
{
	for (ParticleEmitter& emitter : emitters)
		emitter.Update(delta);
}

std::vector<Vertex> ParticleManager::getParticlesAsVertices()
{
	std::vector<Vertex> vertices;

	for (ParticleEmitter& emitter : emitters)
	{
		for (ParticleEmitter::Particle& particle : emitter.particles)
		{
			vertices.push_back(particle.getAsVertex());
		}
	}

	return vertices;
}