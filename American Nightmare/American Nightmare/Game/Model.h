#ifndef MODEL_H
#define MODEL_H

#include "..\Accessories.h"

class Model
{
public:
	Model();
	Model(const Model& other);
	~Model();

	////////////////////////////////////////////////////////////
	// TEMPORARY FUNCTION, REPLACE THIS WITH LOADMODEL WHEN DONE
	////////////////////////////////////////////////////////////
	void BuildTriangle();
	void BuildQuad();
	void BuildQuadTexture();
	void BuildQuadTextureBig();
	void BuildQuad(glm::vec2 size); // Temporary for button
	
	////////////////////////////////////////////////////////////
	// \brief Loads a model with vertices and normals and inserts into buffers
	// \param vertices A vector with the vertices to be inputted
	// \return Returns false if the file could not be found or not read
	////////////////////////////////////////////////////////////
	bool LoadModel(std::vector<VertexUV> vertices);

	////////////////////////////////////////////////////////////
	// \brief Unloads everything
	////////////////////////////////////////////////////////////
	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Binds the vertex array to openGL and draws it
	////////////////////////////////////////////////////////////
	void Draw();

private:
	unsigned int vertexArray;
	unsigned int vertexBuffer;
	unsigned int indexBuffer;
	int vertexCount;
	int indexCount;
};

#endif // !MODEL_H
