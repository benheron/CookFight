#pragma once
#include "AnimationType.h"
#include <unordered_map>

class SpriteSheet {
public:
	SpriteSheet(std::string spriteSheetName, Texture* spriteSheetTexture, std::unordered_map<std::string, AnimationType*> animations);

	~SpriteSheet();

	std::string getName() { return spriteSheetName; }

	AnimationType* getAnimationType(std::string id) { return animations[id]; }


	Texture* getTexture() { return spriteSheetTexture; }

private:
	std::string spriteSheetName;
	std::unordered_map<std::string, AnimationType*> animations;
	Texture* spriteSheetTexture;
};