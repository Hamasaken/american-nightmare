#include "ParticleManager.h"

ParticleManager::ParticleManager() { }

ParticleManager::ParticleManager(const ParticleManager & other) { }

ParticleManager::~ParticleManager() { }

void ParticleManager::ShaderPair(GLuint shader, ParticleType type)
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

void ParticleManager::EffectExplosionLights(glm::vec3 position, int amount, glm::vec4 color, float size)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::LIGHT);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	glm::vec2 s(size, size);
	emitter->LightExplosion(position, color, s, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectBloodSplatter(glm::vec3 position, float angle, float strength, int amount, glm::vec4 color, float size)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::BLOOD);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	glm::vec2 s(size, size);
	emitter->BloodSplatter(position, angle, strength, color, s, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectSmokeCloud(glm::vec3 position, GLuint texture, int amount, glm::vec4 color, float size)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::TEXTURE);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Checking if caller can't reach material manager
	GLuint finalTexture = texture;
	if (finalTexture == 0)
		finalTexture = smokeTexture;

	// Creating particles with inputted variables into emitter
	glm::vec2 s(size, size);
	emitter->SmokeCloud(position, finalTexture, color, s, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectSmokeInDirection(glm::vec3 position, GLuint texture, float angle, float strength, int amount, glm::vec4 color, float size)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::TEXTURE);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Checking if caller can't reach material manager
	GLuint finalTexture = texture;
	if (finalTexture == 0)
		finalTexture = smokeTexture;

	// Creating particles with inputted variables into emitter
	glm::vec2 s(size, size);
	emitter->SmokeInDir(position, finalTexture, angle, strength, color, s, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectBloodCloud(glm::vec3 position, int amount, glm::vec4 color, float size)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::TEXTURE);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	glm::vec2 s(size, size);
	emitter->SmokeCloud(position, bloodTexture, color, s, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectMusicLines(glm::vec3 position, float angle, float strength, int amount, glm::vec4 color, float size)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::MUSIC);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	glm::vec2 s(size, size);
	emitter->MusicLines(position, angle, strength, color, s, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectNutsAndBolts(glm::vec3 position, GLuint texture, int amount, float size)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::NUTSBOLTS);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Checking if caller can't reach material manager
	GLuint finalTexture = texture;
	if (finalTexture == 0)
		finalTexture = smokeTexture;

	// Creating particles with inputted variables into emitter
	glm::vec2 s(size, size);
	emitter->NutsAndBolts(position, finalTexture, s, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectConstantSmoke(glm::vec3 position, GLuint texture, int amount, glm::vec4 color, float size)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::SMOKE);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	glm::vec2 s(size, size);
	emitter->ConstantSmoke(position, texture, color, s, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectLightDust(glm::vec3 center, glm::vec3 dimensions, int amount, glm::vec4 color, float size)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleType::LIGHT_DUST);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	glm::vec2 s(size, size);
	emitter->LightDust(center, dimensions, color, s, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectSmokeSignal(glm::vec3 position, GLuint texture, float angle, int amount, glm::vec4 color, float size)
{
	// Creating a emmiter with a specific type
	IncreasingParticleEmitter* emitter = new IncreasingParticleEmitter();
	emitter->setType(ParticleType::SMOKE);
	emitter->setShader(getShaderFromPair(emitter->getType()));

	// Creating particles with inputted variables into emitter
	glm::vec2 s(size, size);
	emitter->SignalSmoke(position, texture, angle, color, s, amount);
	emitters.push_back(emitter);
}

void ParticleManager::Update(GLfloat deltaT, glm::vec2 playerPos)
{
	for (int i = 0; i < int(emitters.size()); i++)
	{
		if (!emitters[i]->getIsComplete())
			emitters[i]->Update(deltaT, playerPos);
		else
		{
			emitters[i]->Stop();
			delete emitters[i];
			emitters.erase(emitters.begin() + i);
		}
	}
}

std::vector<ParticleEmitter*>* ParticleManager::getEmitters() { return &emitters; }

void ParticleManager::setDefaultTextures(GLuint smokeTexture, GLuint bloodTexture)
{
	this->smokeTexture = smokeTexture;
	this->bloodTexture = bloodTexture;
}
