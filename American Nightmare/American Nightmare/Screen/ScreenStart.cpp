#include "ScreenStart.h"

ScreenStart::ScreenStart() : Screen()
{

}

ScreenStart::ScreenStart(const ScreenStart& other) { }

ScreenStart::~ScreenStart() { }

bool ScreenStart::Start()
{
	Screen::Start();

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

void ScreenStart::Update(GLint deltaT)
{
	// Checking button stuff and that stuff 
}

void ScreenStart::Draw()
{
	camera->buildViewMatrix();

	// - Drawing buttons

}

void ScreenStart::Stop()
{
	// Delete GUI
	// --

	// Deletes Camera & OpenGL ptr
	Screen::Stop();
}
