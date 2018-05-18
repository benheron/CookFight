#include "SpriteSheet.h"


SpriteSheet::SpriteSheet(std::string spriteSheetName, Texture* spriteSheetTexture, std::unordered_map<std::string, AnimationType*> animations)
	: spriteSheetName(spriteSheetName), spriteSheetTexture(spriteSheetTexture), animations(animations)
{

}

SpriteSheet::~SpriteSheet()
{

}
