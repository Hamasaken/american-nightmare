#include "ProjectileHandler.h"


ProjectileHandler::ProjectileHandler(b2World *world, GLuint shader, int CAP)
{
	this->dirInt = 0;
	this->myShader = shader;
	this->wasPressed = false;
	this->nrOfBullets = 0;

	//Test for the cursor
	SDL_ShowCursor(SDL_ENABLE);
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	SDL_SetCursor(cursor);
}

ProjectileHandler::ProjectileHandler() {}

ProjectileHandler::~ProjectileHandler()
{
	
}

void ProjectileHandler::Update(GLint deltaT, b2World* world, glm::vec2 position)
{
	this->isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if (isPressed && !wasPressed && nrOfBullets <= 10)
	{
		this->wasPressed = true;
		this->nrOfBullets++;
		myProjtileVector.push_back(new Projectile(world, myShader));
		myProjtileVector.back()->fireBullet(world, position, fromScreenToNDC(glm::vec2(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y), glm::vec2{ 1280, 720 }, glm::vec2{ 320, 180 }));
	}

	for (int i = 0; i < myProjtileVector.size(); i++)
	{
		myProjtileVector[i]->Update(deltaT);
	}

	this->wasPressed = isPressed;
}

std::vector<Projectile*> ProjectileHandler::getBullets()
{
	return myProjtileVector;
}