#include "TextCharacterType.h"

TextCharacterType::TextCharacterType(Texture *spritesheet, int asciiID, std::string textChar, glm::vec3 characterPosition, glm::vec3 characterDimensions, glm::vec3 characterUVDimens)
	:spritesheet(spritesheet), asciiID(asciiID), textChar(textChar), characterPosition(characterPosition), characterDimensions(characterDimensions), characterUVDimens(characterUVDimens)
{
	glm::vec2 uvPos(characterPosition);
	glm::vec2 v2uv2(characterUVDimens);

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

TextCharacterType::~TextCharacterType()
{

}

/*
void TextCharacterType::render(SDL_Renderer* renderer, glm::vec2 pos)
{
	spritesheet->pushSpriteToScreen(renderer, pos, spriteDimensions, spritePosition, spriteDimensions);
}


void TextCharacterType::render(SDL_Renderer* renderer, Vec2 pos, Vec2 dimensions)
{
	spritesheet->pushSpriteToScreen(renderer, pos, dimensions, spritePosition, spriteDimensions);
}*/

glm::vec3 TextCharacterType::getTextCharacterDimensions()
{
	return characterDimensions;
}

glm::vec3 TextCharacterType::getTextCharacterUVDimensions()
{
	return characterUVDimens;
}

glm::vec3 TextCharacterType::getCharacterPosition()
{
	return characterPosition;
}

std::vector<glm::vec2> TextCharacterType::getTextCharacterTypeUVs()
{
	return UVs;
}