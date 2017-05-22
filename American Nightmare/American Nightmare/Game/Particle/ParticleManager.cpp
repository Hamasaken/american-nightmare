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
	glm::vec2 size(LIGHT_SIZE, LIGHT_SIZE);
	emitter->LightExplosion(position, color, size, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectBloodSplatter(glm::vec3 position, float angle, float strength, int amount, glm::vec4 color)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::BLOOD);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	glm::vec2 size(BLOOD_SIZE, BLOOD_SIZE);
	emitter->BloodSplatter(position, angle, strength, color, size, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectSmokeCloud(glm::vec3 position, GLuint texture, int amount, glm::vec4 color)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::TEXTURE);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	glm::vec2 size(TEXTURE_SIZE, TEXTURE_SIZE);
	emitter->SmokeCloud(position, texture, color, size, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectNutsAndBolts(glm::vec3 position, GLuint texture, int amount)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::NUTSBOLTS);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	glm::vec2 size(NUTS_SIZE, NUTS_SIZE);
	emitter->NutsAndBolts(position, texture, size, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectConstantSmoke(glm::vec3 position, GLuint texture, int amount, glm::vec4 color)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::SMOKE);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	glm::vec2 size(TEXTURE_SIZE, TEXTURE_SIZE);
	emitter->ConstantSmoke(position, texture, color, size, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectLightDust(glm::vec3 center, glm::vec3 dimensions, int amount, glm::vec4 color)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::LIGHT_DUST);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	glm::vec2 size(LIGHT_DUST_SIZE, LIGHT_DUST_SIZE);
	emitter->LightDust(center, dimensions, color, size, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectSmokeSignal(glm::vec3 position, GLuint texture, float angle, int amount, glm::vec4 color)
{
	// Creating a emmiter with a specific type
	IncreasingParticleEmitter* emitter = new IncreasingParticleEmitter();
	emitter->setType(ParticleType::SMOKE);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	glm::vec2 size(SIGNAL_DEFAULT_SIZE, SIGNAL_DEFAULT_SIZE);
	emitter->SignalSmoke(position, texture, angle, color, size, amount);
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
