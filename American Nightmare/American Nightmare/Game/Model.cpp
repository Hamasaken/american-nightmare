#include "Model.h"

Model::Model() { }

Model::Model(const Model& other) { }

Model::~Model() { }

void Model::BuildTriangle(OpenGL* openGL)
{
	Vertex* vertices;
	unsigned int* indices;

	vertexCount = 3;
	indexCount = 3;
	vertices = new Vertex[vertexCount];
	indices = new unsigned int[indexCount];

	// Triangle
	vertices[0].setPosition(glm::vec3(0, 1, 0));
	vertices[0].setColor(glm::vec3(1, 0, 1));
	vertices[1].setPosition(glm::vec3(1, -1, 0));
	vertices[1].setColor(glm::vec3(1, 1, 0));
	vertices[2].setPosition(glm::vec3(-1, -1, 0));
	vertices[2].setColor(glm::vec3(0, 1, 1));


	for (int i = 0; i < indexCount; i++)
		indices[i] = i;

	// Creating the vertex buffer that will hold the buffers
	openGL->glGenVertexArrays(1, &vertexArray);
	openGL->glBindVertexArray(vertexArray);

	// Generating buffers
	openGL->glGenBuffers(1, &indexBuffer);
	openGL->glGenBuffers(1, &vertexBuffer);

	// Binding the vertex buffer and putting in data
	openGL->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	openGL->glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, vertices, GL_STATIC_DRAW);

	// Enable both vertex posiiton & color
	openGL->glEnableVertexAttribArray(0);
	openGL->glEnableVertexAttribArray(1);

	// Setting the location and size of the attributes
	openGL->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	openGL->glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
	openGL->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	openGL->glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (unsigned char*)(3 * sizeof(float)));

	// Binding the index buffer and putting in data
	openGL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	openGL->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, indices, GL_STATIC_DRAW);

	// Clearing from memeory
	delete[]vertices; vertices = nullptr;
	delete[]indices; indices = nullptr;
}

bool LoadModel(OpenGL* openGL, std::string modelPath)
{
	// Load model from file
	return true;
}

void Model::Stop(OpenGL * openGL)
{
	// Disable the attributes
	openGL->glBindVertexArray(vertexArray);
	openGL->glDisableVertexAttribArray(0);
	openGL->glDisableVertexAttribArray(1);

	// Deleteing buffers
	openGL->glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	openGL->glDeleteBuffers(1, &vertexBuffer);
	openGL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	openGL->glDeleteBuffers(1, &indexBuffer);

	// Deleting vertex array
	openGL->glBindVertexArray(vertexArray);
	openGL->glDeleteVertexArrays(1, &vertexArray);
}

void Model::Draw(OpenGL * openGL)
{
	openGL->glBindVertexArray(vertexArray);

	// Render vertex buffer using index buffer
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}
