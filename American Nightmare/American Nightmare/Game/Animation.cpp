#include "Animation.h"

Animation::Animation() : Entity()
{
	currentAnimation = nullptr;
	currentFrameUV.uvTopLeft = glm::vec2();
	currentFrameUV.uvTopRight = glm::vec2();
	currentFrameUV.uvBotLeft = glm::vec2();
	currentFrameUV.uvBotRight = glm::vec2();
	directionIsRight = true;
	isLooping = true;
	isReversed = false;
}

Animation::Animation(const Animation& other) {}

Animation::~Animation() {}

void Animation::AddAnimation(GLuint textureID, GLuint normalMap, std::string animationFile)
{
	AnimationSegment tempAnimation;

	// Loading animation
	if (!loadAnimation(tempAnimation, animationFile)) { return; }

	// Check if animation already exists
	if (findAnimation(tempAnimation.name) != -1)
	{
		printf("Animation already exists: %s\n", tempAnimation.name);
		return;
	}

	tempAnimation.textureID = textureID;
	tempAnimation.normalID = normalMap;

	// Adding animation to list
	animationList.push_back(tempAnimation);

	// If this is the first animation, set current animation to this animation.
	if (currentAnimation == nullptr)
	{
		currentAnimation = &(animationList[0]);
		currentAnimationIndex = 0;
	}
}

bool Animation::loadAnimation(AnimationSegment &aniSeg, std::string animationFile)
{
	std::ifstream in(animationFile);

	if (!in.is_open())
	{
		printf("Animation file did not load : %s\n", animationFile);
		return false;
	}

	AnimationSegment tempAnimation;
	tempAnimation.currentFrame = 0;

	char buffer[64];

	// Loading in animation to tempAnimation
	while (!in.eof())
	{
		in.getline(buffer, 64);

		if (buffer[0] == '/' && buffer[1] == '/') {}

		else if (buffer[0] == 'n' && buffer[1] == 'a' && buffer[2] == 'm' && buffer[3] == 'e')
		{
			char nameBuffer[64];
			sscanf(buffer, "name %s", &nameBuffer);
			tempAnimation.name = nameBuffer;
		}
		else if (buffer[0] == 't' && buffer[1] == 'f')
		{
			GLint tempTF;
			sscanf_s(buffer, "tf %d", &tempTF);
			tempAnimation.totalFrames = tempTF;
		}
		else if (buffer[0] == 'd' && buffer[1] == 'i' && buffer[2] == 'm')
		{
			GLint tempDX;
			GLint tempDY;
			sscanf_s(buffer, "dim %d %d", &tempDX, &tempDY);
			tempAnimation.dimensions = glm::vec2(tempDX, tempDY);
		}
		else if (buffer[0] == 'f' && buffer[1] == 'p' && buffer[2] && 's')
		{
			GLint tempFPS;
			sscanf_s(buffer, "fps %d", &tempFPS);
			tempAnimation.fps = tempFPS;
		}
	}

	aniSeg = tempAnimation;
	return true;
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

bool Animation::changeActiveAnimation(std::string name)
{
	GLint index = -1;

	index = findAnimation(name);

	if (index != -1)
	{
		currentAnimation->currentFrame = 0;
		currentAnimation = &(animationList[index]);
		currentAnimationIndex = index;
		currentAnimation->currentFrame = 0;
		return true;
	}
	return false;
}

bool Animation::changeActiveAnimation(GLuint index)
{
	if (index < animationList.size())
	{
		currentAnimation->currentFrame = 0;
		currentAnimation = &(animationList[index]);
		currentAnimationIndex = index;
		currentAnimation->currentFrame = 0;
		return true;
	}
	return false;
}

void Animation::updateAnimation(GLfloat deltaT)
{
	// Check if currentAnimation is set
	if (currentAnimation == nullptr)
	{
		printf("No animation is set\n");
		return;
	}

	// Get current frame
	if(!isReversed)
		currentAnimation->currentFrame += 0.001 * deltaT * currentAnimation->fps;
	else
		currentAnimation->currentFrame -= 0.001 * deltaT * currentAnimation->fps;

	// If current frame is above total amount of frames - reset to 0
	if (isLooping)
	{
		if (!isReversed)
		{
			while (currentAnimation->currentFrame >= currentAnimation->totalFrames)
			{
				currentAnimation->currentFrame -= currentAnimation->totalFrames;
			}
		}
		else
			while (currentAnimation->currentFrame <= -1.f)
			{
				currentAnimation->currentFrame += currentAnimation->totalFrames;
			}
	}
	// If the animation shouldn't loop we set it to the last frame of the spritesheet
	else
	{
		if (currentAnimation->currentFrame > currentAnimation->totalFrames)
			currentAnimation->currentFrame = currentAnimation->totalFrames - 1.f;
	}

	// Get size of each frame in 0-1 coords
	glm::vec2 frameSize = glm::vec2(1.f / currentAnimation->dimensions.x, 1.f / currentAnimation->dimensions.y);

	// Get collumn and row for current frame
	GLint currentRow = (int)currentAnimation->currentFrame / (int)currentAnimation->dimensions.x;
	GLint currentCol = (int)currentAnimation->currentFrame % (int)currentAnimation->dimensions.x;

	// Get offset in 0-1 coords for current frame
	glm::vec2 offset = glm::vec2(frameSize.x * currentCol, 1 - (frameSize.y * currentRow));

	// Update UVs
	currentFrameUV.uvBotLeft = glm::vec2(offset.x, offset.y - frameSize.y);
	currentFrameUV.uvBotRight = glm::vec2(offset.x + frameSize.x, offset.y - frameSize.y);
	currentFrameUV.uvTopRight = glm::vec2(offset.x + frameSize.x, offset.y);
	currentFrameUV.uvTopLeft = offset;
}

Animation::FrameUV* Animation::getCurrentFrameUV() { return &currentFrameUV; }

GLuint Animation::getAnimationTexture() const { return currentAnimation->textureID; }
GLuint Animation::getAnimationNormal() const { return currentAnimation->normalID; }
GLuint Animation::getActiveAnimationIndex() const {	return currentAnimationIndex; }

bool Animation::isDirectionRight() { return directionIsRight; }