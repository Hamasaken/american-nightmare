#ifndef GAME_H
#define GAME_H

#include "OpenGL.h"
#include "Game\Camera.h"
#include "Game\Model.h"
#include "Game\SolidShader.h"

#define SHADER_PATH "Data/Graphics/Shaders/"
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
	OpenGL* openGL;
	SolidShader* solidShader;
	Model* model;
	Camera* camera;
};


#endif // !GRAPHICS_H
