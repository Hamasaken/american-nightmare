#ifndef STRUCTREG_H
#define STRUCTREG_H

#include"MeshManager.h"
#include"MaterialManager.h"

struct ProjectileData
{
	const MeshManager::Mesh* mesh;
	const MaterialManager::Material* material;
	bool isCircle;

	ProjectileData()
	{
	}

	ProjectileData(const MeshManager::Mesh* mesh, const MaterialManager::Material* material, bool isCircle)
	{
		this->mesh = mesh;
		this->material = material;
		this->isCircle = isCircle;
	}
};

#endif // !STRUCTREG_H

