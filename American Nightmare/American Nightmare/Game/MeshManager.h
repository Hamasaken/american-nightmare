#ifndef MESHMANAGER_H
#define MESHMANAGER_H

#include "../Game/Model.h"
#include "..\Accessories.h"
#include <vector>

class MeshManager
{
public:
	struct Mesh
	{
		std::string name;
		Model* model;

		Mesh() : name(""), model(nullptr) { };
		Mesh(std::string name, Model* model) : name(name), model(model) { };
		Mesh(const Mesh& inMesh) : name(inMesh.name), model(inMesh.model) { };
	};

public:
	MeshManager();
	MeshManager(const MeshManager& other);
	~MeshManager();

	void Clear();
	void AddMesh(std::string name, std::string meshPath);

	std::vector<Model*> getMeshList() const;
private:
	std::vector<Model*> meshList;
};

#endif // !MESHMANAGER_H

