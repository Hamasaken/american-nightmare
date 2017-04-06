#ifndef GAME_H
#define GAME_H

#include "OpenGL.h"
#include "Camera.h"
#include "Model.h"
#include "SolidShader.h"

#define CLEAR_COLOR glm::vec4(0.1f, 0.1, 0.1, 1)

class Game
{
public:
	Game();
	Game(const Game& other);
	~Game();

	bool Start(OpenGL* openGL, HWND hwnd);
	void SetStartVariables();
	void Stop();

	bool Update();
	bool Draw();

private:
	OpenGL* m_openGL;
	SolidShader* m_solidShader;
	Model* m_model;
	Camera* m_camera;
};


#endif // !GRAPHICS_H
