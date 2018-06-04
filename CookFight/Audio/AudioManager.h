#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "Audio.h"

class AudioManager {
public:

	AudioManager(std::string filePath);
	~AudioManager();

	bool loadAudio(std::string filePath);

	Audio* getSFXByID(std::string id);
	Audio* getSFXByName(std::string id);
	Audio* getSFXByIndex(int index);

	Audio* getMusicByID(std::string id);
	Audio* getMusicByName(std::string id);
	Audio* getMusicByIndex(int index);

protected:
	std::unordered_map<std::string, Audio*> soundEffectsID;
	std::unordered_map<std::string, Audio*> soundEffectsString;
	std::vector<Audio*> soundEffectsList;

	std::unordered_map<std::string, Audio*> bgMusicID;
	std::unordered_map<std::string, Audio*> bgMusicString;
	std::vector<Audio*> bgMusicList;
};