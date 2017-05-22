#include "ShaderManager.h"

ShaderManager::ShaderManager() { }

ShaderManager::ShaderManager(const ShaderManager& other) { }

ShaderManager::~ShaderManager() { }

void ShaderManager::Start() { currentShaderProgram = -1; }

void ShaderManager::Stop()
{
	glUseProgram(0);
	// Deleting shader programs
	while (shaderList.size() > 0)
	{
		glDeleteProgram(shaderList.back().id);
		shaderList.pop_back();
	}
}

void ShaderManager::AddShader(std::string name, std::string vs, std::string fs)
{
	// Reads the file and puts everything into buffer
	std::string vertexShaderBuffer = getSource(vs);
	std::string fragmentShaderBuffer = getSource(fs);

	// Create the shader variables
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Compile the files
	vertexShader = compileShader(vertexShaderBuffer, GL_VERTEX_SHADER);
	fragmentShader = compileShader(fragmentShaderBuffer, GL_FRAGMENT_SHADER);

	// Create the program
	GLuint shaderProgram = glCreateProgram();

	// Attach shaders
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Attributes locations
	glBindAttribLocation(shaderProgram, 0, "inputPosition");
	glBindAttribLocation(shaderProgram, 1, "inputColor");

	// Link program
	glLinkProgram(shaderProgram);

	// Add program to vector
	shaderList.push_back(ShaderProgram(name, shaderProgram));

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void ShaderManager::AddShader(std::string name, std::string vs, std::string gs, std::string fs)
{
	// Reads the file and puts everything into buffer
	std::string vertexShaderBuffer = getSource(vs);
	std::string geometryShaderBuffer = getSource(gs);
	std::string fragmentShaderBuffer = getSource(fs);

	// Create the shader variables
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Compile the files
	vertexShader = compileShader(vertexShaderBuffer, GL_VERTEX_SHADER);
	geometryShader = compileShader(geometryShaderBuffer, GL_GEOMETRY_SHADER);
	fragmentShader = compileShader(fragmentShaderBuffer, GL_FRAGMENT_SHADER);

	// Create the program
	GLuint shaderProgram = glCreateProgram();

	// Attach shaders
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, geometryShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Link program
	glLinkProgram(shaderProgram);

	// Add program to vector
	shaderList.push_back(ShaderProgram(name, shaderProgram));

	glDetachShader(shaderProgram, vertexShader);
	glDetachShader(shaderProgram, geometryShader);
	glDetachShader(shaderProgram, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);
}

void ShaderManager::setShader(GLuint shaderProgram)
{
	// Setting shader program
	glUseProgram(shaderProgram);
	currentShaderProgram = shaderProgram;
}

bool ShaderManager::setShader(std::string name)
{
	// Setting shader program

	GLuint shaderProgram = findShader(name);

	if (shaderProgram != -1)
	{
		glUseProgram(shaderProgram);
		currentShaderProgram = shaderProgram;
		return true;
	}
		
	return false;
}

GLuint ShaderManager::getShader() const
{
	return currentShaderProgram;
}

GLuint ShaderManager::getShader(std::string name) const
{
	return findShader(name);
}

std::string ShaderManager::getShader(GLuint id) const
{
	return findShader(id);
}

bool ShaderManager::SetParameters(glm::mat4 world, glm::mat4 view, glm::mat4 projection)
{
	// Loading uniforms
	GLuint location = NULL;
	GLboolean transpose = GL_FALSE;

	// Loading world matrix (We first find the position and then put it in that position!)
	location = glGetUniformLocation(currentShaderProgram, "world");
	if (location == -1) return false;
	glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(world));

	// Loading view matrix
	location = glGetUniformLocation(currentShaderProgram, "view");
	if (location == -1) return false;
	glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(view));

	// Loading projection matrix
	location = glGetUniformLocation(currentShaderProgram, "projection");
	if (location == -1) return false;
	glUniformMatrix4fv(location, 1, transpose, glm::value_ptr(projection));

	return true;
}

bool ShaderManager::SetParametersAnimated(Animation* character)
{
	GLuint location = NULL;
	Animation::FrameUV* tempFrameUV = character->getCurrentFrameUV();

	// Loading top left uv
	location = glGetUniformLocation(character->getShader(), "uvTopLeft");
	if (location == -1) return false;
	glUniform2f(location, tempFrameUV->uvTopLeft.x, tempFrameUV->uvTopLeft.y);

	// Loading top right uv
	location = glGetUniformLocation(character->getShader(), "uvTopRight");
	if (location == -1) return false;
	glUniform2f(location, tempFrameUV->uvTopRight.x, tempFrameUV->uvTopRight.y);

	// Loading bot left uv
	location = glGetUniformLocation(character->getShader(), "uvBotLeft");
	if (location == -1) return false;
	glUniform2f(location, tempFrameUV->uvBotLeft.x, tempFrameUV->uvBotLeft.y);

	// Loading bot right uv
	location = glGetUniformLocation(character->getShader(), "uvBotRight");
	if (location == -1) return false;
	glUniform2f(location, tempFrameUV->uvBotRight.x, tempFrameUV->uvBotRight.y);

	// Loading direction of animation
	location = glGetUniformLocation(character->getShader(), "isRight");
	if (location == -1) return false;
	glUniform1i(location, character->isDirectionRight());

	return true;
}

GLint ShaderManager::findShader(std::string name) const
{
	GLint shaderProgram = -1;

	for (int i = 0; i < shaderList.size() && shaderProgram == -1; i++)
	{
		if (shaderList[i].name == name)
		{
			shaderProgram = shaderList[i].id;
		}
	}

	return shaderProgram;
}

std::string ShaderManager::findShader(GLuint id) const
{
	std::string shaderProgram = "unknownshader";

	for (int i = 0; i < shaderList.size() && shaderProgram == "unknownshader"; i++)
	{
		if (shaderList[i].id == id)
		{
			shaderProgram = shaderList[i].name;
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

GLuint ShaderManager::compileShader(std::string text, GLenum type)
{
	GLuint compiled = glCreateShader(type);

	const char* txt = text.c_str();
	glShaderSource(compiled, 1, &txt, nullptr);
	glCompileShader(compiled);

	int error;
	char msg[512];

	// Check if everything went ok
	glGetShaderiv(compiled, GL_COMPILE_STATUS, &error);
	if (!error)
	{
		glGetShaderInfoLog(compiled, 512, nullptr, msg);
		printf("Shader could not complile because: \n%s", std::string(msg));
		throw std::runtime_error("Could not compile shader because: " + std::string(msg));
	}

	return compiled;
}