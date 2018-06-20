#include "AudioManager.h"

AudioManager::AudioManager(std::string filePath)
{
	loadAudio(filePath);
}

AudioManager::~AudioManager()
{
	for (int i = 0; i < soundEffectsList.size(); i++)
	{
		delete soundEffectsList[i];
	}
	soundEffectsList.clear();
	soundEffectsID.clear();
	soundEffectsString.clear();

	for (int i = 0; i < bgMusicList.size(); i++)
	{
		delete bgMusicList[i];
	}
	bgMusicList.clear();
	bgMusicID.clear();
	bgMusicString.clear();
}

bool AudioManager::loadAudio(std::string filePath)
{
	printf("Loading all audio list data: %s \n", filePath.c_str());

	std::ifstream audioList(filePath);

	if (audioList.is_open())
	{
		for (int i = 0; i < 2; i++)
		{
			int numItems;

			audioList >> numItems;

			for (int j = 0; j< numItems; j++)
			{
				std::string id;
				std::string name;
				std::string audioFileTxt;

				audioList >> id;
				audioList >> name;
				audioList >> audioFileTxt;

				printf("Loading audio data: %s \n", audioFileTxt.c_str());
				std::ifstream audioFile(audioFileTxt);
				if (!audioFile)
				{
					printf("File doesn't exist. \n");
				}
				else {
					printf("File exists! \n");
				}

				Audio *a = new Audio(audioFileTxt, i);

				if (i == 0)
				{
					bgMusicID[id] = a;
					bgMusicString[name] = a;

					bgMusicList.push_back(a);
				}
				else if (i == 1)
				{
					soundEffectsID[id] = a;
					soundEffectsString[name] = a;

					soundEffectsList.push_back(a);
				}

				


			}
		}
		
		audioList.close();
	}
	else {
		//failed
		printf("Failed to load audio data list:  %s \n", filePath.c_str());
		return false;
	}
	return true;
}


Audio* AudioManager::getSFXByID(std::string id)
{
	return soundEffectsID[id];
}

Audio* AudioManager::getSFXByName(std::string name)
{
	return soundEffectsString[name];
}

Audio* AudioManager::getSFXByIndex(int i)
{
	return soundEffectsList[i];
}

Audio* AudioManager::getMusicByID(std::string id)
{
	return bgMusicID[id];
}

Audio* AudioManager::getMusicByName(std::string name)
{
	return bgMusicString[name];
}

Audio* AudioManager::getMusicByIndex(int i)
{
	return bgMusicList[i];
}

