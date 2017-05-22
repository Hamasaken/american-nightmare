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
	virtual void setPosition(glm::vec3 position);
	virtual void setRotation(glm::vec3 rotation);
	virtual void setScale(glm::vec3 scale);
	virtual void setShader(GLuint shader);
	glm::vec3 getPosition() const;
	glm::vec3 getCenter() const;
	glm::vec3 getRotation() const;
	glm::vec3 getScale() const;
	GLuint getShader() const;
	GLuint getTextureID() const;
	const MaterialManager::Material* getMaterial() const;
	void setMaterial(const MaterialManager::Material* material);

protected:
	glm::vec3 position;	//< Object position
	glm::vec3 rotation;	//< Object rotation
	glm::vec3 scale;	//< Object scale
	GLuint shader;		//< Identifier for shaderprogram to use when drawing

protected:	// Note: Make this private when loadModel is implemented!
	Model* model;	//< This object's model
	const MaterialManager::Material* material; //< This object's material
};

class Poster : public Object
{ public: void Update(GLint deltaT) { rotation.z += 0.025f; } };

#endif // !OBJECT_H
