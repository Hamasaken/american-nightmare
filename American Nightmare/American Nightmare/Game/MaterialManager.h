#ifndef MATERIALMANAGER_H
#define MATERIALMANAGER_H

#include "..\Accessories.h"
#include "SFML\Graphics.hpp"
#include <vector>



class MaterialManager
{
public:
	struct Texture;

	struct Material
	{
		std::string name; //temp identifier

		glm::vec3 ambient;
		GLfloat specular;

		Texture* texture;

		Material() : name(""), ambient(glm::vec3(0)), specular(0.f), texture(nullptr) { };
		Material(std::string name, glm::vec3 ambient, GLfloat specular, Texture* texture) : name(name), ambient(ambient), specular(specular), texture(texture) { };
		Material(const Material& inMaterial) : name(inMaterial.name), ambient(inMaterial.ambient), specular(inMaterial.specular), texture(inMaterial.texture) { };
		GLuint getTextureID() const { return texture->textureID; }
	};

	MaterialManager();
	MaterialManager(const MaterialManager& other);
	~MaterialManager();

	void Clear();

	bool AddMaterial(std::string matName, glm::vec3 ambient, GLfloat specular, std::string textureName, std::string texturePath);
	GLint AddTexture(std::string name, std::string texturePath);	// Returns index for the added texture in textureList
	const Material* getMaterial(std::string name) const;
	GLuint getTextureID(GLint index) const;
	GLuint getTextureID(std::string name) const;

private:
	struct Texture
	{
		std::string name; // temp identifier
		GLuint textureID;

		Texture() : name(""), textureID(0) { };
		Texture(std::string name, GLuint textureID) : name(name), textureID(textureID) { };
		Texture(const Texture& inTexture) : name(inTexture.name), textureID(inTexture.textureID) { };
	};

	GLuint loadTexture(std::string inImage);						// Return identifier for glTexture that was created
	GLint findMaterial(std::string name) const;						// Returns index for material in materialList
	GLint findTexture(std::string name) const;						// Returns index for texture in textureList

	std::vector<Material*> materialList;
	std::vector<Texture*> textureList;
};

#endif // !MATERIALMANAGER_H
