#ifndef QUADTREE_H
#define QUADTREE_H

// #include "Frustum.h"
#include "../Accessories.h"
#include "../Game/Object.h"

#define QUAD_TREE_MAX_OBJECTS 5

class QuadTree
{
private:
	struct Node 
	{
		Node()
		{
			for (int i = 0; i < 4; i++)
				child[i] = nullptr;
		}

		void Stop()
		{
			if (objects != nullptr)
			{
				for (Object* object : *objects)
				{
					object->Stop();
					delete object;
					object = nullptr;
				}
				delete objects;
				objects = nullptr;
			}
		}

		void Update(GLfloat deltaT)
		{
			for (Object* object : *objects)
				object->Update(deltaT);
		}

		void Draw()
		{
			for (Object* object : *objects)
				object->Draw();
		}

		std::vector<Object*>* objects;
		glm::vec3 dimensions;
		glm::vec3 origin;
		Node* child[4];
	};

public:
	QuadTree();
	QuadTree(const QuadTree& other);
	~QuadTree();

	bool Start(glm::vec3 origin, glm::vec3 dimensions, std::vector<Object*>* objects);
	void Stop();

	void Update();
	void Draw();

private:
	void StopNode(Node* node);
	void MakeTree(Node* node, std::vector<Object*>* objects, glm::vec3 parentDimensions, glm::vec3 parentOrigin);
	int CountObjects(glm::vec3 origin, glm::vec3 dimensions);
	void FindQuadAt(glm::vec3 position, Node* node);

	Node* parent;
	// Frustum* frustum;
};

#endif // !QUADTREE_H

