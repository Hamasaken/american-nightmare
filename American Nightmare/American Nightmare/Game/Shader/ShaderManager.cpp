#include "ShaderManager.h"

ShaderManager::ShaderManager() { }

ShaderManager::ShaderManager(const ShaderManager& other) { }

ShaderManager::~ShaderManager() { }

void ShaderManager::Start(OpenGL* openGL) { currentShaderProgram = -1; }

void ShaderManager::Stop(OpenGL* openGL)
{
	// Deleting shader programs
	while (shaderList.size() > 0)
	{
		openGL->glDeleteProgram(shaderList.back().id);
		shaderList.pop_back();
	}
}

void ShaderManager::AddShader(OpenGL* openGL, std::string name, std::string vs, std::string fs)
{
	// Reads the file and puts everything into buffer
	std::string vertexShaderBuffer = getSource(vs);
	std::string fragmentShaderBuffer = getSource(fs);

	// Create the shader variables
	GLuint vertexShader = openGL->glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = openGL->glCreateShader(GL_FRAGMENT_SHADER);

	// Compile the files
	vertexShader = compileShader(openGL, vertexShaderBuffer, GL_VERTEX_SHADER);
	fragmentShader = compileShader(openGL, fragmentShaderBuffer, GL_FRAGMENT_SHADER);

	// Create the program
	GLuint shaderProgram = openGL->glCreateProgram();

	// Attach shaders
	openGL->glAttachShader(shaderProgram, vertexShader);
	openGL->glAttachShader(shaderProgram, fragmentShader);

	// Link program
	openGL->glLinkProgram(shaderProgram);

	// Add program to vector
	shaderList.push_back(ShaderProgram(name, shaderProgram));

	openGL->glDetachShader(shaderProgram, vertexShader);
	openGL->glDetachShader(shaderProgram, fragmentShader);
	openGL->glDeleteShader(vertexShader);
	openGL->glDeleteShader(fragmentShader);
}

void ShaderManager::AddShader(OpenGL* openGL, std::string name, std::string vs, std::string gs, std::string fs)
{
	// Reads the file and puts everything into buffer
	std::string vertexShaderBuffer = getSource(vs);
	std::string geometryShaderBuffer = getSource(gs);
	std::string fragmentShaderBuffer = getSource(fs);

	// Create the shader variables
	GLuint vertexShader = openGL->glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = openGL->glCreateShader(GL_FRAGMENT_SHADER);

	// Compile the files
	vertexShader = compileShader(openGL, vertexShaderBuffer, GL_VERTEX_SHADER);
	fragmentShader = compileShader(openGL, fragmentShaderBuffer, GL_FRAGMENT_SHADER);

	// Create the program
	GLuint shaderProgram = openGL->glCreateProgram();

	// Attach shaders
	openGL->glAttachShader(shaderProgram, vertexShader);
	openGL->glAttachShader(shaderProgram, fragmentShader);

	// Link program
	openGL->glLinkProgram(shaderProgram);

	// Add program to vector
	shaderList.push_back(ShaderProgram(name, shaderProgram));

	openGL->glDetachShader(shaderProgram, vertexShader);
	openGL->glDetachShader(shaderProgram, fragmentShader);
	openGL->glDeleteShader(vertexShader);
	openGL->glDeleteShader(fragmentShader);
}

void ShaderManager::SetShader(OpenGL* openGL, GLuint shaderProgram)
{
	// Setting shader program
	openGL->glUseProgram(shaderProgram);
	currentShaderProgram = shaderProgram;
}

bool ShaderManager::SetShader(OpenGL* openGL, std::string name)
{
	// Setting shader program

	GLuint shaderProgram = findShader(name);

	if (shaderProgram != -1)
	{
		openGL->glUseProgram(shaderProgram);
		currentShaderProgram = shaderProgram;
		return true;
	}
		
	return false;
}

GLuint ShaderManager::GetShader() const
{
	return currentShaderProgram;
}

GLuint ShaderManager::GetShader(std::string name) const
{
	return findShader(name);
}

bool ShaderManager::SetParameters(OpenGL* openGL, glm::mat4 world, glm::mat4 view, glm::mat4 projection)
{
	// Loading uniforms
	GLuint location = NULL;
	GLboolean transpose = GL_FALSE;

	// Loading world matrix (We first find the position and then put it in that position!)
	location = openGL->glGetUniformLocation(currentShaderProgram, "world");
	if (location == -1) return false;
	openGL->glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(world));

	// Loading view matrix
	location = openGL->glGetUniformLocation(currentShaderProgram, "view");
	if (location == -1) return false;
	openGL->glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(view));

	// Loading projection matrix
	location = openGL->glGetUniformLocation(currentShaderProgram, "projection");
	if (location == -1) return false;
	openGL->glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(projection));

	return true;
}

GLuint ShaderManager::findShader(std::string name) const
{
	GLuint shaderProgram = -1;

	for (int i = 0; i < shaderList.size() && shaderProgram == -1; i++)
	{
		if (shaderList[i].name == name)
		{
			shaderProgram = shaderList[i].id;
		}
	}

	return shaderProgram;
}

std::string ShaderManager::getSource(std::string path)
{
	std::stringstream sstream;
	std::ifstream file(path);
	std::string source;

	if (!file.is_open())
		throw std::runtime_error("Could not read shader at: " + path);

	sstream << file.rdbuf();
	source = sstream.str();

	return source;
}

GLuint ShaderManager::compileShader(OpenGL* openGL, std::string text, GLenum type)
{
	GLuint compiled = openGL->glCreateShader(type);

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