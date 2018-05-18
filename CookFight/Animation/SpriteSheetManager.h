#pragma once
#include "../Texture.h"
#include <vector>
#include <unordered_map>
#include <fstream>
#include "SpriteSheet.h"


class SpriteSheetManager {
public:
	SpriteSheetManager(std::string filePath);
	~SpriteSheetManager();

	

	void loadSpriteSheet(std::string filePath);

	SpriteSheet* getSpriteSheetByID(std::string id) { return spriteSheets[id]; }

private:
	std::unordered_map<std::string, SpriteSheet*> spriteSheets;

};