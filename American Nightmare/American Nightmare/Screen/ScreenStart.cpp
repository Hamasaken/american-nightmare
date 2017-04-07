#include "ScreenStart.h"

ScreenStart::ScreenStart() : Screen()
{

}

ScreenStart::ScreenStart(const ScreenStart& other) { }

ScreenStart::~ScreenStart() { }

bool ScreenStart::Start(OpenGL * openGL)
{
	Screen::Start(openGL);

	// Loading GUI
	// --

	SetStartVariables();

	return true;
}

void ScreenStart::SetStartVariables()
{
	// Backing the camera a little bit backwards
	camera->setPosition(glm::vec3(0, 0, 10));
}

void ScreenStart::Update()
{
	// Checking button stuff and that stuff 
}

void ScreenStart::Draw()
{
	// Starting draw section
	openGL->StartDraw(CLEAR_COLOR);
	camera->buildViewMatrix();

	// - Drawing buttons

	// Ending Draw section
	openGL->EndDraw();
}

void ScreenStart::Stop()
{
	// Delete GUI
	// --

	// Deletes Camera & OpenGL ptr
	Screen::Stop();
}
