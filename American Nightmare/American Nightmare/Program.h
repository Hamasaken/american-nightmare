#ifndef PROGRAH
#define PROGRAH

// PRE-PROCESS
#define WIN32_LEAN_AND_MEAN // to exclude useless includes (for this project) to speed up things

// INCLUDES
#include "Screen\ScreenManager.h"
#include "OpenGL.h"
#include <SFML\Window.hpp>
#include <SFML\Window\Keyboard.hpp>

// DEFINES
#define APP_NAME		L"American Nightmare"
#define FULL_SCREEN_ON		true
#define SHOW_CURSOR		true
#define DEFAULT_SCREEN_SIZE	glm::vec2(1140, 800)
#define SCREEN_DEPTH		50.f
#define SCREEN_NEAR		0.1f
#define VSYNC_ON		true

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
	void StartSFMLWindow();
	bool StartWindow();
	void StopWindow();

	// Update
	bool Update();

	sf::Window* window;		//< SFML window (not active atm)
	OpenGL* openGL;			//< OpenGL pointer
	ScreenManager* screenManager;	//< ScreenManager, hold everything game/meny based
	std::wstring appName;		//< Application name
	HINSTANCE hInstance;		//< hInstance
	HWND hwnd;			//< Window created by StartWindow
	glm::vec2 screenSize;		//< Screensize in (x,y)
};

// Window Proc Func
static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
static Program* pgr = nullptr;

#endif // !PROGRAM