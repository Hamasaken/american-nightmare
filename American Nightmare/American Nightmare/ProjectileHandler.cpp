#include "ProjectileHandler.h"


ProjectileHandler::ProjectileHandler(b2World *world, GLuint shader, int CAP)
{
	this->dirInt = 0;
	this->myShader = shader;
	this->wasPressed = false;
	

	//Test for the cursor
	SDL_ShowCursor(SDL_ENABLE);
	cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
	SDL_SetCursor(cursor);

	
	//this->tempProj = new Projectile(world, myShader);
	//myProjtileVector.push_back(tempProj);
}

ProjectileHandler::ProjectileHandler() {}

ProjectileHandler::~ProjectileHandler()
{
	//for (int i = 0; i < myProjtileVector.size(); i++)
	//myProjtileVector[i] = myProjtileVector.erase();
}

void ProjectileHandler::Update(GLint deltaT, b2World* world, glm::vec2 position)
{
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	//{
	//	myProjtileVector.push_back(new Projectile(world, myShader));
	//	dirInt = 1;
	//	myProjtileVector.back()->fireBullet(world, position, dirInt);
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	//{
	//	myProjtileVector.push_back(new Projectile(world, myShader));
	//	dirInt = 2;
	//	myProjtileVector.back()->fireBullet(world, position, dirInt);
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	//{
	//	myProjtileVector.push_back(new Projectile(world, myShader));
	//	dirInt = 3;
	//	myProjtileVector.back()->fireBullet(world, position, dirInt);
	//}
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	//{
	//	myProjtileVector.push_back(new Projectile(world, myShader));
	//	dirInt = 4;
	//	myProjtileVector.back()->fireBullet(world, position, dirInt);
	//}


	this->isPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if (isPressed && !wasPressed)
	{
		this->wasPressed = true;
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