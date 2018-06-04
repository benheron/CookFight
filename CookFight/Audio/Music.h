#pragma once

#include "Audio.h"

class Music : public Audio
{
public:
	Music(std::string filePath);
	~Music();

	virtual void playAudio(int loops);

	virtual void stopAudio();


	virtual bool loadAudio(std::string filePath);





private:
	Mix_Music *music;

};