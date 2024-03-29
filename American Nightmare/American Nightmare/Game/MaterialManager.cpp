#include "MaterialManager.h"


MaterialManager::MaterialManager() { }

MaterialManager::MaterialManager(const MaterialManager& other) { }

MaterialManager::~MaterialManager() { Clear(); }

void MaterialManager::Clear()
{
	for (int i = 0; i < textureList.size(); i++)
		glDeleteTextures(1, &textureList[i]->textureID);

	for (Material* material : materialList)
		delete material;

	for (Texture* texture : textureList)
		delete texture;

	materialList.clear();
	textureList.clear();
}

bool MaterialManager::AddMaterial(std::string matName, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, GLfloat specularExponent, std::string textureName, std::string texturePath)
{
	// Check if material exists
	if (findMaterial(matName) != -1) return false;

	Material* tempMaterial = new Material();

	tempMaterial->name = matName;
	tempMaterial->ambient = ambient;
	tempMaterial->diffuse = diffuse;
	tempMaterial->specular = specular;
	tempMaterial->specularExponent = specularExponent;

	if (texturePath.size() < 10)
	{
		tempMaterial->texture = textureList[0];
		materialList.push_back(tempMaterial);
		return true;
	}

	// Check if texture exists
	GLint textureIndex = findTexture(textureName);
	if (textureIndex != -1)
	{
		tempMaterial->texture = textureList[textureIndex];
		materialList.push_back(tempMaterial);
		return true;
	}
	else
	{
		textureIndex = AddTexture(textureName, texturePath);
		if (textureIndex != -1)
		{
			tempMaterial->texture = textureList[textureIndex];
			materialList.push_back(tempMaterial);
			return true;
		}
		else
		{
			tempMaterial->texture = textureList[0];
			materialList.push_back(tempMaterial);
			return true;
		}
	}

	return false;
}

GLint MaterialManager::AddTexture(std::string name, std::string texturePath)
{
	GLuint textureID = loadTexture(texturePath);

	if (textureID != 0)
	{
		textureList.push_back(new Texture(name, textureID));
		return textureList.size() - 1;
	}

	return -1;
}

GLuint MaterialManager::loadTexture(std::string inImage)
{
	sf::Image* sfImage = new sf::Image();
	if (!sfImage->loadFromFile(inImage))
	{
		return 0;
	}

	if (sfImage != nullptr)
	{
		GLuint glTexture;

		glGenTextures(1, &glTexture);
		glBindTexture(GL_TEXTURE_2D, glTexture);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sfImage->getSize().x, sfImage->getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, sfImage->getPixelsPtr());

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		sfImage->~Image();
		delete sfImage;

		return glTexture;
	}

	return 0;
}

GLint MaterialManager::findMaterial(std::string name) const
{
	GLint listIndex = -1;

	for (int i = 0; i < materialList.size() && listIndex == -1; i++)
	{
		if (materialList[i]->name == name)
		{
			listIndex = i;
		}
	}

	return listIndex;
}

GLint MaterialManager::findTexture(std::string name) const
{
	GLint listIndex = -1;

	for (int i = 0; i < textureList.size() && listIndex == -1; i++)
	{
		if (textureList[i]->name == name)
		{
			listIndex = i;
		}
	}

	return listIndex;
}

const MaterialManager::Material* MaterialManager::getMaterial(std::string name) const
{
	GLint materialIndex = findMaterial(name);

	if (materialIndex != -1)
		return materialList[materialIndex];

	return nullptr;
}

GLuint MaterialManager::getTextureID(GLint index) const { return textureList[index]->textureID; }

GLuint MaterialManager::getTextureID(std::string name) const
{
	GLint textureIndex = findTexture(name);

	if (textureIndex != -1)
		return textureList[textureIndex]->textureID;

	return -1;
}