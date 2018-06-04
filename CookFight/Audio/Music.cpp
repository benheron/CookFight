#include "Music.h"

Music::Music(std::string filePath) : Audio(filePath, 0)
{

}

Music::~Music()
{
	delete music;
}


bool Music::loadAudio(std::string filePath)
{
	music = Mix_LoadMUS(filePath.c_str());


	if (music == NULL)
	{
		//fail
		printf("SDL_Init failed: %s\n", SDL_GetError());
		printf("Problem trying to load music. \n");
		return false;
	}

	return true;
}

void Music::playAudio(int loops)
{
	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		if (Mix_PlayMusic(music, loops) == -1)
		{
			printf("Problem trying to play sound. \n");
			audioPlaying = false;
		}
	}
}

void Music::stopAudio()
{
	if (Mix_HaltMusic() == -1)
	{
		printf("Problem trying to stop sound. \n");
		return;
	}
}