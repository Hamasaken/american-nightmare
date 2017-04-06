#ifndef MODEL_H
#define MODEL_H

#include "OpenGL.h"

class Model
{
public:
	Model();
	Model(const Model& other);
	~Model();

	bool Start(OpenGL* openGL);
	void Stop(OpenGL* openGL);
	void Draw(OpenGL* openGL);

private:
	unsigned int vertexArray;
	unsigned int vertexBuffer;
	unsigned int indexBuffer;
	int vertexCount;
	int indexCount;
};

#endif // !MODEL_H
