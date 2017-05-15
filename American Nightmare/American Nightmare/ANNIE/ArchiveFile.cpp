#include "ArchiveFile.h"


AArchiveHeader::AArchiveHeader()
{
	nameSize = NAME_SIZE;
	version = ARCHIVE_FILE_VERSION;

	
	srand(time(NULL));
	uid = rand() % 65036 + 500; //The 500 first uid's are reserved
	nextID = 1; //Slot 0 is reserved

	nrOfMeshes = 0;
	nrOfCameras = 0;
	nrOfLights = 0;

	nrOfMaterials = 0;
	nrOfTextures = 0;
}

AArchiveHandler::AArchiveHandler()
{
}

AArchiveHandler::~AArchiveHandler()
{
}




const uint16_t AArchiveHandler::getUniqueID()
{
	return archiveHeader.nextID++;
}


const AMesh* AArchiveHandler::getMesh(const uint16_t uid) const
{
	for (int i = 0; i < meshes.size(); i++)
	{
		if (meshes[i].identifier.uid == uid)
		{
			return &meshes[i];
		}
	}
	return nullptr;
}
const AMesh* AArchiveHandler::getMesh(const char* name) const
{
	for (int i = 0; i < meshes.size(); i++)
	{
		if (meshes[i].identifier.name == name)
		{
			return &meshes[i];
		}
	}
	return nullptr;
}


const ATexture* AArchiveHandler::getTexture(const uint16_t uid) const
{
	for (int i = 0; i < textures.size(); i++)
	{
		if (textures[i].identifier.uid == uid)
		{
			return &textures[i];
		}
	}
	return nullptr;
}
const ATexture* AArchiveHandler::getTexture(const char* name) const
{
	for (int i = 0; i < textures.size(); i++)
	{
		if (textures[i].identifier.name == name)
		{
			return &textures[i];
		}
	}
	return nullptr;
}


const AMaterial* AArchiveHandler::getMaterial(const uint16_t uid) const
{
	for (int i = 0; i < materials.size(); i++)
	{
		if (materials[i].identifier.uid == uid)
		{
			return &materials[i];
		}
	}
	return nullptr;
}
const AMaterial* AArchiveHandler::getMaterial(const char* name) const
{
	for (int i = 0; i < materials.size(); i++)
	{
		if (materials[i].identifier.name == name)
		{
			return &materials[i];
		}
	}
	return nullptr;
}


const ACamera* AArchiveHandler::getCamera(const uint16_t uid) const
{
	for (int i = 0; i < cameras.size(); i++)
	{
		if (cameras[i].identifier.uid == uid)
		{
			return &cameras[i];
		}
	}
	return nullptr;
}
const ACamera* AArchiveHandler::getCamera(const char* name) const
{
	for (int i = 0; i < cameras.size(); i++)
	{
		if (cameras[i].identifier.name == name)
		{
			return &cameras[i];
		}
	}
	return nullptr;
}


const ALight* AArchiveHandler::getLight(const uint16_t uid) const
{
	for (int i = 0; i < lights.size(); i++)
	{
		if (lights[i].identifier.uid == uid)
		{
			return &lights[i];
		}
	}
	return nullptr;
}
const ALight* AArchiveHandler::getLight(const char* name) const
{
	for (int i = 0; i < lights.size(); i++)
	{
		if (lights[i].identifier.name == name)
		{
			return &lights[i];
		}
	}
	return nullptr;
}




void AArchiveHandler::emptyArchive()
{
	archiveHeader = AArchiveHeader(); //Reset header

	//Clear all vector data
	meshes.clear();
	textures.clear();
	materials.clear();
	cameras.clear();
	lights.clear();
}


void AArchiveHandler::writeToFile(const char* path) const
{
	//Create file at path
	ofstream out(path, ios::binary);

	//Write header
	out.write(reinterpret_cast<const char*>(&archiveHeader), sizeof(AArchiveHeader));

	//Write all meshes
	for (int i = 0; i < archiveHeader.nrOfMeshes; i++)
	{
		out.write(reinterpret_cast<const char*>(&meshes[i].identifier), sizeof(Identifier));
		out.write(reinterpret_cast<const char*>(&meshes[i].material), sizeof(Identifier));
		out.write(reinterpret_cast<const char*>(&meshes[i].binormals), sizeof(bool));
		out.write(reinterpret_cast<const char*>(&meshes[i].nrOfVerticies), sizeof(uint32_t));

		//Write all verticies
		out.write(reinterpret_cast<const char*>(meshes[i].vertices.data()), sizeof(AVertex) * meshes[i].nrOfVerticies);
	}

	//Write all textures
	for (int i = 0; i < archiveHeader.nrOfTextures; i++)
	{
		out.write(reinterpret_cast<const char*>(&textures[i].identifier), sizeof(Identifier));
		out.write(reinterpret_cast<const char*>(&textures[i].pathLength), sizeof(uint16_t));

		//Write entire path string
		out.write(reinterpret_cast<const char*>(textures[i].texturePath.data()), sizeof(char) * textures[i].pathLength);
	}

	//Write all materials
	out.write(reinterpret_cast<const char*>(materials.data()), sizeof(AMaterial) * archiveHeader.nrOfMaterials);
	
	//Write all cameras
	out.write(reinterpret_cast<const char*>(cameras.data()), sizeof(ACamera) * archiveHeader.nrOfCameras);
	
	//Write all lights
	out.write(reinterpret_cast<const char*>(lights.data()), sizeof(ALight) * archiveHeader.nrOfLights);

	out.close(); //Close the file
}



void AArchiveHandler::readFromFile(const char* path)
{	
	//Open file at path
	ifstream in(path, ios::binary);

	if (!in.is_open())
	{
		cout << "Error opening the archive file!" << endl;
	}
	else
	{
		emptyArchive(); //Empty all arrays

		//Read header
		in.read(reinterpret_cast<char*>(&archiveHeader), sizeof(AArchiveHeader));

		//Read all meshes
		for (int i = 0; i < archiveHeader.nrOfMeshes; i++)
		{
			AMesh tempMesh;

			in.read(reinterpret_cast<char*>(&tempMesh.identifier), sizeof(Identifier));
			in.read(reinterpret_cast<char*>(&tempMesh.material), sizeof(Identifier));
			in.read(reinterpret_cast<char*>(&tempMesh.binormals), sizeof(bool));
			in.read(reinterpret_cast<char*>(&tempMesh.nrOfVerticies), sizeof(uint32_t));

			//Read all verticies
			tempMesh.vertices.resize(tempMesh.nrOfVerticies);
			in.read(reinterpret_cast<char*>(&tempMesh.vertices[0]), sizeof(AVertex) * tempMesh.nrOfVerticies);

			meshes.push_back(tempMesh);
		}

		//Read all textures
		for (int i = 0; i < archiveHeader.nrOfTextures; i++)
		{
			ATexture tempTexture;

			in.read(reinterpret_cast<char*>(&tempTexture.identifier), sizeof(Identifier));
			in.read(reinterpret_cast<char*>(&tempTexture.pathLength), sizeof(uint16_t));

			//Read entire path string
			tempTexture.texturePath.resize(tempTexture.pathLength);
			in.read(&tempTexture.texturePath[0], sizeof(char) * tempTexture.pathLength);

			textures.push_back(tempTexture);
		}

		//Read all materials
		materials.resize(archiveHeader.nrOfMaterials);
		in.read((reinterpret_cast<char*>(materials.data())), sizeof(AMaterial) * archiveHeader.nrOfMaterials);

		//Read all cameras
		cameras.resize(archiveHeader.nrOfCameras);
		in.read(reinterpret_cast<char*>(cameras.data()), sizeof(ACamera) * archiveHeader.nrOfCameras);

		//Read all lights
		lights.resize(archiveHeader.nrOfLights);
		in.read(reinterpret_cast<char*>(&lights[0]), sizeof(ALight) * archiveHeader.nrOfLights);
	}
}



