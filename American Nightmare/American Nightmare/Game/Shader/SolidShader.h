#ifndef SOLIDSHADER_H
#define SOLIDSHADER_H

#include "Shader.h"

class SolidShader : public Shader
{
public:
	SolidShader();
	SolidShader(const SolidShader& other);
	~SolidShader();

	void Start(OpenGL* openGL, std::string vs, std::string fs);	// lazy ass std::runtime errors atm, change this into a bool function later
	void Stop(OpenGL* openGL);

	bool SetParameters(OpenGL* openGL, glm::mat4 world, glm::mat4 view, glm::mat4 projection);

private:
	GLuint vertexShader;
	GLuint fragmentShader;
};

#endif // !SOLIDSHADER_H
