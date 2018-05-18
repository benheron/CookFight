#include "TextCharacter.h"

TextCharacter::TextCharacter(glm::vec3 pos, glm::vec3 dimensions, TextCharacterType* textCharType) : Entity(pos, dimensions), textCharType(textCharType)
{
	generateTextVerticesUVs();
}

TextCharacter::~TextCharacter()
{

}

void TextCharacter::update(float dt)
{

}

/*
void TextCharacter::render(SDL_Renderer *renderer)
{
	textCharType->render(renderer, pos, dimensions);
}*/



void TextCharacter::setTextCharacterType(TextCharacterType *tct)
{
	textCharType = tct;

	/*vertices.clear();
	UVs.clear();

	generateTextVerticesUVs();*/
}

TextCharacterType* TextCharacter::getTextCharacterType(TextCharacterType *tct)
{
	return textCharType;
}


void TextCharacter::generateTextVerticesUVs()
{

	glm::vec2 v2(textCharType->getTextCharacterDimensions());

	//UVs are upside down so top left vertex is bottom right

	glm::vec2 topLeftVert = glm::vec2(pos.x, pos.y);
	glm::vec2 topRightVert = glm::vec2(pos.x + v2.x, pos.y);
	glm::vec2 bottomLeftVert = glm::vec2(pos.x, pos.y + v2.y);
	glm::vec2 bottomRightVert = glm::vec2(pos.x + v2.x, pos.y + v2.y);

	/*vertices.push_back(bottomLeftVert);
	vertices.push_back(topLeftVert);
	vertices.push_back(bottomRightVert);

	vertices.push_back(topRightVert);
	vertices.push_back(bottomRightVert);
	vertices.push_back(topLeftVert);*/







	vertices.push_back(topLeftVert);
	vertices.push_back(bottomLeftVert);
	vertices.push_back(topRightVert);

	vertices.push_back(bottomRightVert);
	vertices.push_back(topRightVert);
	vertices.push_back(bottomLeftVert);




	/*glm::vec2 uvPos (textCharType->getCharacterPosition());
	glm::vec2 v2uv2(textCharType->getTextCharacterUVDimensions());

	glm::vec2 topLeftUV = glm::vec2(uvPos.x, uvPos.y);
	glm::vec2 topRighttUV = glm::vec2(uvPos.x + v2uv2.x, uvPos.y);
	glm::vec2 bottomLefttUV = glm::vec2(uvPos.x, uvPos.y + v2uv2.y);
	glm::vec2 bottomRightUV = glm::vec2(uvPos.x + v2uv2.x, uvPos.y + v2uv2.y);


	UVs.push_back(topLeftUV);
	UVs.push_back(bottomLefttUV);
	UVs.push_back(topRighttUV);


	UVs.push_back(bottomRightUV);
	UVs.push_back(topRighttUV);
	UVs.push_back(bottomLefttUV);*/

}

std::vector<glm::vec2> TextCharacter::getTextCharacterVertices()
{
	return vertices;
}

std::vector<glm::vec2> TextCharacter::getTextCharacterUVs()
{
	return textCharType->getTextCharacterTypeUVs();
}
