#include "SFX.h"

SFX::SFX(std::string filePath) : Audio(filePath, 1)
{

}

SFX::~SFX()
{
	delete sfx;
}


bool SFX::loadAudio(std::string filePath)
{
	sfx = Mix_LoadWAV(filePath.c_str());

	if (sfx == NULL)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		printf("Problem trying to load sound effect. \n");
		return false;
	}
}

void SFX::playAudio(int loops)
{
	if (Mix_PlayChannel(-1, sfx, loops) == -1)
	{
		printf("Problem trying to play sound. \n");
		audioPlaying = false;
	}
}

void SFX::stopAudio()
{
	if (Mix_HaltChannel(-1) == -1)
	{
		printf("Problem trying to stop sound. \n");
	}
}