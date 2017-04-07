#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "Screen.h"
#include "../Game/Player.h"
#include "../Game/Shader/SolidShader.h"

#define CLEAR_COLOR glm::vec4(0.1f, 0.1, 0.1, 1)

class ScreenGame : public Screen
{
public:
	ScreenGame();
	ScreenGame(const ScreenGame& other);
	~ScreenGame();

	////////////////////////////////////////////////////////////
	// \brief Loads everything related to the playable game
	// \return Returns false if any object could not be loaded
	////////////////////////////////////////////////////////////
	bool Start(OpenGL* openGL);

	////////////////////////////////////////////////////////////
	// \brief Unloads everything related to this screen 
	////////////////////////////////////////////////////////////
	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Set hardcoded stuff (camera start, ui)
	////////////////////////////////////////////////////////////
	void SetStartVariables();

	////////////////////////////////////////////////////////////
	// \brief Update game screen
	////////////////////////////////////////////////////////////
	void Update();

	////////////////////////////////////////////////////////////
	// \brief Draw game screen 
	////////////////////////////////////////////////////////////
	void Draw();

private:
	SolidShader* solidShader;	//< Temporary Color Shader (Replace this with a shaderManager as fast as possible)
	Player* player;			//< The player object
	Object* wall;			//< Background Wall (Temporary, just to see the camera movement)
	Object* floor;
};

#endif // !SCREENGAME_H
