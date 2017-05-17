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

	//Write everything
	out.write(reinterpret_cast<const char*>(archives.data()), sizeof(CharData) * levelHeader.nrOfArchives);
	out.write(reinterpret_cast<const char*>(meshes.data()), sizeof(LMesh) * levelHeader.nrOfMeshes);
	out.write(reinterpret_cast<const char*>(lights.data()), sizeof(LLight) * levelHeader.nrOfLights);
	out.write(reinterpret_cast<const char*>(hitboxes.data()), sizeof(LHitbox) * levelHeader.nrOfHitboxes);
	out.write(reinterpret_cast<const char*>(triggers.data()), sizeof(LTrigger) * levelHeader.nrOfTriggers);
	out.write(reinterpret_cast<const char*>(spawners.data()), sizeof(LSpawner) * levelHeader.nrOfSpawners);
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
		in.read((reinterpret_cast<char*>(archives.data())), sizeof(CharData) * levelHeader.nrOfArchives); //&archives[0] doesn't work. WHY???

		//Read meshes
		meshes.resize(levelHeader.nrOfMeshes);
		in.read((reinterpret_cast<char*>(&meshes[0])), sizeof(LMesh) * levelHeader.nrOfMeshes);

		//Read lights
		lights.resize(levelHeader.nrOfLights);
		in.read((reinterpret_cast<char*>(&lights[0])), sizeof(LLight) * levelHeader.nrOfLights);

		//Read hitboxes
		hitboxes.resize(levelHeader.nrOfHitboxes);
		in.read((reinterpret_cast<char*>(&hitboxes[0])), sizeof(LHitbox) * levelHeader.nrOfHitboxes);

		//Read triggers
		triggers.resize(levelHeader.nrOfTriggers);
		in.read((reinterpret_cast<char*>(&triggers[0])), sizeof(LTrigger) * levelHeader.nrOfTriggers);

		//Read spawners
		spawners.resize(levelHeader.nrOfSpawners);
		in.read((reinterpret_cast<char*>(&spawners[0])), sizeof(LSpawner) * levelHeader.nrOfSpawners);

		//Read effects
		effects.resize(levelHeader.nrOfEffects);
		in.read((reinterpret_cast<char*>(&effects[0])), sizeof(LEffect) * levelHeader.nrOfEffects);
	}
}







