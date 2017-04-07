#include "Screen.h"

Screen::Screen() 
{	
	// Setting ptr's to nullptr
	camera = nullptr;
	openGL = nullptr;
}

Screen::Screen(const Screen & other) { }

Screen::~Screen() { }

bool Screen::Restart()
{
	// Saving pointer to openGL
	OpenGL* ptr = openGL;

	// Unload everything
	Stop();

	// Trying to restart
	if (!Start(ptr))
		return false;

	return true;
}

bool Screen::Start(OpenGL* openGL)
{
	// Saving OpenGL ptr
	this->openGL = openGL;

	// Creating Camera Object
	camera = new Camera();
	if (camera == nullptr) return false;

	return true;
}

void Screen::Stop()
{
	// Deleting camera
	if (camera != nullptr)
	{
		delete camera;
		camera = nullptr;
	}

	// Removing our openGL ptr
	openGL = nullptr;
}
