#include "ParticleManager.h"

ParticleManager::ParticleManager() { }

ParticleManager::ParticleManager(const ParticleManager & other) { }

ParticleManager::~ParticleManager() { }

bool ParticleManager::Start()
{
	return true;
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

	// Disable the attributes
	glBindVertexArray(vertexArray);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	// Deleteing buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glDeleteBuffers(1, &vertexBuffer);

	// Deleting vertex array
	glBindVertexArray(vertexArray);
	glDeleteVertexArrays(1, &vertexArray);
}

void ParticleManager::MakeVertices()
{
	// Clearing previous stuff
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glDeleteBuffers(1, &vertexBuffer);
	glBindVertexArray(vertexArray);
	glDeleteVertexArrays(1, &vertexArray);
	vertices.clear();

	// Creating the vertices
	for (ParticleEmitter* emitter : emitters)
	{
		std::vector<Vertex*>* emitterVertices = emitter->getParticlesAsVertices();
		std::transform(std::begin(*emitterVertices), std::end(*emitterVertices), std::back_inserter(vertices), [](Vertex* item) { return *item; });
	}

	// Getting the number of vertices
	vertexCount = vertices.size();

	// If the emitters are active but empty
	if (vertexCount == 0) return;

	// Creating the vertex buffer that will hold the buffers
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// Generating buffer
	glGenBuffers(1, &vertexBuffer);

	// Binding the vertex buffer and putting in data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, (&vertices[0]), GL_STATIC_DRAW);

	// Enable both vertex posiiton & color
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// Setting the location and size of the attributes
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (unsigned char*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (unsigned char*)(7 * sizeof(float)));
}

void ParticleManager::EffectExplosionLights(glm::vec3 position, int amount, glm::vec4 color)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleEmitter::LIGHT);

	// Creating particles with inputted variables into emitter
	emitter->LightExplosion(position, color, LIGHT_SIZE, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectBloodSplatter(glm::vec3 position, float angle, float strength, int amount, glm::vec4 color)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleEmitter::BLOOD);

	// Creating particles with inputted variables into emitter
	emitter->BloodSplatter(position, angle, strength, color, BLOOD_SIZE, amount);
	emitters.push_back(emitter);
}

void ParticleManager::EffectTextureExplosion(glm::vec3 position, GLuint texture, int amount, glm::vec4 color)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(ParticleEmitter::TEXTURE);

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

	// Updating vertices and vertexarray
	if (emitters.size() != 0)
		MakeVertices();
}

void ParticleManager::Draw()
{
	glBindVertexArray(vertexArray);

	// Render vertex buffer using index buffer
	glDrawArrays(GL_POINTS, 0, vertexCount);
}

GLuint ParticleManager::getShader() { return shader; }

void ParticleManager::setShader(GLuint shader) { this->shader = shader; }
