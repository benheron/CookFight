#include "AnimationType.h"
AnimationType::AnimationType(std::string id, std::vector<Frame*> frames) : id(id), frames(frames)
{

}

AnimationType::~AnimationType()
{

}

Frame* AnimationType::getFrame(int index)
{
	return frames[index];
}

int AnimationType::getNumFrames()
{
	return frames.size();
}