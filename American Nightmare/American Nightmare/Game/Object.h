#ifndef OBJECT_H
#define OBJECT_H

// Classes
#include "SFML\Graphics.hpp"
#include "MaterialManager.h"
#include "MeshManager.h"
#include "Model.h"
#include "Box2D.h"

class Object
{
public:
	Object();
	Object(const Object& other);
	~Object();

	////////////////////////////////////////////////////////////
	// \brief Loads both a model & texture
	// \param mesh The specific mesh to be created (if nullptr, a quad is created)
	// \param material The specific material on this mesh
	// \return Returns false if one or both fails
	////////////////////////////////////////////////////////////
	virtual bool Start(const MeshManager::Mesh* mesh, const MaterialManager::Material* material);

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
	glm::vec3 getCenter() const;
	void setRotation(glm::vec3 rotation);
	glm::vec3 getRotation() const;
	virtual void setScale(glm::vec3 scale);
	glm::vec3 getScale() const;
	virtual void setShader(GLuint shader);
	GLuint getShader() const;
	GLuint getTextureID() const;

protected:
	glm::vec3 position;	//< Object position
	glm::vec3 rotation;	//< Object rotation
	glm::vec3 scale;	//< Object scale
	GLuint shader;		//< Identifier for shaderprogram to use when drawing

protected:	// Note: Make this private when loadModel is implemented!
	Model* model;	//< This object's model
	const MaterialManager::Material* material; //< This object's material
};


#endif // !OBJECT_H
