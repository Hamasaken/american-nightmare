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

	bool Start();
	void Stop();

	// Game-loop function
	bool Run();

private:
	
	// Initializing window
	void StartSFMLWindow();
	bool StartWindow();
	void StopWindow();

	// Updating everything
	bool Update();

	sf::Window* window;
	OpenGL* openGL;
	ScreenManager* screenManager;
	std::wstring appName;
	HINSTANCE hInstance;
	HWND hwnd;
	glm::vec2 screenSize;
};

// Window Proc Func
static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam);
static Program* pgr = nullptr;

#endif // !PROGRAM