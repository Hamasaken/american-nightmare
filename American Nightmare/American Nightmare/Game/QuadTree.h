#ifndef QUADTREE_H
#define QUADTREE_H

#include "../Accessories.h"
#include "../Game/Object.h"

#define QUAD_TREE_MAX_OBJECTS 2

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
//				for (Object* object : *objects)
//				{
				//	delete object;
				//	object = nullptr;
//				}
			//	delete objects;
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
		glm::vec2 dimensions;
		glm::vec2 origin;
		Node* child[4];
	};

public:
	QuadTree();
	QuadTree(const QuadTree& other);
	~QuadTree();

	bool Start(glm::vec2 screenSize);
	bool StartTree(std::vector<Object*>* objects);
	void Stop();

	void Update();
	void Draw();

private:
	bool IsRectangleInside(glm::vec3 center, glm::vec3 dimensions);
	void StopNode(Node* node);
	void MakeTree(Node* node, std::vector<Object*>* objects, glm::vec2 parentDimensions, glm::vec2 parentOrigin);
	int CountObjects(glm::vec2 origin, glm::vec2 dimensions, std::vector<Object*>* objects);
	void FindQuadAt(glm::vec2 position, Node* node);

	Node* parent;
	glm::vec2 screenSize;
	glm::vec2 dimensions;
};

#endif // !QUADTREE_H

