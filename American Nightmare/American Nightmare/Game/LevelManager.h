#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "Player.h"
#include "LightManager.h"
#include "Particle\ParticleManager.h"
#include <vector>
#include <Box2D.h>
#include "../Enemy.h"
#include "Trigger.h"
#include "../Projectile.h"
#include "../MyContactListener.h"
#include "../SoundManager.h"
#include "../ANNIE/ArchiveFile.h"
#include "../ANNIE/LevelFile.h"

class LevelManager
{
public:
	LevelManager();
	LevelManager(const LevelManager& other);
	~LevelManager();

	////////////////////////////////////////////////////////////
	// \brief Starts class, gets the openGL ptr
	// \param playerShader The specific shader for the player
	// \param materialManager ptr to all the materials
	// \param particleManager ptr to the particle manager
	// \return Returns true if everything went well
	////////////////////////////////////////////////////////////
	bool Start(GLuint playerShader, MaterialManager* materialManager, ParticleManager* particleManager, SoundManager* soundManager);

	////////////////////////////////////////////////////////////
	// \brief Unloads whole level
	////////////////////////////////////////////////////////////
	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Unloads the map
	////////////////////////////////////////////////////////////
	void StopMap();

	////////////////////////////////////////////////////////////
	// \brief Loads new map objects from a file and setting 
	//	which specific shader to use for all those objects
	// \param shader ID for the shader to be used
	// \param levelFile Only the name of the file (path is already set)
	// \return Returns false if the map could not be loaded, otherwise true
	////////////////////////////////////////////////////////////
	bool LoadLevel(GLuint shader, std::string levelPath);
	void LoadTempLevel(GLuint shader);

	////////////////////////////////////////////////////////////
	// \brief Updates every object on map
	///////////////////////////////////////////////////////////
	void Update(GLint deltaT);

	////////////////////////////////////////////////////////////
	// \brief Get the vector of objects to draw or do something with
	///////////////////////////////////////////////////////////
	std::vector<Object*> getMap();

	const LightManager* getLightManager() const;
	Player* getPlayer();
	Enemy* getEnemy();
	Projectile* getProjectile();
	//ProjectileHandler* getProjectiles();

	//////////////////////////////////////////////////////////////
	// Shoot something
	/////////////////////////////////////////////////////////////
	void shoot(GLuint shader, std::string modelPath);


private:
	////////////////////////////////////////////////////////////
	// \brief Check for action triggers on the map 
	///////////////////////////////////////////////////////////
	void CheckTriggers();

	std::vector<Object*> map;	//< Vector with level specific objects
	std::vector<Hitbox*> hitboxes;
	std::vector<Trigger*> triggers;
	Player* player;				//< The player object

	Enemy* enemy;				//< A Enemy object

	AArchiveHandler archive;
	LLevelHandler levelFile;

	ParticleManager* particleManager;
	SoundManager* soundManager;
	LightManager* lightManager;
	MaterialManager* materialManager;
	b2World *world;
	MyContactListener contactManager;

	//ProjectileHandler* myPH;

	Projectile* myProjectile;
	//Projectile* moveble;

};

#endif  !LEVELMANAGER_H
