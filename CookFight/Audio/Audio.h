#pragma once
#include <iostream>
#include <SDL_mixer.h>


class Audio
{
public:
	Audio(std::string filePath, int type);
	~Audio();

	virtual void playAudio(int loops);

	virtual void stopAudio();

	virtual void togglePause();

	virtual void pauseAudio();

	virtual void resumeAudio();


	virtual bool loadSound(std::string filePath);

	bool loadMusic(std::string filePath);

	bool loadSoundEffect(std::string filePath);

	void setVolume(int v);

	bool isPlaying() { return audioPlaying; }

	int getType() { return type; }

	int getSFXChannel() { return sfxChannel; }

	bool setPlaybackSpeed();

protected:
	Mix_Music *music;
	Mix_Chunk *sfx;

	int type;

	int volume;

	bool audioPlaying;

	int sfxChannel;

	bool sfxPaused;
};