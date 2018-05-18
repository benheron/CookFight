#include "BackgroundManager.h"


BackgroundManager::BackgroundManager(std::string filePath)
{
	loadBackground(filePath);
}

BackgroundManager::~BackgroundManager()
{

}


void BackgroundManager::loadBackground(std::string filePath)
{


	printf("Opening backgrounds at filepath: %s \n", filePath.c_str());
	std::ifstream backgrounds(filePath);



	if (backgrounds.is_open())
	{
		int numBackgrounds;

		backgrounds >> numBackgrounds;

		for (int i = 0; i < numBackgrounds; i++)
		{
			std::string backgroundName;
			std::string backgroundInfo;
			
			backgrounds >> backgroundName;
			backgrounds >> backgroundInfo;


			std::ifstream thisBackground(backgroundInfo);

			if (thisBackground.is_open())
			{
				int numLayers;

				thisBackground >> numLayers;

				std::vector<Texture*> bgLayers;

				for (int j = 0; j < numLayers; j++)
				{
					std::string texturePath;
					thisBackground >> texturePath;


					Texture *t = new Texture(texturePath);

					bgLayers.push_back(t);
				}

				backgroundsByID[backgroundName] = bgLayers;

				thisBackground.close();
			}

		}

		backgrounds.close();
	}
	else {
		printf("Failed to open filepath: %s \n", filePath.c_str());
	}

	int f = 0;
}