#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter() 
{
	isComplete = false;
	texture = -1;
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

void ParticleEmitter::TextureExplosion(glm::vec3 position, GLuint texture, glm::vec4 color, glm::vec2 size, int amount)
{
	this->texture = texture;
	for (int i = 0; i < amount; i++)
	{
		TextureParticle* particle = new TextureParticle;
		particle->Start(position, color, size);
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

	// Disable the attributes
	glBindVertexArray(vertexArray);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	// Deleteing buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glDeleteBuffers(1, &vertexBuffer);

	// Deleting vertex array
	glBindVertexArray(vertexArray);
	glDeleteVertexArrays(1, &vertexArray);
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

	// If this emitter is out of particles, otherwise, build vertexarray
	if (particles.size() == 0)
		isComplete = true;
	else
		MakeVertices();
}

void ParticleEmitter::MakeVertices()
{
	// Clearing previous stuff
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glDeleteBuffers(1, &vertexBuffer);
	glBindVertexArray(vertexArray);
	glDeleteVertexArrays(1, &vertexArray);

	vertices.clear();	
	for (Particle* p : particles)
		vertices.push_back(*p->getAsVertex());

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
	glEnableVertexAttribArray(3);

	// Setting the location and size of the attributes
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(Vertex), (unsigned char*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (unsigned char*)(7 * sizeof(float)));
	glVertexAttribPointer(3, 1, GL_FLOAT, false, sizeof(Vertex), (unsigned char*)(9 * sizeof(float)));
}

void ParticleEmitter::Draw()
{
	glBindVertexArray(vertexArray);

	// Render vertex buffer using index buffer
	glDrawArrays(GL_POINTS, 0, vertexCount);
}

void ParticleEmitter::setPosition(glm::vec3 position) { this->position = position; }
glm::vec3 ParticleEmitter::getPosition() { return position; }
bool ParticleEmitter::getIsComplete() { return isComplete; }
void ParticleEmitter::setType(ParticleType type) { this->type = type; }
ParticleType ParticleEmitter::getType() { return type; }
int ParticleEmitter::getNumberOfParticles() { return particles.size(); }
void ParticleEmitter::setShader(GLuint shader) { this->shader = shader; }
GLuint ParticleEmitter::getTexture() const { return texture; }
GLuint ParticleEmitter::getShader() const { return shader; }
