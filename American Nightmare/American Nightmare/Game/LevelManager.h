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
#include "MeshManager.h"
#include "QuadTree.h"
#include "EntityManager.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

class LevelManager
{
public:
	LevelManager();
	LevelManager(const LevelManager& other);
	~LevelManager();

	////////////////////////////////////////////////////////////
	// \brief Starts class, gets the openGL ptr
	// \param screenSize For optimazition
	// \param playerShader The specific shader for the player
	// \param mapShader The specific shader for the whole map
	// \param materialManager ptr to all the materials
	// \param meshManager ptr to all the meshes
	// \param particleManager ptr to the particle manager
	// \return Returns true if everything went well
	////////////////////////////////////////////////////////////
	bool Start(glm::vec2 screenSize, GLuint playerShader, GLuint mapShader, MaterialManager* materialManager, MeshManager* meshManager, ParticleManager* particleManager, SoundManager* soundManager, Camera* camera);

	////////////////////////////////////////////////////////////
	// \brief Unloads whole level
	////////////////////////////////////////////////////////////
	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Unloads the map
	////////////////////////////////////////////////////////////
	void StopMap();

	////////////////////////////////////////////////////////////
	// \brief Loads new map objects from a file 
	// \param levelFile Only the name of the file (.anl)
	// \param archiveFile Only the name of the archive file (.ana)
	// \return Returns false if the map could not be loaded, otherwise true
	////////////////////////////////////////////////////////////
	bool LoadLevel(std::string levelPath, std::string archivePath);
	void LoadTempLevel();

	////////////////////////////////////////////////////////////
	// \brief Updates every object on map
	///////////////////////////////////////////////////////////
	void Update(GLint deltaT);

	////////////////////////////////////////////////////////////
	// \brief Get the vector of objects to draw or do something with
	///////////////////////////////////////////////////////////
	std::vector<Object*> getMap();
	//std::vector<Projectile*> getProj();
	std::vector<Projectile*> getProjectiles();

	const LightManager* getLightManager() const;
	EntityManager* getEntityManager();
	Player* getPlayer();
	//Projectile* getProjectile();
	//ProjectileHandler* getProjectiles();

	//////////////////////////////////////////////////////////////
	// Shoot something
	/////////////////////////////////////////////////////////////

private:
	////////////////////////////////////////////////////////////
	// \brief Check for action triggers on the map 
	///////////////////////////////////////////////////////////
	void CheckTriggers();

	// Archive
	void LoadArchiveMeshes(std::vector<AMesh> meshes);
	void LoadArchiveMaterials(std::vector<AMaterial> materials);
	void LoadArchiveTextures(std::vector<ATexture> textures);

	// Level
	void LoadLevelMeshes(std::vector<LMesh> meshes);
	void LoadLevelHitboxes(std::vector<LHitbox> hitboxes);
	void LoadLevelLights(std::vector<LLight> lights);
	void LoadLevelSpawners(std::vector<LSpawner> spawner);
	void LoadLevelTriggers(std::vector<LTrigger> triggers);
	void LoadLevelEffects(std::vector<LEffect> effects);
	
	// Unlock a poster
	void UnlockPoster(int index);

	std::vector<Object*> map;	//< Vector with level specific objects
	std::vector<Hitbox*> hitboxes;
	std::vector<Trigger*> triggers;
	std::vector<Projectile*> projectiles;
	Player* player;				//< The player object

	AArchiveHandler archive;
	LLevelHandler levelFile;
	EntityManager* entityManager;
	MeshManager* meshManager;
	ParticleManager* particleManager;
	SoundManager* soundManager;
	LightManager* lightManager;
	MaterialManager* materialManager;
	b2World *world;
	MyContactListener contactManager;
	QuadTree* quadTree;
	Camera* camera;

	GLuint mapShader;
	GLuint playerShader;

	//ProjectileHandler* myPH;
	//ProjectileHandler* myPH;
	//Projectile* myProjectile;
	Projectile* moveble;

	void deleteProjects(b2World* world);

};

#endif  !LEVELMANAGER_H
