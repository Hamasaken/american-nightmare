#ifndef PROGRAH
#define PROGRAH

// PRE-PROCESS
#define WIN32_LEAN_AND_MEAN // to exclude useless includes (for this project) to speed up things

// INCLUDES
#include "Screen\ScreenManager.h"
#include <SFML\Window.hpp>
#include <SFML\Window\Keyboard.hpp>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_syswm.h>

// DEFINES
#define APP_NAME			"American Nightmare"
#define FULL_SCREEN_ON		false
#define SHOW_CURSOR			true
#define DEFAULT_SCREEN_SIZE	glm::vec2(1920, 1080)
#define SCREEN_DEPTH		50.f
#define SCREEN_NEAR			0.1f
#define VSYNC_ON			true

class Program
{
public:
	Program();
	Program(const Program& other);
	~Program();

	////////////////////////////////////////////////////////////
	// \brief Starting window & then enters the game loop
	////////////////////////////////////////////////////////////
	bool Start();

	////////////////////////////////////////////////////////////
	// \brief Unloads everything in the program
	////////////////////////////////////////////////////////////
	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Game loop function!
	// \return Returns false when we exit in any way
	////////////////////////////////////////////////////////////
	bool Run();

private:
	
	// Windows
	void StartSDLWindow();
	void StopWindow();

	// Update
	bool Update(GLint deltaT);

	SDL_Window* window;		//< SDL window
	SDL_GLContext context;
	ScreenManager* screenManager;	//< ScreenManager, hold everything game/meny based
	std::string appName;		//< Application name
	HINSTANCE hInstance;		//< hInstance
	HWND hwnd;					//< Windowhandle from SDL window
	glm::vec2 screenSize;		//< Screensize in (x,y)
	int posX, posY;				//< Screen Position in (x,y)


	/*SDL_Cursor* cursor;*/
};

#endif // !PROGRAM