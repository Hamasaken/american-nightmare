#include "Model.h"

Model::Model() { }

Model::Model(const Model& other) { }

Model::~Model() { }

bool Model::Start(std::string modelPath)
{
	// Trying to load model
//	if (!LoadModel(openGL, modelPath))
//		return false;

	return true;
}

// Temp function
void Model::BuildTriangle()
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
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// Generating buffers
	glGenBuffers(1, &indexBuffer);
	glGenBuffers(1, &vertexBuffer);

	// Binding the vertex buffer and putting in data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, vertices, GL_STATIC_DRAW);

	// Enable both vertex posiiton & color
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Setting the location and size of the attributes
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (unsigned char*)(3 * sizeof(float)));

	// Binding the index buffer and putting in data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, indices, GL_STATIC_DRAW);

	// Clearing from memeory
	delete[]vertices; vertices = nullptr;
	delete[]indices; indices = nullptr;
}

// Temp function
void Model::BuildQuad()
{
	Vertex* vertices;
	unsigned int* indices;

	vertexCount = 4;
	indexCount = 6;
	vertices = new Vertex[vertexCount];
	indices = new unsigned int[indexCount];

	// Quad
	vertices[0].setPosition(glm::vec3(-1, 1, 0));
	vertices[0].setColor(glm::vec3(1, 0, 0));
	vertices[1].setPosition(glm::vec3(1, 1, 0));
	vertices[1].setColor(glm::vec3(0, 1, 0));
	vertices[2].setPosition(glm::vec3(1, -1, 0));
	vertices[2].setColor(glm::vec3(0, 0, 1));
	vertices[3].setPosition(glm::vec3(-1, -1, 0));
	vertices[3].setColor(glm::vec3(1, 1, 1));


	//for (int i = 0; i < indexCount; i++)
	//	indices[i] = i;

	indices[0] = 0;
	indices[1] = 2;
	indices[2] = 3;
	indices[3] = 0;
	indices[4] = 1;
	indices[5] = 2;

	// Creating the vertex buffer that will hold the buffers
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// Generating buffers
	glGenBuffers(1, &indexBuffer);
	glGenBuffers(1, &vertexBuffer);

	// Binding the vertex buffer and putting in data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, vertices, GL_STATIC_DRAW);

	// Enable both vertex posiiton & color
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Setting the location and size of the attributes
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (unsigned char*)(3 * sizeof(float)));

	// Binding the index buffer and putting in data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, indices, GL_STATIC_DRAW);

	// Clearing from memeory
	delete[]vertices; vertices = nullptr;
	delete[]indices; indices = nullptr;
}


// Temp function
void Model::BuildQuadTexture()
{
	VertexUV* vertices;
	unsigned int* indices;

	vertexCount = 4;
	indexCount = 6;
	vertices = new VertexUV[vertexCount];
	indices = new unsigned int[indexCount];

	// Quad
	vertices[0].setPosition(glm::vec3(-1, 1, 0));
	vertices[0].setUV(glm::vec2(0, 1));
	vertices[1].setPosition(glm::vec3(1, 1, 0));
	vertices[1].setUV(glm::vec2(1, 1));
	vertices[2].setPosition(glm::vec3(1, -1, 0));
	vertices[2].setUV(glm::vec2(1, 0));
	vertices[3].setPosition(glm::vec3(-1, -1, 0));
	vertices[3].setUV(glm::vec2(0, 0));


	//for (int i = 0; i < indexCount; i++)
	//	indices[i] = i;

	indices[0] = 0;
	indices[1] = 2;
	indices[2] = 3;
	indices[3] = 0;
	indices[4] = 1;
	indices[5] = 2;

	// Creating the vertex buffer that will hold the buffers
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// Generating buffers
	glGenBuffers(1, &indexBuffer);
	glGenBuffers(1, &vertexBuffer);

	// Binding the vertex buffer and putting in data
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexUV) * vertexCount, vertices, GL_STATIC_DRAW);

	// Enable both vertex posiiton & color
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Setting the location and size of the attributes
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(VertexUV), 0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexUV), (unsigned char*)(3 * sizeof(float)));

	// Binding the index buffer and putting in data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexCount, indices, GL_STATIC_DRAW);

	// Clearing from memeory
	delete[]vertices; vertices = nullptr;
	delete[]indices; indices = nullptr;
}

bool Model::LoadModel(std::string modelPath)
{
	// Load model from file
	return true;
}

void Model::Stop()
{
	// Disable the attributes
	glBindVertexArray(vertexArray);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	// Deleteing buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glDeleteBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glDeleteBuffers(1, &indexBuffer);

	// Deleting vertex array
	glBindVertexArray(vertexArray);
	glDeleteVertexArrays(1, &vertexArray);
}

void Model::Draw()
{
	glBindVertexArray(vertexArray);

	// Render vertex buffer using index buffer
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}
