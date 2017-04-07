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

	void SetShader(OpenGL* openGL);
	virtual bool SetParameters(OpenGL* openGL, glm::mat4 world, glm::mat4 view, glm::mat4 projection) = 0;

protected:
	GLuint shaderProgram;

	std::string getSource(std::string path);
	GLuint compileShader(OpenGL* openGL, std::string text, GLenum type);
};

#endif // !SHADER_H
