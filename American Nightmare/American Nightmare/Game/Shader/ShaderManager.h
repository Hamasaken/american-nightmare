#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include "..\..\Accessories.h"
#include <fstream>
#include <sstream>
#include <vector>

class ShaderManager
{
public:
	ShaderManager();
	ShaderManager(const ShaderManager& other);
	~ShaderManager();

	void Start();
	void Stop();

	void AddShader(std::string name, std::string vs, std::string fs);
	void AddShader(std::string name, std::string vs, std::string gs, std::string fs);

	void setShader(GLuint shaderProgram);
	bool setShader(std::string name);
	GLuint getShader() const;
	GLuint getShader(std::string name) const;

	bool SetParameters(glm::mat4 world, glm::mat4 view, glm::mat4 projection);

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
	GLuint compileShader(std::string text, GLenum type);

	std::vector<ShaderProgram> shaderList;
	GLuint currentShaderProgram;
};

#endif // !SHADERMANAGER_H
