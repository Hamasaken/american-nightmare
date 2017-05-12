#pragma once
#include <cstdint>
#include <vector>

#include "Header.h"

/****************************************************************************************
*
*	Copyright (C) 2017 David Wistrand & Emma Henriksson
*	All rights reserved. Do not distribute.
*
*	American Nightmare Native Importer/Exporter (ANNIE)
*	is protected by copyright law.
*
****************************************************************************************/


enum EMaterialType
{
	eMaterialLambert,
	eMaterialPhong
};

enum ELightType
{
	ePoint,
	eDirectional,
	eSpot
};

enum EDecayType
{
	eNone,
	eLinear,
	eQuadratic,
	eCubic
};





struct Identifier
{
	char name[NAME_SIZE];
	uint16_t uid;
};




struct ATexture
{
	Identifier identifier;

	uint16_t pathLength;
	string texturePath;
};

struct AMaterial
{
	Identifier identifier;
	EMaterialType materialType;

	Identifier diffuseMap;
	Identifier normalMap;
	Identifier specularMap;

	float diffuse[3];
	float ambient[3];
	float emissive[3];
	float specular[3];

	float opacity;
	float shininess;
	float reflectionFactor;
};




struct ALight
{
	Identifier identifier;

	ELightType lightType;
	EDecayType decayType;

	float color[3];
	float intensity;
};

struct ACamera
{
	Identifier identifier;

	float roll;
	float fieldOfView;
	float nearPlane;
	float FarPlane;
	float focalLength;

	float interestPos[3];
	float upDirection[3];
};




struct AVertex
{
	float position[3];
	float uv[2];
	float normal[3];
	float tangent[3];
	float binormal[3];
};

struct AMesh
{
	Identifier identifier;
	Identifier material;
	bool binormals;

	uint32_t nrOfVerticies;

	vector<AVertex> vertices;
};





struct AArchiveHeader
{
	uint8_t nameSize;
	uint16_t version;

	uint16_t uid;
	uint16_t nextID;

	uint16_t nrOfMeshes;
	uint16_t nrOfCameras;
	uint16_t nrOfLights;

	uint16_t nrOfMaterials;
	uint16_t nrOfTextures;

	AArchiveHeader();
};


class AArchiveHandler
{
public:
	AArchiveHeader archiveHeader;
	
	vector<AMesh> meshes; //Varying sizes
	vector<ATexture> textures; //Varying sizes
	vector<AMaterial> materials;
	vector<ACamera> cameras;
	vector<ALight> lights;


	AArchiveHandler();
	~AArchiveHandler();

	
	const uint16_t getUniqueID();

	const AMesh* getMesh(const uint16_t uid) const;
	const AMesh* getMesh(const char* name) const;

	const ATexture* getTexture(const uint16_t uid) const;
	const ATexture* getTexture(const char* name) const;

	const AMaterial* getMaterial(const uint16_t uid) const;
	const AMaterial* getMaterial(const char* name) const;

	const ACamera* getCamera(const uint16_t uid) const;
	const ACamera* getCamera(const char* name) const;

	const ALight* getLight(const uint16_t uid) const;
	const ALight* getLight(const char* name) const;



	void emptyArchive();

	void writeToFile(const char* path) const;

	void readFromFile(const char* path);
};


