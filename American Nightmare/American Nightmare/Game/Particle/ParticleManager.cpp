#include "ParticleManager.h"

ParticleManager::ParticleManager() { }

ParticleManager::ParticleManager(const ParticleManager & other) { }

ParticleManager::~ParticleManager() { }

bool ParticleManager::Start()
{
	Explosion(ParticleEmitter::PIXEL, glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), 1000);

	return true;
}

void ParticleManager::Stop() 
{
	// Erasing everything in vector
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
	// Creating the vertices
	std::vector<Vertex> vertices;
	for (ParticleEmitter& emitter : emitters)
	{
		std::vector<Vertex> emitterVertices = emitter.getParticlesAsVertices();
		vertices.insert(vertices.end(), emitterVertices.begin(), emitterVertices.end());
	}

	// Creating the vertex buffer that will hold the buffers
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// Generating buffer
	glGenBuffers(1, &vertexBuffer);

	// Binding the vertex buffer and putting in data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, &vertices[0], GL_STATIC_DRAW);

	// Enable both vertex posiiton & color
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Setting the location and size of the attributes
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (unsigned char*)(3 * sizeof(float)));

	// Clearing from memeory
	vertices.clear();
}

void ParticleManager::Explosion(ParticleEmitter::ParticleType type, glm::vec3 position, glm::vec3 color, int amount)
{
	// Creating a emmiter with a specific type
	ParticleEmitter emitter;
	emitter.setType(type);

	// Creating particles with inputted variables into emitter
	emitter.CreateParticles(position, color, amount);

	// Pushing new emitter into vector
	emitters.push_back(emitter);
}

void ParticleManager::Update(sf::Time delta)
{
	for (int i = 0; i < int(emitters.size()); i++)
	{
	//	if (!emitter.isComplete())
			emitters[i].Update(delta);
	//	else 
	//		emitters.erase(emitter);
	}

	// Updating vertices and vertexarray
	if (emitters.size() != 0)
		MakeVertices();
}

void ParticleManager::Draw()
{
	glBindVertexArray(vertexArray);

	// Render vertex buffer using index buffer
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}