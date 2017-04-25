#ifndef OBJECT_H
#define OBJECT_H

// Classes
#include "SFML\Graphics.hpp"
#include "MaterialManager.h"
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
	// \return Returns false if one or both fails
	////////////////////////////////////////////////////////////
	virtual bool Start(std::string modelName, const MaterialManager::Material* material, b2World& world, float x = 0.f, float y = 0.f, bool isDynamic = false);

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
	virtual void setShader(GLuint shader);
	GLuint getShader() const;
	GLuint getTexture() const;
	GLuint getTextureID() const;
	void SetAsBoxbox(float x, float y);


	b2BodyDef bodyDef;
	b2Body* body;

	b2PolygonShape shape;
	b2FixtureDef fixtureDef;

protected:
	glm::vec3 position;	//< Object position
	glm::vec3 rotation;	//< Object rotation
	glm::vec3 scale;	//< Object scale
	GLuint shader;		//< Identifier for shaderprogram to use when drawing

protected:	// Note: Make this private when loadModel is implemented!
	Model* model;	//< This object's model
	GLuint texture;	//< This object's texture 
	const MaterialManager::Material* material; //< This object's material

};


#endif // !OBJECT_H
