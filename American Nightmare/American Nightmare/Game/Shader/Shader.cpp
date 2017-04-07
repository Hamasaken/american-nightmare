#include "Shader.h"

Shader::Shader() { }

Shader::Shader(const Shader& other) { }

Shader::~Shader() { }

void Shader::SetShader(OpenGL* openGL)
{
	openGL->glUseProgram(shaderProgram);
}

std::string Shader::getSource(std::string path)
{
	std::stringstream sstream;
	std::ifstream file(path);
	std::string source;

	if (!file.is_open()) 
		throw std::runtime_error("Could not read shader at: " + path);

	// Reads full file into stream
	sstream << file.rdbuf();

	// Gets the stream as a string
	source = sstream.str();

	return source;
}

GLuint Shader::compileShader(OpenGL* openGL, std::string text, GLenum type)
{
	GLuint compiled = openGL->glCreateShader(type);

	// Compile with openGL by putting in full string of file
	const char* txt = text.c_str();
	openGL->glShaderSource(compiled, 1, &txt, nullptr);
	openGL->glCompileShader(compiled);

	int error;
	char msg[512];

	// Check if everything went ok
	openGL->glGetShaderiv(compiled, GL_COMPILE_STATUS, &error);
	if (!error)
	{
		openGL->glGetShaderInfoLog(compiled, 512, nullptr, msg);
		throw std::runtime_error("Could not compile shader because: " + std::string(msg));
	}

	return compiled;
}