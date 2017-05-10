#include "ScreenCutscene.h"
#include <iostream>

ScreenCutscene::ScreenCutscene() : Screen() 
{ 

}

ScreenCutscene::ScreenCutscene(const ScreenCutscene& other) { }

ScreenCutscene::~ScreenCutscene() { }

bool ScreenCutscene::Start(glm::vec2 screenSize, glm::vec2 screenPosition, State* state, SoundManager* soundManager)
{
	Screen::Start(screenSize, screenPosition, state, soundManager);

	SetStartVariables();

	return true;
}

void ScreenCutscene::Stop()
{
	Screen::Stop();
}

bool ScreenCutscene::StartCutscene(std::string movieName)
{
	std::string cutScenePath = CUTSCENE_PATH;

	std::cout << "Loading movie file: " << cutScenePath + movieName << std::endl;

	/*if (!movie.openFromFile(cutScenePath + movieName))
	{

	}*/

	//movie.setPosition(0, 0);
	//movie.play();

	return true;
}

void ScreenCutscene::SetStartVariables()
{
	// Starting cutscene
	StartCutscene("nope.mp4");
}

void ScreenCutscene::Update(GLint deltaT)
{
	// Just temporary keyboundings
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) Restart();
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) SkipCutscene();

	// Getting the current frame as an sf::Image
	//sf::Texture texture = movie.getCurrentImage();
	//frame = texture.copyToImage();
}

void ScreenCutscene::SkipCutscene()
{
}

void ScreenCutscene::Draw()
{

}
