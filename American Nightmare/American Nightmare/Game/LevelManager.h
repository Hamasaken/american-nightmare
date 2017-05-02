#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "Player.h"
#include "LightManager.h"
#include <vector>
#include <Box2D.h>
#include "../Enemy.h"
#include "../Projectile.h"
#include <Box2D.h>

class LevelManager
{
public:
	LevelManager();
	LevelManager(const LevelManager& other);
	~LevelManager();

	////////////////////////////////////////////////////////////
	// \brief Starts class, gets the openGL ptr
	// \return Returns true if everything went well
	////////////////////////////////////////////////////////////
	bool Start(GLuint playerShader);

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
	bool LoadLevel(GLuint shader, std::string levelFile);
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
	std::vector<Object*> map;	//< Vector with level specific objects
	Player* player;				//< The player object

	Enemy* enemy;				//< A Enemy object

	LightManager* lightManager;
	MaterialManager materialManager;
	b2World *world;

	//ProjectileHandler* myPH;

	Projectile* myProjectile;
	//Projectile* moveble;

};

#endif  !LEVELMANAGER_H
