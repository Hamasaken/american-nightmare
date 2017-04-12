#include "ScreenCutscene.h"

ScreenCutscene::ScreenCutscene() : Screen() { }

ScreenCutscene::ScreenCutscene(const ScreenCutscene& other) { }

ScreenCutscene::~ScreenCutscene() { }

bool ScreenCutscene::Start()
{
	Screen::Start();

	// Initialize movie stuff

	SetStartVariables();

	return true;
}

void ScreenCutscene::Stop()
{
	Screen::Stop();

	// Unload movie
}

bool ScreenCutscene::StartCutscene(std::string movieName)
{
	return false;
}

void ScreenCutscene::SetStartVariables()
{
	// Set variables
}

void ScreenCutscene::Update()
{

}

void ScreenCutscene::Draw()
{

}
