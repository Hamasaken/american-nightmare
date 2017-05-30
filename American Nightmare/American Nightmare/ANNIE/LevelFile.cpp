#include "LevelFile.h"

LLevelHeader::LLevelHeader()
{
	nameSize = NAME_SIZE;
	version = LEVEL_FILE_VERSION;

	nrOfArchives = 0;
	nrOfMeshes = 0;
	nrOfLights = 0;
	nrOfHitboxes = 0;
	nrOfTriggers = 0;
	nrOfSpawners = 0;
	nrOfEffects = 0;

	playerSpawn[0] = 0;
	playerSpawn[1] = 0;
}



LLevelHandler::LLevelHandler()
{
}

LLevelHandler::~LLevelHandler()
{
}



void LLevelHandler::emptyLevel()
{
	levelHeader = LLevelHeader(); //Reset header

	//Clear all vector data
	archives.clear();
	meshes.clear();
	lights.clear();
	hitboxes.clear();
	triggers.clear();
	spawners.clear();
	effects.clear();
}



void LLevelHandler::writeToFile(const char* path) const
{
	//Create file at path
	ofstream out(path, ios::binary);

	//Write header
	out.write(reinterpret_cast<const char*>(&levelHeader), sizeof(LLevelHeader));

	//Write everything (almost)
	out.write(reinterpret_cast<const char*>(archives.data()), sizeof(CharData) * levelHeader.nrOfArchives);
	out.write(reinterpret_cast<const char*>(meshes.data()), sizeof(LMesh) * levelHeader.nrOfMeshes);
	out.write(reinterpret_cast<const char*>(lights.data()), sizeof(LLight) * levelHeader.nrOfLights);
	out.write(reinterpret_cast<const char*>(hitboxes.data()), sizeof(LHitbox) * levelHeader.nrOfHitboxes);

	//Write triggers
	for (int i = 0; i < levelHeader.nrOfTriggers; i++)
	{
		out.write(reinterpret_cast<const char*>(&triggers[i].triggerType), sizeof(ETriggerType));
		out.write(reinterpret_cast<const char*>(&triggers[i].data.size), sizeof(StringData::size));
		out.write(reinterpret_cast<const char*>(triggers[i].data.data.data()), sizeof(char) * triggers[i].data.size);
		out.write(reinterpret_cast<const char*>(&triggers[i].hitbox), sizeof(LHitbox));
	}
	
	//Write spawners
	for (int i = 0; i < levelHeader.nrOfSpawners; i++)
	{
		out.write(reinterpret_cast<const char*>(&spawners[i].spawnerType), sizeof(ESpawnerType));
		out.write(reinterpret_cast<const char*>(&spawners[i].data.size), sizeof(StringData::size));
		out.write(reinterpret_cast<const char*>(spawners[i].data.data.data()), sizeof(char) * spawners[i].data.size);
		out.write(reinterpret_cast<const char*>(&spawners[i].position), sizeof(LSpawner::position));
	}

	//Write effects
	out.write(reinterpret_cast<const char*>(effects.data()), sizeof(LEffect) * levelHeader.nrOfEffects);

	out.close(); //Close the file
}



void LLevelHandler::readFromFile(const char* path)
{
	//Open file at path
	ifstream in(path, ios::binary);

	if (!in.is_open())
	{
		cout << "Error opening the level file!" << endl;
	}
	else
	{
		emptyLevel(); //Empty all arrays
		
		//Read header
		in.read(reinterpret_cast<char*>(&levelHeader), sizeof(LLevelHeader));

		//Read archives
		archives.resize(levelHeader.nrOfArchives);
		in.read((reinterpret_cast<char*>(archives.data())), sizeof(CharData) * levelHeader.nrOfArchives);

		//Read meshes
		meshes.resize(levelHeader.nrOfMeshes);
		in.read((reinterpret_cast<char*>(meshes.data())), sizeof(LMesh) * levelHeader.nrOfMeshes);

		//Read lights
		lights.resize(levelHeader.nrOfLights);
		in.read((reinterpret_cast<char*>(lights.data())), sizeof(LLight) * levelHeader.nrOfLights);

		//Read hitboxes
		hitboxes.resize(levelHeader.nrOfHitboxes);
		in.read((reinterpret_cast<char*>(hitboxes.data())), sizeof(LHitbox) * levelHeader.nrOfHitboxes);

		//Read triggers
		triggers.resize(levelHeader.nrOfTriggers);
		for (int i = 0; i < levelHeader.nrOfTriggers; i++)
		{
			in.read(reinterpret_cast<char*>(&triggers[i].triggerType), sizeof(ETriggerType));
			in.read(reinterpret_cast<char*>(&triggers[i].data.size), sizeof(StringData::size));
			triggers[i].data.data.resize(triggers[i].data.size);
			in.read(reinterpret_cast<char*>(&triggers[i].data.data[0]), sizeof(char) * triggers[i].data.size);
			in.read(reinterpret_cast<char*>(&triggers[i].hitbox), sizeof(LHitbox));
		}

		//Read spawners
		spawners.resize(levelHeader.nrOfSpawners);
		for (int i = 0; i < levelHeader.nrOfSpawners; i++)
		{
			in.read(reinterpret_cast<char*>(&spawners[i].spawnerType), sizeof(ESpawnerType));
			in.read(reinterpret_cast<char*>(&spawners[i].data.size), sizeof(StringData::size));
			spawners[i].data.data.resize(spawners[i].data.size);
			in.read(reinterpret_cast<char*>(&spawners[i].data.data[0]), sizeof(char) * spawners[i].data.size);
			in.read(reinterpret_cast<char*>(&spawners[i].position), sizeof(LSpawner::position));
		}

		//Read effects
		effects.resize(levelHeader.nrOfEffects);
		in.read((reinterpret_cast<char*>(effects.data())), sizeof(LEffect) * levelHeader.nrOfEffects);
	}
}







