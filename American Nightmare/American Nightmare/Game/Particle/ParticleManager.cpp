#include "ParticleManager.h"

ParticleManager::ParticleManager() { }

ParticleManager::ParticleManager(const ParticleManager & other) { }

ParticleManager::~ParticleManager() { }

void ParticleManager::ShaderPair(GLuint shader,  ParticleType type)
{
	shaderPairs.push_back(std::pair<ParticleType, GLuint>(type, shader));
}

GLuint ParticleManager::getShaderFromPair(ParticleType type)
{
	for (int i = 0; i < shaderPairs.size(); i++)
	{
		if (shaderPairs[i].first == type)
			return shaderPairs[i].second;
	}

	printf("Effect does not have a shader set.\n");
	return this->shader;

	return 0;
}

void ParticleManager::Stop()
{
	// Erasing everything in vector
	for (int i = 0; i < emitters.size(); i++)
	{
		if (emitters[i] != nullptr)
		{
			emitters[i]->Stop();
			delete emitters[i];
			emitters[i] = nullptr;
		}
	}
	emitters.clear();
}

void ParticleManager::EffectExplosionLights(glm::vec3 position, int amount, glm::vec4 color)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::LIGHT);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	emitter->LightExplosion(position, color, LIGHT_SIZE, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectBloodSplatter(glm::vec3 position, float angle, float strength, int amount, glm::vec4 color)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::BLOOD);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	emitter->BloodSplatter(position, angle, strength, color, BLOOD_SIZE, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectTextureExplosion(glm::vec3 position, GLuint texture, int amount, glm::vec4 color)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::TEXTURE);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	emitter->TextureExplosion(position, texture, color, TEXTURE_SIZE, amount);
	emitters.push_back(emitter);
}

void ParticleManager::Update(GLfloat deltaT)
{
	for (int i = 0; i < int(emitters.size()); i++)
	{
		if (!emitters[i]->getIsComplete())
			emitters[i]->Update(deltaT);
		else
		{
			emitters[i]->Stop();
			delete emitters[i];
			emitters.erase(emitters.begin() + i);
		}
	}
}

std::vector<ParticleEmitter*>* ParticleManager::getEmitters() { return &emitters; }
