#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "Object.h"
#include "../Game/Shader/Shader.h"
#include <vector>

class LevelManager
{
public:
	LevelManager();
	LevelManager(const LevelManager& other);
	~LevelManager();

	bool Start(OpenGL* openGL);
	void Stop();

	bool LoadLevel(GLuint shader, std::string levelFile);

	void Update(sf::Time delta);
	void Draw();

	std::vector<Object*> getMap();

private:
	OpenGL* openGL;
	std::vector<Object*> map;
};


#endif  !LEVELMANAGER_H
