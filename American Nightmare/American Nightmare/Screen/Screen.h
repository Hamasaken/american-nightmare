#ifndef SCREEN_H
#define SCREEN_H

#include "../OpenGL.h"
#include "../Game/Camera.h"
#include "../Game/Object.h"
#include "../Game/Shader/Shader.h"	// temporary, replace this with abstract shader
#include "../Game/Shader/ShaderManager.h"

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
	virtual bool Start(OpenGL* openGL);
	
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
	virtual void Update() = 0;

	////////////////////////////////////////////////////////////
	// \brief Drawing everything on screen
	////////////////////////////////////////////////////////////
	virtual void Draw() = 0;

	////////////////////////////////////////////////////////////
	// \brief Drawing a specific object on screen
	// \note Replace the solid shader with an abstract "Shader" instead
	////////////////////////////////////////////////////////////
	void DrawObject(Object* object, ShaderManager* shader);

protected:
	Camera* camera;	//< Simple Camera object
	OpenGL* openGL;	//< Ptr to OpenGL functions
};

#endif // !SCREEN_H
