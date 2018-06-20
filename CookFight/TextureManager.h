#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "Texture.h"

class TextureManager {
public:

	TextureManager(std::string filePath);
	~TextureManager();

	bool loadTextures(std::string filePath);

	//Texture* getTextureByID(std::string id);
	Texture* getTextureByName(std::string id);
	Texture* getTextureByIndex(int index);

	

protected:
	//std::unordered_map<std::string, Texture*> texturesID;
	std::unordered_map<std::string, Texture*> texturesString;
	std::vector<Texture*> texturesList;
};