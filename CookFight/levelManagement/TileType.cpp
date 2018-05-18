#include "TileType.h"

TileType::TileType(Texture* spritesheet, std::string iD, glm::vec2 uvOffset, glm::vec2 spriteDimensions,
	bool collidable, bool destructible, float frictionValue, float bounciness, float damageValue, bool climbable)
	: spritesheet(spritesheet), iD(iD), uvOffset(uvOffset), spriteDimensions(spriteDimensions),
	collidable(collidable), destructible(destructible), frictionValue(frictionValue), bounciness(bounciness), damageValue(damageValue), climbable(climbable)
	
{
	generateTileUVs();
}

TileType::~TileType()
{

}

void TileType::generateTileUVs()
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



bool TileType::getCollidable()
{
	return collidable;
}

bool TileType::getDestructible()
{
	return destructible;
}

float TileType::getFrictionValue()
{
	return frictionValue;
}

float TileType::getBounciness()
{
	return bounciness;
}

float TileType::getDamageValue()
{
	return damageValue;
}

bool TileType::getClimbable()
{
	return climbable;
}

Texture* TileType::getTexture()
{
	return spritesheet;
}

std::string TileType::getID()
{
	return iD;
}

glm::vec2 TileType::getSpriteOffset()
{
	return uvOffset;
}

glm::vec2 TileType::getSpriteDimensions()
{
	return spriteDimensions;
}