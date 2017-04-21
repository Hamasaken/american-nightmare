#include "ScreenCutscene.h"
#include <iostream>

ScreenCutscene::ScreenCutscene() : Screen() 
{ 
	model = nullptr;
}

ScreenCutscene::ScreenCutscene(const ScreenCutscene& other) { }

ScreenCutscene::~ScreenCutscene() { }

bool ScreenCutscene::Start(glm::vec2 screenSize, SoundManager* soundManager)
{
	Screen::Start(screenSize, soundManager);

	////////////////////////////////////////////////////////////
	// Starting Model Class
	////////////////////////////////////////////////////////////
	model = new Model();
	if (model == nullptr) return false;
	if (!model->Start("Quad"))
		return false;

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
	// Building basic 1x4 quad for movie to be on
	model->BuildQuadTexture();

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
	// Generating a texture
	glGenTextures(1, &texture);

	// Binding texture
	glBindTexture(GL_TEXTURE_2D, texture);

	// Getting the frame's pixel pointer and setting it into our binded texture ID
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, frame.getSize().x, frame.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, frame.getPixelsPtr());

	// Making mip map and stuff
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Unbinding the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	model->Draw();
}
