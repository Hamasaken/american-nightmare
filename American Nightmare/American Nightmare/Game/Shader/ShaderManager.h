#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "../../OpenGL.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class ShaderManager
{
public:
	ShaderManager();
	ShaderManager(const ShaderManager& other);
	~ShaderManager();

	void Start(OpenGL* openGL);
	void Stop(OpenGL* openGL);

	void AddShader(OpenGL* openGL, std::string name, std::string vs, std::string fs);
	void AddShader(OpenGL* openGL, std::string name, std::string vs, std::string gs, std::string fs);

	void SetShader(OpenGL* openGL, GLuint shaderProgram);
	bool SetShader(OpenGL* openGL, std::string name);
	GLuint GetShader() const;
	GLuint GetShader(std::string name) const;

	bool SetParameters(OpenGL* openGL, glm::mat4 world, glm::mat4 view, glm::mat4 projection);

private:
	struct ShaderProgram
	{
		std::string name;
		GLuint id;

		ShaderProgram() : name("undefined"), id(-1) {}
		ShaderProgram(std::string name, GLuint id) : name(name), id(id) {}
		ShaderProgram(const ShaderProgram& shader) : name(shader.name), id(shader.id) {}
	};

	GLuint findShader(std::string name) const;
	std::string getSource(std::string path);
	GLuint compileShader(OpenGL* openGL, std::string text, GLenum type);

	std::vector<ShaderProgram> shaderList;
	GLuint currentShaderProgram;
};

#endif // !SHADERMANAGER_H
