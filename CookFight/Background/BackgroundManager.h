#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "../Texture.h"

class BackgroundManager
{
public:
	BackgroundManager(std::string filePath);

	~BackgroundManager();

	void loadBackground(std::string filePath);

	std::vector<Texture*> getBackgroundsByID(std::string id) { return backgroundsByID[id]; }


private:

	std::unordered_map<std::string, std::vector<Texture*>>  backgroundsByID;
};