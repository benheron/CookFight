#pragma once
#include "../Texture.h"
#include <glm/glm.hpp>
#include <vector>

class TextCharacterType
{
public:
	TextCharacterType(Texture *spritesheet, int asciiID, std::string textChar, glm::vec3 characterPositions, glm::vec3 characterDimensions, glm::vec3 characterUVDimens);
	~TextCharacterType();

	//void render(SDL_Renderer* renderer, glm::vec2 pos);
	//void render(SDL_Renderer* renderer, glm::vec2 pos, glm::vec2 dimensions);
	glm::vec3 getTextCharacterDimensions();

	glm::vec3 getTextCharacterUVDimensions();

	glm::vec3 getCharacterPosition();

	std::vector<glm::vec2> getTextCharacterTypeUVs();


protected:
	///A pointer to the spritesheet.
	Texture* spritesheet;
	///The ID of the TextCharacterType (or the character itself).
	int asciiID;
	///The character itself
	std::string textChar;
	///The position of the sprite on the spritesheet. From 0-1
	glm::vec3 characterPosition;
	///The index position of the sprite on the spritesheet.
	glm::vec3 spriteIndexPositions;
	///The dimensions of the sprite.
	glm::vec3 characterDimensions;
	///The UV
	glm::vec3 characterUVDimens;

	std::vector<glm::vec2> UVs;

};