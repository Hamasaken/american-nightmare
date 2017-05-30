#pragma once

#include "Header.h"


enum class ETriggerType
{
	door,
	deathZone,
	poster,
	garbageBin,
	message
};

enum class ESpawnerType
{
	zombie1,
	zombie2,
	skater1,
	flying1,
	trash,
	box
};

enum class EEffectType
{
	smoke,
	steam,
	dust
};



struct StringData
{
	uint16_t size;
	string data;
};

struct CharData
{
	char data[NAME_SIZE];
};




struct LMesh
{
	CharData name;

	float position[3];
	float rotation[3];
	float scale[3];
};

struct LLight
{
	CharData name;

	float position[3];
	float rotation[3];
};



struct LHitbox
{
	float position[2];
	float rotation;
	float scale[2];
};




struct LTrigger
{
	ETriggerType triggerType;
	StringData data;

	LHitbox hitbox;
};


struct LSpawner
{
	ESpawnerType spawnerType;
	StringData data;

	float position[2];
};

struct LEffect
{
	EEffectType effectType;

	float position[2];
};




struct LLevelHeader
{
	uint8_t nameSize;
	uint16_t version;

	uint32_t nrOfArchives;
	uint32_t nrOfMeshes;
	uint32_t nrOfLights;
	uint32_t nrOfHitboxes;
	uint32_t nrOfTriggers;
	uint32_t nrOfSpawners;
	uint32_t nrOfEffects;

	float playerSpawn[2];

	LLevelHeader();
};

class LLevelHandler
{
public:
	LLevelHeader levelHeader;

	vector<CharData> archives;

	vector<LMesh> meshes;
	vector<LLight> lights;
	vector<LHitbox> hitboxes;
	vector<LTrigger> triggers;
	vector<LSpawner> spawners;
	vector<LEffect> effects;


	LLevelHandler();
	~LLevelHandler();

	void emptyLevel();

	void writeToFile(const char* path) const;
	void readFromFile(const char* path);
};




