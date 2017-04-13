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
	// \brief Loads the modelfile and makes vertices & indices
	////////////////////////////////////////////////////////////
	bool Start(std::string modelPath);

	////////////////////////////////////////////////////////////
	// TEMPORARY FUNCTION, REPLACE THIS WITH LOADMODEL WHEN DONE
	////////////////////////////////////////////////////////////
	void BuildTriangle();
	void BuildQuad();
	void BuildQuadTexture();
	void BuildQuad(glm::vec3 position, glm::vec4 color, glm::vec2 size); // For button
	
	////////////////////////////////////////////////////////////
	// \brief Loads a model with vertices and normals and inserts into buffers
	// \param path The file in question
	// \return Returns false if the file could not be found or not read
	////////////////////////////////////////////////////////////
	bool LoadModel(std::string modelPath);

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
