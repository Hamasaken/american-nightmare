#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include Object.h
#include ShaderShader.h
#include vector

class LevelManager
{
public
	LevelManager();
	LevelManager(const LevelManager& other);
	~LevelManager();

	bool Start(OpenGL openGL);
	void Stop();

	bool LoadLevel(GLuint shader, stdstring levelFile);

	void Update(sfTime delta);
	void Draw();

	stdvectorObject getMap();

private
	OpenGL openGL;
	stdvectorObject map;
};


#endif  !LEVELMANAGER_H
