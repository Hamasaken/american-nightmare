#include "ParticleManager.h"

ParticleManager::ParticleManager() { }

ParticleManager::ParticleManager(const ParticleManager & other) { }

ParticleManager::~ParticleManager() { }

bool ParticleManager::Start()
{
	Explosion(PIXEL, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 1000);

	return true;
}

void ParticleManager::Stop() { }

void ParticleManager::Explosion(ParticleType type, glm::vec3 position, glm::vec3 color, int amount)
{
	ParticleEmitter emitter;
	emitter.type = type;

	for (int i = 0; i < amount; i++)
		emitter.particles.push_back(ParticleEmitter(position, color));

	emitters.push_back(emitter);
}

void ParticleManager::Update(sf::Time delta)
{
	for (ParticleEmitter& emitter : emitters)
		emitter.update(delta);
}

std::vector<Vertex> ParticleManager::getParticlesAsVertices()
{
	std::vector<Vertex> vertices;

	for (ParticleEmitter& emitter : emitters)
	{
		for (Particle& particle : emitter.particles)
		{
			vertices.push_back(particle.getAsVertex());
		}
	}

	return vertices;
}