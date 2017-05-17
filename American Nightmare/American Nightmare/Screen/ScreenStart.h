#ifndef SCREENSTART_H
#define SCREENSTART_H

#include "Screen.h"
#include "../Game/GUI/GUIManager.h"
#include "../Game/MaterialManager.h"
#include "../Game/Particle/ParticleManager.h"

#define CLEAR_COLOR glm::vec4(1, 1, 1, 1)

class ScreenStart : public Screen
{
public:
	ScreenStart();
	ScreenStart(const ScreenStart& other);
	~ScreenStart();

	////////////////////////////////////////////////////////////
	// \brief Loads Screen specific things like buttons/logo
	////////////////////////////////////////////////////////////
	bool Start(glm::vec2 screenSize, glm::vec2 screenPosition, State* state, SoundManager* soundManager);

	////////////////////////////////////////////////////////////
	// \brief Unloads Screen specific things like buttons/logo
	////////////////////////////////////////////////////////////
	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Setting GUI positions 
	////////////////////////////////////////////////////////////
	void SetStartVariables();

	////////////////////////////////////////////////////////////
	// \brief Look for mouse-presses and button hovers 
	////////////////////////////////////////////////////////////
	void Update(GLint deltaT);

	////////////////////////////////////////////////////////////
	// \brief Draw full start meny
	////////////////////////////////////////////////////////////
	void Draw();

private:
	MeshManager* meshManager;			//< Mesh Manager
	MaterialManager* materialManager;	//< Materials & Textures
	GUIManager* guiManager;				//< Buttons & Text
	ShaderManager* shaderManager;		//< Shader Manager
	ParticleManager* particleManager;	//< Manager for particle effects
};

#endif // !SCREENSTART_H
