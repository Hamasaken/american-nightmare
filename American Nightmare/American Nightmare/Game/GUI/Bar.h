#ifndef BAR_H
#define BAR_H

#include "../Object.h"

class Bar : public Object
{
public:
	Bar();
	Bar(const Bar& other);
	~Bar();
	//
	////////////////////////////////////////////////////////////
	// \brief Starts a bar
	// \param The value that this bar is looking at and updating from
	// \param The maximum value of the value that the bar is looking at
	// \param position Position of the center position of the button
	// \param size Size of the bar & quad
	// \param material The material of this bar (no path needed)
	// \param mesh The mesh of this bar (leave as nullptr for normal quad)
	// \return Returns false if model or font could not be created
	////////////////////////////////////////////////////////////
	bool Start(float &value, float maxValue, glm::vec3 position, glm::vec2 size, const MaterialManager::Material* material, const MeshManager::Mesh* mesh);
	void Stop();

	////////////////////////////////////////////////////////////
	// \brief Updates button by checking if increasing/decreasing and changing value
	// \param deltaT The time between each frame in milliseconds
	////////////////////////////////////////////////////////////
	void Update(GLfloat deltaT);

	////////////////////////////////////////////////////////////
	// \brief Draws the model and the text on top
	////////////////////////////////////////////////////////////
	void Draw();

	// Set & Get functions
	glm::vec3 getStartPosition();
	int getProcent();

private:
	float* value;			//< The value this bar is looking at with the actual value
	float maxValue;			//< The value this bar is looking at but the 100% value
	float procent;			//< From 0% --> 100%
	float showProcent;		//< The visual bit of the procent, should be a bit slower.. because it looks better
	State state;			//< Current state of the bar
	glm::vec3 startPosition;//< The starting position of this bar
	glm::vec2 startSize;	//< The starting size of this bar
};

#endif // !BAR_H
