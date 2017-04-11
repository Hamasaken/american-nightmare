#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H

#include "ParticleEmitter.h"

class ParticleManager
{
public:
	ParticleManager();
	ParticleManager(const ParticleManager& other);
	~ParticleManager();

	bool Start();
	void Stop();

	void Explosion(ParticleEmitter::ParticleType type, glm::vec3 position, glm::vec3 color, int amount);

	void Update(sf::Time delta);
	
	std::vector<Vertex> getParticlesAsVertices();

private:
	std::vector<ParticleEmitter> emitters;
};

#endif // !PARTICLEMANAGER_H
