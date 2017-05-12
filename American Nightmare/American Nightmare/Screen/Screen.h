#ifndef SCREEN_H
#define SCREEN_H

#include "../Game/Camera.h"
#include "../Game/Object.h"
#include "../Game/Animation.h"
#include "../Game/Shader/ShaderManager.h"
#include "Rendering/DeferredRendering.h"
#include "../Game/LightManager.h"
#include "../Screen/Rendering/ShadowManager.h"
#include "../SoundManager.h"
#include "../Game/Particle/ParticleManager.h"
#include "../Game/GUI/Button.h"

class Screen
{
public:
	Screen();
	Screen(const Screen& other);
	~Screen();

	////////////////////////////////////////////////////////////
	// \brief Loads all needed objects, also runs SetStartVariables
	// \return Returrns true if every object could be created
	////////////////////////////////////////////////////////////
	virtual bool Start(glm::vec2 screenSize, glm::vec2 screenPosition, State* state, SoundManager* soundManager);
	
	////////////////////////////////////////////////////////////
	// \brief A combined function that runs both Stop & Start
	// \return Returns true if the Start function returns true
	//	otherwise it returns false
	////////////////////////////////////////////////////////////
	bool Restart();

	////////////////////////////////////////////////////////////
	// \brief Deletes the camera class and removes the openGL ptr
	// \note Use this function last in the Screen's Stop Function
	//	Because we remove the openGL ptr, and we might need it
	//	to delete other stuff
	////////////////////////////////////////////////////////////
	virtual void Stop();

	////////////////////////////////////////////////////////////
	// \brief Initializing starting variables, like camera position
	// \note Should be called in the end of Start function
	////////////////////////////////////////////////////////////
	virtual void SetStartVariables() = 0;

	////////////////////////////////////////////////////////////
	// \brief Updating the screen
	////////////////////////////////////////////////////////////
	virtual void Update(GLint deltaT) = 0;

	////////////////////////////////////////////////////////////
	// \brief Drawing everything on screen
	////////////////////////////////////////////////////////////
	virtual void Draw() = 0;

	////////////////////////////////////////////////////////////
	// \brief Drawing a specific object on screen
	// \note Replace the solid shader with an abstract "Shader" instead
	////////////////////////////////////////////////////////////
	void DrawObject(Object* object, ShaderManager* shaderManager);
	void DrawObjectDirShadowMap(Object* object, ShaderManager* shaderManager, glm::mat4 lightSpaceMatrix);
	void DrawObjectDirShadowMapTransparent(Animation* animatedObj, ShaderManager* shaderManager, glm::mat4 lightSpaceMatrix);
	void DrawObjectPointShadowMap(Object* object, ShaderManager* shaderManager, ShadowManager::PointShadowMap* pointShadowMap);
	void DrawObjectGUI(Object* object, ShaderManager* shaderManager);
	void DrawObjectAnimation(Animation* animatedObj, ShaderManager* shaderManager, std::vector<LightManager::PointLight*> pointLightList, std::vector<LightManager::DirectionalLight*> directionalLightList, std::vector<ShadowManager::DirectionalShadowMap*> directionalShadowMapList, bool useShadow);
	void DrawObjectGeometryPass(Object* object, ShaderManager* shaderManager);
	void DrawObjectLightPass(DeferredRendering* drRendering, ShaderManager* shaderManager, std::vector<LightManager::PointLight*> pointLightList, std::vector<LightManager::DirectionalLight*> directionalLightList, std::vector<ShadowManager::DirectionalShadowMap*> directionalShadowMapList, std::vector<ShadowManager::PointShadowMap*> pointShadowMapList, bool useShadow);
	void DrawParticles(ParticleManager* particleManager, ShaderManager* shaderManager);

protected:
	Camera* camera;	//< Simple Camera object
	SoundManager* soundManager; // Sound Manager
	State* state;

	glm::vec2 screenSize;
	glm::vec2 screenPosition;
	glm::mat4 worldMatrix;
	glm::mat4 projectionMatrix;
};

#endif // !SCREEN_H
