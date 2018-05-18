#pragma once
#include <string>
#include <vector>
#include "AnimationType.h"

class Animation {
public:
	Animation();
	~Animation();

	void animationInit();

	void update(float dt);

	void setFrameIndex(int index);
	
	Frame* getFrame(int index);
	Frame* getCurrentFrame();

	int getFrameIndex() { return currentFrameIndex; }

	void setAnimationType(AnimationType* anTy); 
	AnimationType* getAnimationType() { return aniType; }

	int getNumFrames();

	void setFrameRate(float fr);
	float getFrameRate();


	void pauseAnimation();
	void playAnimation();

protected:
	AnimationType *aniType;
	int currentFrameIndex;

	float frameRate;

	bool playTheAnimation;

	float frameTimings;
};