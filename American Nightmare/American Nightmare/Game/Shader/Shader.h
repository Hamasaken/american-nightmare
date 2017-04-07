#ifndef SHADER_H
#define SHADER_H

#include "../../OpenGL.h"
#include <fstream>
#include <string>
#include <sstream>

class Shader
{
public:
	Shader();
	Shader(const Shader& other);
	~Shader();
	virtual void Stop(OpenGL* openGL) = 0;

	////////////////////////////////////////////////////////////
	// \brief Setting this shader as openGL currently active
	////////////////////////////////////////////////////////////
	void SetShader(OpenGL* openGL);

	////////////////////////////////////////////////////////////
	// \brief Function setting parameters into shaderprogram
	////////////////////////////////////////////////////////////
	virtual bool SetParameters(OpenGL* openGL, glm::mat4 world, glm::mat4 view, glm::mat4 projection) = 0;

protected:
	GLuint shaderProgram;	//< The Shader Program

	////////////////////////////////////////////////////////////
	// \brief Reads the file at path and returns string
	// \return Returns the full file in text as a long string in one line
	////////////////////////////////////////////////////////////
	std::string getSource(std::string path);

	////////////////////////////////////////////////////////////
	// \brief Compiles the shader
	// \param text The full text from the file
	// \param type What type of file it is, vertex/fragment/etc
	// \return Returns the id where it's stored in OpenGL
	////////////////////////////////////////////////////////////
	GLuint compileShader(OpenGL* openGL, std::string text, GLenum type);
};

#endif // !SHADER_H
