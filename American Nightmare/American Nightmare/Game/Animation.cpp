#include "Animation.h"

Animation::Animation() : Object()
{
	currentAnimation = nullptr;
	currentFrameUV.uvTopLeft = glm::vec2();
	currentFrameUV.uvTopRight = glm::vec2();
	currentFrameUV.uvBotLeft = glm::vec2();
	currentFrameUV.uvBotRight = glm::vec2();
}

Animation::Animation(const Animation& other) {}

Animation::~Animation() {}

void Animation::AddAnimation(GLuint texture, std::string animationFile)
{
	AnimationSegment tempAnimation = AnimationSegment();

	// Temporary, load from animationFile
	tempAnimation.name = "test";
	tempAnimation.textureID = texture;
	tempAnimation.totalFrames = 27;
	tempAnimation.dimensions.x = 7;
	tempAnimation.dimensions.y = 4;
	tempAnimation.currentDir = right;
	tempAnimation.fps = 48;
	tempAnimation.currentFrame = 0;

	if (findAnimation(tempAnimation.name) != -1)
	{
		printf("Animation already exists: %s", tempAnimation.name);
		return;
	}

	animationList.push_back(tempAnimation);

	if (currentAnimation == nullptr)
	{
		currentAnimation = &(animationList[0]);
	}

}

GLint Animation::findAnimation(std::string name) const
{
	GLint index = -1;

	for (int i = 0; i < animationList.size() && index == -1; i++)
	{
		if (animationList[i].name == name)
		{
			index = i;
		}
	}

	return index;
}

void Animation::changeActiveAnimation(std::string name)
{
	GLint index = -1;

	index = findAnimation(name);

	if (index != -1)
	{
		currentAnimation->currentFrame = 0;
		currentAnimation = &(animationList[index]);
		currentAnimation->currentFrame = 0;
	}
}

void Animation::updateAnimation(GLfloat deltaT)
{
	// Check if currentAnimation is set
	if (currentAnimation == nullptr)
	{
		printf("No animation is set");
		return;
	}

	// Get current frame
	currentAnimation->currentFrame += 0.001 * deltaT * currentAnimation->fps;

	//printf("currentFrame: %f\n", currentAnimation->currentFrame);

	// If current frame is above total amount of frames - reset to 0
	if (currentAnimation->currentFrame >= currentAnimation->totalFrames)
	{
		currentAnimation->currentFrame = 0.f;
	}

	// Get size of each frame in 0-1 coords
	glm::vec2 frameSize = glm::vec2(1.f / currentAnimation->dimensions.x, 1.f / currentAnimation->dimensions.y);

	// Get collumn and row for current frame
	GLint currentRow = (int)currentAnimation->currentFrame / (int)currentAnimation->dimensions.x;
	GLint currentCol = (int)currentAnimation->currentFrame % (int)currentAnimation->dimensions.x;

	//printf("currentCol: %d", currentCol);

	//printf("currentFrame: %f\n", currentAnimation->currentFrame);

	// Get offset in 0-1 coords for current frame
	glm::vec2 offset = glm::vec2(frameSize.x * currentCol, 1 - (frameSize.y * currentRow));

	// Update UVs
	currentFrameUV.uvBotLeft = glm::vec2(offset.x, offset.y - frameSize.y);
	currentFrameUV.uvBotRight = glm::vec2(offset.x + frameSize.x, offset.y - frameSize.y);
	currentFrameUV.uvTopRight = glm::vec2(offset.x + frameSize.x, offset.y);
	currentFrameUV.uvTopLeft = offset;



}

Animation::FrameUV* Animation::GetCurrentFrameUV()
{
	return &currentFrameUV;
}