#ifndef OBJECT_H
#define OBJECT_H

// Classes
// #include "Texture.h"
#include "Model.h"

class Object
{
public:
	Object();
	Object(const Object& other);
	~Object();

	////////////////////////////////////////////////////////////
	// \brief Loads both a model & texture
	// \return Returns false if one or both fails
	////////////////////////////////////////////////////////////
	virtual bool Start(OpenGL* openGL, std::string modelName, std::string textureName);

	////////////////////////////////////////////////////////////
	// \brief Unloads both model & texture
	////////////////////////////////////////////////////////////
	virtual void Stop();

	////////////////////////////////////////////////////////////
	// \brief Virtual Update function
	////////////////////////////////////////////////////////////
	virtual void Update() = 0;

	////////////////////////////////////////////////////////////
	// \brief Draws the model
	////////////////////////////////////////////////////////////
	virtual void Draw();

	////////////////////////////////////////////////////////////
	// Sets & Gets
	////////////////////////////////////////////////////////////
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition() const;
	void setRotation(glm::vec3 rotation);
	glm::vec3 getRotation() const;
	glm::vec3 getRotationInRadians() const;
	void setScale(glm::vec3 scale);
	glm::vec3 getScale() const;

protected:	// Note: Make this private when loadModel is implemented!
	glm::vec3 position;	//< Object position
	glm::vec3 rotation;	//< Object rotation
	glm::vec3 scale;	//< Object scale
	OpenGL* openGL;		//< OpenGL functions ptr
	Model* model;		//< This object's model
	// Texture* texture;	//< This object's texture 
};


#endif // !OBJECT_H
