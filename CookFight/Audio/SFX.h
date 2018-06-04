#pragma once

#include "Audio.h"

class SFX : public Audio
{
public:
	SFX(std::string filePath);
	~SFX();

	virtual void playAudio(int loops);

	virtual void stopAudio();


	virtual bool loadAudio(std::string filePath);




private:
	Mix_Chunk *sfx;

};