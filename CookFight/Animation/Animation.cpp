#include "Animation.h"
Animation::Animation()
{
	animationInit();
}

Animation::~Animation()
{

}

void Animation::animationInit()
{
	currentFrameIndex = 0;
	playTheAnimation = false;
	frameTimings = 0;
	frameRate = 30;
}

void Animation::update(float dt)
{

	//update animation
	if (playTheAnimation)
	{
		//add the time between the last frame
		frameTimings+= dt;

	

		//if more than the frame rate of the animation
		if (frameTimings > (1.f / frameRate))
		{
			//change to next frame
			currentFrameIndex++;
			frameTimings = 0;

			//if frame is beyond the max frames, reset to 0
			if (currentFrameIndex > (aniType->getNumFrames()-1))
			{
				currentFrameIndex = 0;
			}
		}
	}
}

void Animation::setFrameIndex(int index)
{
	currentFrameIndex = index; 
	
	if (currentFrameIndex > (aniType->getNumFrames() - 1))
	{
		currentFrameIndex = 0;
	}
}

Frame* Animation::getCurrentFrame()
{
	return aniType->getFrame(currentFrameIndex);
}

Frame* Animation::getFrame(int index)
{
	return aniType->getFrame(index);
}

void Animation::setAnimationType(AnimationType* anTy)
{
	currentFrameIndex = 0;
	aniType = anTy;
}

int Animation::getNumFrames()
{
	return aniType->getNumFrames();
}

void Animation::pauseAnimation() {

}

void Animation::playAnimation()
{
	playTheAnimation = true;
}

void Animation::setFrameRate(float fr)
{
	frameRate = fr;
}

float Animation::getFrameRate()
{
	return frameRate;
}

