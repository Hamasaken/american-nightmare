#ifndef SCREENGAME_H
#define SCREENGAME_H

#include "Screen.h"
#include "Rendering/DeferredRendering.h"
#include "../Game/Player.h"
#include "../Game/LevelManager.h"
#include "../Game/Particle/ParticleManager.h"
#include "../Game/GUI/GUIManager.h"

#define CLEAR_COLOR glm::vec4(0.1f, 0.1, 0.1, 1)
#define PAUS_TIMER 500.f // 0.5 sec

class ScreenGame : public Screen
{
private:
	enum GameState { PAUSED, PAUSING, UNPAUSING, PLAYING };
public:
	ScreenGame();
	ScreenGame(const ScreenGame& other);
	~ScreenGame();

	////////////////////////////////////////////////////////////
	// \brief Loads everything related to the playable game
	// \return Returns false if any object could not be loaded
	////////////////////////////////////////////////////////////
	bool Start(glm::vec2 screenSize, glm::vec2 screenPosition, State* state, SoundManager* soundManager);

	////////////////////////////////////////////////////////////
	// \brief Unloads everything related to this screen 
	////////////////////////////////////////////////////////////
	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Set hardcoded stuff (camera start, ui)
	////////////////////////////////////////////////////////////
	void SetStartVariables();

	////////////////////////////////////////////////////////////
	// \brief Update game screen
	////////////////////////////////////////////////////////////
	void Update(GLint deltaT);

	////////////////////////////////////////////////////////////
	// \brief Draw game screen 
	////////////////////////////////////////////////////////////
	void Draw();

private:
	void UpdatePaused(GLint deltaT);
	void UpdatePlaying(GLint deltaT);
	void UpdatePausing(GLint deltaT);
	void UpdateUnpausing(GLint deltaT);

	MaterialManager* materialManager;	//< The material manager
	GameState gameState;				//< Current State of the gameloop
	GUIManager* guiManager;				//< Paus Meny
	ParticleManager* particleManager;	//< Manager for particle effects
	ShaderManager* shaderManager;		//< Manager for shaderprograms
	LevelManager* levelManager;			//< Manager for levels/maps
	DeferredRendering drRendering;		//< Holds framebuffer for deferred rendering
};

#endif // !SCREENGAME_H
