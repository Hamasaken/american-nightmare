#include "QuadTree.h"

QuadTree::QuadTree() 
{
	parent = nullptr;
}

QuadTree::QuadTree(const QuadTree & other) { }

QuadTree::~QuadTree() { }

bool QuadTree::Start(glm::vec2 screenSize)
{	
	// Creating the parent node, containing everything on level
	parent = new Node();
	if (parent == nullptr) return false;

	return true;
}

bool QuadTree::StartTree(Node * node, std::vector<Object*>* objects)
{
	// Calculate origin and dimensions of the full map
	glm::vec2 origin = glm::vec2(0, 0);
	glm::vec2 dimensions = glm::vec2(1000, 1000);

	MakeTree(node, objects, origin, dimensions);

	return true;
}

void QuadTree::Stop()
{
	// Unloading everything inside node
	if (parent != nullptr)
	{
		StopNode(parent);
	}
}

bool QuadTree::IsRectangleInside(glm::vec3 center, glm::vec3 dimensions)
{
	
	return true;
}

void QuadTree::StopNode(Node* node)
{
	// Deleting everything inside the node
	for (int i = 0; i < 4; i++)
	{
		if (node->child[i] != nullptr)
		{
			StopNode(node->child[i]);
		}
	}

	// Deleting this node
	node->Stop();
	delete node;
	node = nullptr;
}

void QuadTree::MakeTree(Node* node, std::vector<Object*>* objects, glm::vec2 parentDimensions, glm::vec2 parentOrigin)
{
	node->dimensions = parentDimensions;
	node->origin = parentOrigin;
	node->objects = objects;
	for (int i = 0; i < 4; i++)
		node->child[i] = nullptr;

	int nrOfObjects = CountObjects(node->origin, node->dimensions);
	if (nrOfObjects == 0) return;
	if (nrOfObjects > QUAD_TREE_MAX_OBJECTS)
	{
		glm::vec2 offset;
		glm::vec2 newPos;
		for (int i = 0; i < 4; i++)
		{
			// Splitting the quad up into four new quads, does not bother changing the Z pos, because of sidescroller
			offset.x = (((i % 2) < 1) ? -1.0f : 1.0f) * (parentDimensions.x / 4.0f);
			offset.y = (((i % 4) < 2) ? -1.0f : 1.0f) * (parentDimensions.y / 4.0f);
			newPos.x = parentOrigin.x + offset.x;
			newPos.y = parentOrigin.y + offset.y;
			
			// Counting objects in specific quad
			nrOfObjects = CountObjects(newPos, (parentDimensions / 2.f));
			if (nrOfObjects > NULL)
			{
				node->child[i] = new Node();
				MakeTree(node->child[i], node->objects, newPos, (parentDimensions / 2.f));
			}
		}

		// Remove objects ptr and returns here, because this quad is only holding children now
		node->objects = nullptr;
		return;
	}
	
	// The fact that we've reached the end means this is the end of a quad splitting, fill this node up remaining objects 
	std::vector<Object*>* finalObjects = new std::vector<Object*>;
	for (Object* object : *node->objects)
	{
		// if (frustum->isBoxInside(node->dimensions, Object->getBoundingBox()))
		finalObjects->push_back(object);
	}
}

int QuadTree::CountObjects(glm::vec2 origin, glm::vec2 dimensions)
{

	return 0;
}

void QuadTree::FindQuadAt(glm::vec2 position, Node * node)
{
}

void QuadTree::Update()
{
	/*
		check with frustum which nodes are inside of screne and update them	
		** dont forget to also check with the player screen
		** to see if the player can also see the object updating, like for example
		** a zombie in inside the visiable quad, but not in the player screen!
	*/
}

void QuadTree::Draw()
{
	/*
		check with frustum which nodes are inside of screne and draw them
		** dont forget to also check with the player screen
	*/
}
