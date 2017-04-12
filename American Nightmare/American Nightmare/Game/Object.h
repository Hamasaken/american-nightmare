#ifndef OBJECT_H
#define OBJECT_H

// Classes
#include "SFML\Graphics.hpp"
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
	virtual bool Start(std::string modelName, std::string textureName);

	////////////////////////////////////////////////////////////
	// \brief Unloads both model & texture
	////////////////////////////////////////////////////////////
	virtual void Stop();

	////////////////////////////////////////////////////////////
	// \brief Virtual Update function
	////////////////////////////////////////////////////////////
	virtual void Update(GLint deltaT);

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
	void setShader(GLuint shader);
	GLuint getShader() const;
	GLuint getTexture() const;

protected:
	glm::vec3 position;	//< Object position
	glm::vec3 rotation;	//< Object rotation
	glm::vec3 scale;	//< Object scale
	GLuint shader;		//< Identifier for shaderprogram to use when drawing

	GLuint loadTexture(std::string inImage); //< 

protected:	// Note: Make this private when loadModel is implemented!
	;		//< OpenGL functions ptr
	Model* model;		//< This object's model
	GLuint texture;	//< This object's texture 
};


#endif // !OBJECT_H
