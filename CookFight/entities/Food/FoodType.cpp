#include "FoodType.h"

FoodType::FoodType(Texture* spritesheet, std::string iD, std::unordered_map<std::string, glm::vec2> uvOffsets, glm::vec2 spriteDimensions)
	: spritesheet(spritesheet), iD(iD), uvOffsets(uvOffsets), spriteDimensions(spriteDimensions)

{
	
	generateUVs();
}

FoodType::~FoodType()
{

}

void FoodType::generateUVs()
{
	glm::vec2 uvPos(uvOffset);
	glm::vec2 v2uv2(spriteDimensions);

	glm::vec2 topLeftUV = glm::vec2(uvPos.x, uvPos.y);
	glm::vec2 topRighttUV = glm::vec2(uvPos.x + v2uv2.x, uvPos.y);
	glm::vec2 bottomLefttUV = glm::vec2(uvPos.x, uvPos.y + v2uv2.y);
	glm::vec2 bottomRightUV = glm::vec2(uvPos.x + v2uv2.x, uvPos.y + v2uv2.y);


	UVs.push_back(topLeftUV);
	UVs.push_back(bottomLefttUV);
	UVs.push_back(topRighttUV);


	UVs.push_back(bottomRightUV);
	UVs.push_back(topRighttUV);
	UVs.push_back(bottomLefttUV);
}

Texture* FoodType::getTexture()
{
	return spritesheet;
}

std::string FoodType::getID()
{
	return iD;
}

glm::vec2 FoodType::getSpriteOffset(std::string foodState)
{
	return uvOffsets[foodState];
}

glm::vec2 FoodType::getSpriteDimensions()
{
	return spriteDimensions;
}

