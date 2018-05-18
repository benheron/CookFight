#pragma once
#include <string>
#include <vector>
#include "Frame.h"


class AnimationType {
public:
	AnimationType(std::string id, std::vector<Frame*> frames);
	~AnimationType();



	Frame* getFrame(int index);
	int getNumFrames();

	std::string getID() { return id; }



private:
	std::string id;
	std::vector<Frame*> frames;

};