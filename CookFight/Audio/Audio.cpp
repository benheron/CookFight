#include "Audio.h"

Audio::Audio(std::string filePath, int type)
{
	if (type == 0)
	{
		loadMusic(filePath);
	}
	else {
		loadSoundEffect(filePath);
	}

	this->type = type;
	volume = 128;
	audioPlaying = false;
	sfxPaused = false;
	sfxChannel = -1;
}

Audio::~Audio()
{
	if (type == 0)
	{
		Mix_FreeMusic(music);
	}
	if (type == 1)
	{
		Mix_FreeChunk(sfx);
	}
}

bool Audio::loadMusic(std::string filePath)
{
	music = Mix_LoadMUS(filePath.c_str());

	
	if (music == NULL)
	{
		//fail
		printf("SDL_Init failed: %s\n", SDL_GetError());
		printf( "Problem trying to load music. \n");
		return false;
	}

	return true;

}

bool Audio::loadSoundEffect(std::string filePath)
{
	sfx = Mix_LoadWAV(filePath.c_str());

	if (sfx == NULL)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		printf("Problem trying to load sound effect. \n");
		return false;
	}

	return true;
}

void Audio::playAudio(int loops)
{
	audioPlaying = true;
	if (type == 0)
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
	else if (type == 1)
	{


		sfxChannel = Mix_PlayChannel(-1, sfx, loops);

		if (sfxChannel == -1)
		{
			printf("Problem trying to play sound. \n");
			audioPlaying = false;
		}
		
	}
	
}

void Audio::stopAudio()
{
	if (type == 0)
	{
		if (audioPlaying)
		{
			if (Mix_HaltMusic() == -1)
			{
				printf("Problem trying to stop sound. \n");
				return;
			}
		}
	}
	else if (type == 1)
	{
		if (audioPlaying)
		{
			if (Mix_HaltChannel(sfxChannel) == -1)
			{
				printf("Problem trying to stop sound. \n");
			}
		}
		
	}
	audioPlaying = false;
}

void Audio::setVolume(int v)
{
	volume = v;
	Mix_Volume(-1, volume);
}

bool Audio::loadSound(std::string filePath)
{
	return false;
}

void Audio::togglePause()
{
	//if (audioPlaying)
	{
		if (type == 0)
		{
			if (Mix_PlayingMusic())
			{
				Mix_PausedMusic() ? Mix_ResumeMusic() : Mix_PauseMusic();
			}
		}
		else if (type == 1 && sfxChannel >=0)
		{
			int pauseVal = Mix_Paused(sfxChannel);
			if (!sfxPaused)
			{
				sfxPaused = true;
				Mix_Pause(sfxChannel);
			}
			else {
				sfxPaused = false;
				Mix_Resume(sfxChannel);
				
			}

			 

			

			printf("Sound effect Paused: %i \n", Mix_Paused(sfxChannel));
		}
	}
	
}

void Audio::pauseAudio()
{
	if (type == 0)
	{
		if (Mix_PlayingMusic())
		{
			Mix_PauseMusic();
		}
	}
	else if (type == 1 && sfxChannel >= 0)
	{
		
		if(!Mix_Paused(sfxChannel))
		{
			Mix_Pause(sfxChannel);
		}
	}
}

void Audio::resumeAudio()
{
	if (type == 0)
	{
		if (Mix_PlayingMusic())
		{
			Mix_ResumeMusic();
		}
	}
	else if (type == 1 && sfxChannel >= 0)
	{
		if (Mix_Paused(sfxChannel))
		{
			Mix_Resume(sfxChannel);
		}
	}
}