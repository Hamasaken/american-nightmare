#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Particle.h"
#include "BloodParticle.h"
#include "TextureParticle.h"
#include "DustParticle.h"

class ParticleEmitter
{
public:
	ParticleEmitter();
	ParticleEmitter(const ParticleEmitter& other);
	~ParticleEmitter();

	void LightExplosion(glm::vec3 position, glm::vec4 color, glm::vec2 size, int amount);
	void BloodSplatter(glm::vec3 position, float angle, float strength, glm::vec4 color, glm::vec2 size, int amount);
	void SmokeCloud(glm::vec3 position, GLuint texture, glm::vec4 color, glm::vec2 size, int amount);
	void ConstantSmoke(glm::vec3 position, GLuint texture, glm::vec4 color, glm::vec2 size, int amount);
	void LightDust(glm::vec3 center, glm::vec3 dimensions, glm::vec4 color, glm::vec2 size, int amount);

	////////////////////////////////////////////////////////////
	// \brief Unloads every particle in this vector
	////////////////////////////////////////////////////////////
	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Updates every particle in this emitter
	// \param deltaT Time between each frame in milliseconds
	////////////////////////////////////////////////////////////
	void Update(GLfloat deltaT);

	void MakeVertices();

	void Draw();

	// Get & Set functions
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	bool getIsComplete();
	void setType(ParticleType type);
	ParticleType getType();
	int getNumberOfParticles();
	void setShader(GLuint shader);
	GLuint getTexture() const;
	GLuint getShader() const;

private:
	unsigned int vertexArray;
	unsigned int vertexBuffer;
	int vertexCount;

	bool isComplete;					//< If this emitter is finished or not
	glm::vec3 position;					//< The starting position of this emitter (will use for optimaztion later on)
	ParticleType type;					//< The type of particles inside this emitter
	std::vector<Vertex> vertices;		//< The vertices in this emitter in a vector
	std::vector<Particle*> particles;	//< The particles in this emitter in a vector
	GLuint texture;						//< Holds the potential texture for the particles
	GLuint shader;						//< Holds the shader for this portion of particles
};

#endif // !PARTICLEEMITTER_H
