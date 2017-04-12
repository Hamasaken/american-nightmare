#ifndef ANIMATION_H
#define ANIMATION_H

#include "Object.h"
#include <fstream>
#include <sstream>
#include <vector>

#define ANIMATION_PATH ""

class Animation : public Object
{
public:
	Animation();
	Animation(const Animation& other);
	~Animation();

	struct FrameUV
	{
		glm::vec2 uvTopLeft;
		glm::vec2 uvTopRight;
		glm::vec2 uvBotLeft;
		glm::vec2 uvBotRight;
	};

	void AddAnimation(GLuint texture, std::string animationFile);
	FrameUV* GetCurrentFrameUV();

protected:
	void changeActiveAnimation(std::string name);
	void updateAnimation(GLfloat deltaT);

private:
	enum AnimationDirection
	{
		right,
		left
	};

	struct AnimationSegment
	{
		std::string name;
		GLuint textureID;
		GLint totalFrames;
		glm::vec2 dimensions;
		AnimationDirection currentDir;
		GLint fps;
		GLfloat currentFrame;

		AnimationSegment() : name("undefined"), textureID(-1), totalFrames(0), dimensions(glm::vec2()), currentDir(right), fps(0), currentFrame(0.f) {}
		AnimationSegment(std::string inName, GLuint inTextureID, GLint inTotalFrames, glm::vec2 inDimensions, AnimationDirection inCurrentDir, GLint infps, GLfloat inCurrentFrame) 
			: name(inName), textureID(inTextureID), totalFrames(inTotalFrames), dimensions(inDimensions), currentDir(inCurrentDir), fps(infps), currentFrame(inCurrentFrame) {}
		AnimationSegment(const AnimationSegment& aniSeg) 
			: name(aniSeg.name), textureID(aniSeg.textureID), totalFrames(aniSeg.totalFrames), dimensions(aniSeg.dimensions), currentDir(aniSeg.currentDir), fps(aniSeg.fps), currentFrame(aniSeg.currentFrame) {}
	};

	GLint findAnimation(std::string name) const;

	std::vector<AnimationSegment> animationList;
	AnimationSegment* currentAnimation;
	FrameUV currentFrameUV;
};

#endif // !ANIMATION_H