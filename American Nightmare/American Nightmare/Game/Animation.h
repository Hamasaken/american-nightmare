#ifndef ANIMATION_H
#define ANIMATION_H

#include "Entity.h"
#include <fstream>
#include <sstream>
#include <vector>

class Animation : public Entity
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

	void AddAnimation(GLuint textureID, GLuint normalMap, std::string animationFile);
	FrameUV* getCurrentFrameUV();
	GLuint getAnimationTexture() const;
	GLuint getAnimationNormal() const;
	bool isDirectionRight();

protected:
	bool changeActiveAnimation(std::string name);
	bool changeActiveAnimation(GLuint index);
	void updateAnimation(GLfloat deltaT);
	bool directionIsRight;
	bool isLooping;
private:

	// Holds information about a single animation (for exmaple a jumping animation)
	struct AnimationSegment
	{
		std::string name;
		GLuint textureID;
		GLuint normalID;
		GLint totalFrames;
		glm::vec2 dimensions;
		GLint fps;
		GLfloat currentFrame;

		AnimationSegment() : name("undefined"), textureID(-1), normalID(-1), totalFrames(0), dimensions(glm::vec2()), fps(0), currentFrame(0.f) {}
		AnimationSegment(std::string inName, GLuint textureID, GLuint inNormalID, GLint inTotalFrames, glm::vec2 inDimensions, GLint infps, GLfloat inCurrentFrame)
			: name(inName), textureID(textureID), normalID(inNormalID), totalFrames(inTotalFrames), dimensions(inDimensions), fps(infps), currentFrame(inCurrentFrame) {}
		AnimationSegment(const AnimationSegment& aniSeg) 
			: name(aniSeg.name), textureID(aniSeg.textureID), normalID(aniSeg.normalID), totalFrames(aniSeg.totalFrames), dimensions(aniSeg.dimensions), fps(aniSeg.fps), currentFrame(aniSeg.currentFrame) {}
	};

	GLint findAnimation(std::string name) const;
	bool loadAnimation(AnimationSegment &aniSeg, std::string animationFile);

	std::vector<AnimationSegment> animationList;
	AnimationSegment* currentAnimation;
	FrameUV currentFrameUV;
};

#endif // !ANIMATION_H
