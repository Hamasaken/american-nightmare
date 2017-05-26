#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include "../Game/Model.h"
#include "..\Accessories.h"
#include <vector>
#include "../ANNIE/ArchiveFile.h"

class MeshManager
{
public:
	struct Mesh
	{
		std::string name;
		Model* model;

		Mesh(std::string name, Model* model) : name(name), model(model) { };
		Mesh(const Mesh& inMesh) : name(inMesh.name), model(inMesh.model) { };
		~Mesh() 
		{ 
			model->Stop(); 
			delete model; 
		};
	};

public:
	MeshManager();
	MeshManager(const MeshManager& other);
	~MeshManager();

	void Clear();
	bool AddMesh(std::string name, int nrOfVertices, std::vector<AVertex> vertices);

	Mesh* getMesh(std::string name) const;
	std::vector<Mesh*> getMeshList() const;
private:

	void MakeDefaultQuad();
	void MakeDefaultCube();
	void MakeDefaultSphere();

	std::vector<Mesh*> meshList;
};

#endif // !MESHMANAGER_H

