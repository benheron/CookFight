#pragma once
#include <string>
#include "../Texture.h"
#include "../entities/Entity.h"
#include "TextCharacterType.h"

class TextCharacter : public Entity
{
public:
	TextCharacter(glm::vec3 pos, glm::vec3 dimensions, TextCharacterType* textCharType);
	~TextCharacter();

	void update(float dt);
	void render(SDL_Renderer* renderer);

	void setTextCharacterType(TextCharacterType *tct);
	TextCharacterType* getTextCharacterType(TextCharacterType *tct);


	std::vector<glm::vec2> getTextCharacterVertices();
	std::vector<glm::vec2> getTextCharacterUVs();


protected:


	void generateTextVerticesUVs();


	///A pointer to the spritesheet.
	Texture* spritesheet;
	///The ID of the TextCharacter (or the character itself).
	std::string ID;
	///The position of the sprite on the spritesheet.
	glm::vec3 spritePosition;
	///The index position of the sprite on the spritesheet.
	glm::vec3 spriteIndexPositions;
	///The dimensions of the sprite.
	glm::vec3 spriteDimensions;

	TextCharacterType* textCharType;

	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;
};