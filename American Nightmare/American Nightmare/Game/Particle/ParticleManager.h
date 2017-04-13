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

	void MakeVertices();
	void Effect(ParticleEmitter::ParticleType type, glm::vec3 position, glm::vec4 color, int amount);

	void Update(GLfloat deltaT);
	void Draw();

	GLuint getShader();
	void setShader(GLuint shader);

private:
	GLuint shader;
	std::vector<Vertex> vertices;
	std::vector<ParticleEmitter*> emitters;
	unsigned int vertexArray;
	unsigned int vertexBuffer;
	int vertexCount;
};

#endif // !PARTICLEMANAGER_H
