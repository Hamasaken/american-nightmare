#ifndef SOLIDSHADER_H
#define SOLIDSHADER_H

#include "../OpenGL.h"
#include <fstream>
#include <string>
#include <sstream>

class SolidShader
{
public:
	SolidShader();
	SolidShader(const SolidShader& other);
	~SolidShader();

	void Start(OpenGL* openGL, std::string vs, std::string fs);	// lazy ass std::runtime errors atm, change this into a bool function later
	void Stop(OpenGL* openGL);

	void SetShader(OpenGL* openGL);
	bool SetParameters(OpenGL* openGL, glm::mat4 world, glm::mat4 view, glm::mat4 projection);

private:
	std::string getSource(std::string path);
	GLuint compileShader(OpenGL* openGL, std::string text, GLenum type);

	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint shaderProgram;
};

#endif // !SOLIDSHADER_H
