#include "TextureManager.h"

TextureManager::TextureManager(std::string filePath)
{
	loadTextures(filePath);
}

TextureManager::~TextureManager()
{
	for (int i = 0; i < texturesList.size(); i++)
	{
		delete texturesList[i];
	}
	texturesList.clear();
	//texturesID.clear();
	texturesString.clear();
}

bool TextureManager::loadTextures(std::string filePath)
{
	printf("Loading all miscellaneous textures list data: %s \n", filePath.c_str());

	std::ifstream textureList(filePath);

	if (textureList.is_open())
	{
		
		int numItems;

		textureList >> numItems;

		for (int j = 0; j < numItems; j++)
		{
			
			std::string name;
			std::string textureFileTxt;

			
			textureList >> name;
			textureList >> textureFileTxt;

			printf("Loading audio data: %s \n", textureFileTxt.c_str());
			std::ifstream textureFile(textureFileTxt);
			if (!textureFile)
			{
				printf("File doesn't exist. \n");
			}
			else {
				printf("File exists! \n");
			}

			Texture *t = new Texture(textureFileTxt);

			
			//texturesID[id] = t;
			texturesString[name] = t;

			texturesList.push_back(t);
			
			




		}
		

		textureList.close();
	}
	else {
		//failed
		printf("Failed to load audio data list:  %s \n", filePath.c_str());
		return false;
	}
	return true;
}


/*
Texture* TextureManager::getTextureByID(std::string id)
{
	return texturesID[id];
}
*/

Texture* TextureManager::getTextureByName(std::string name)
{
	return texturesString[name];
}

Texture* TextureManager::getTextureByIndex(int i)
{
	return texturesList[i];
}
