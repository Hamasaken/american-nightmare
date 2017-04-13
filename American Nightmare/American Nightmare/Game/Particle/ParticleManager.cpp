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
		std::vector<Vertex> emitterVertices = emitter->getParticlesAsVertices();
		vertices.insert(vertices.end(), emitterVertices.begin(), emitterVertices.end());
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, &vertices[0], GL_STATIC_DRAW);

	// Enable both vertex posiiton & color
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Setting the location and size of the attributes
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (unsigned char*)(3 * sizeof(float)));
}

void ParticleManager::Explosion(ParticleEmitter::ParticleType type, glm::vec3 position, glm::vec3 color, int amount)
{
	// Creating a emmiter with a specific type
	ParticleEmitter* emitter = new ParticleEmitter();
	emitter->setType(type);

	// Creating particles with inputted variables into emitter
	emitter->CreateParticles(position, color, amount);

	// Pushing new emitter into vector
	emitters.push_back(emitter);
}

void ParticleManager::Update(GLfloat deltaT)
{
	for (int i = 0; i < int(emitters.size()); i++)
	{
	//	if (!emitter.isComplete())
			emitters[i]->Update(deltaT);
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
	glDrawArrays(GL_POINTS, 0, vertexCount);
}

GLuint ParticleManager::getShader() { return shader; }

void ParticleManager::setShader(GLuint shader) { this->shader = shader; }
