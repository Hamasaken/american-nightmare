#ifndef MODEL_H
#define MODEL_H

#include "../OpenGL.h"

class Model
{
public:
	Model();
	Model(const Model& other);
	~Model();

	////////////////////////////////////////////////////////////
	// TEMPORARY FUNCTION, REPLACE THIS WITH LOADMODEL WHEN DONE
	////////////////////////////////////////////////////////////
	void BuildTriangle(OpenGL* openGL);
	
	////////////////////////////////////////////////////////////
	// \brief Loads a model with vertices and normals and inserts into buffers
	// \param path The file in question
	// \return Returns false if the file could not be found or not read
	////////////////////////////////////////////////////////////
	bool LoadModel(OpenGL* openGL, std::string modelPath);

	////////////////////////////////////////////////////////////
	// \brief Unloads everything
	////////////////////////////////////////////////////////////
	void Stop(OpenGL* openGL);

	////////////////////////////////////////////////////////////
	// \brief Binds the vertex array to openGL and draws it
	////////////////////////////////////////////////////////////
	void Draw(OpenGL* openGL);

private:
	sf::Sprite sprite;

	unsigned int vertexArray;
	unsigned int vertexBuffer;
	unsigned int indexBuffer;
	int vertexCount;
	int indexCount;
};

#endif // !MODEL_H
