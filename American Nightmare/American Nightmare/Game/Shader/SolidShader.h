#ifndef SOLIDSHADER_H
#define SOLIDSHADER_H

#include "Shader.h"

class SolidShader : public Shader
{
public:
	SolidShader();
	SolidShader(const SolidShader& other);
	~SolidShader();

	////////////////////////////////////////////////////////////
	// \brief Loads shader, reads and compiles shader files
	////////////////////////////////////////////////////////////
	void Start(OpenGL* openGL, std::string vs, std::string fs);

	////////////////////////////////////////////////////////////
	// \brief Unloads shader
	////////////////////////////////////////////////////////////
	void Stop(OpenGL* openGL);

	////////////////////////////////////////////////////////////
	// \brief Update parameters
	// \return Returns false if we can't find locations in vertexShader
	////////////////////////////////////////////////////////////
	bool SetParameters(OpenGL* openGL, glm::mat4 world, glm::mat4 view, glm::mat4 projection);

private:
	GLuint vertexShader;	//< Vertex Shader
	GLuint fragmentShader;	//< Fragment Shader
};

#endif // !SOLIDSHADER_H
