#include "Tile.h"



Tile::Tile(glm::vec3 pos, glm::vec3 dimensions, TileType *tileType) : WorldObject(pos, dimensions/*, tileType->getSpriteDimensions()*/), tileType(tileType)
{

	tileInit();

}

Tile::Tile(Texture* texture, glm::vec3 pos, glm::vec3 dimensions, TileType *tileType) : WorldObject(texture, pos, dimensions), tileType(tileType)
{

	tileInit();

}


void Tile::tileInit()
{
	collidable = tileType->getCollidable();
	destructible = tileType->getDamageValue();

	climbable = tileType->getClimbable();
	damageValue = tileType->getDamageValue();


	sideL = false;
	sideR = false;
	sideU = false;
	sideD = false;

	staticFriction = 0.95;
	dynamicFriction = 15;
}

Tile::~Tile()
{
}

glm::vec2 Tile::getTextureUVOffset()
{
	return tileType->getSpriteOffset();
}


void Tile::update(float dt)
{
}


Texture* Tile::getTexture()
{
	return tileType->getTexture();
}

std::vector<glm::vec2> Tile::getEntityUVs()
{
	return tileType->getTileTypeUVs();
}

bool Tile::haveBlankID()
{
	return (tileType->getID() == "XX") ? true : false;
}

void Tile::setTileType(std::string ID, TileTypeManager *ttmng)
{
	tileType = ttmng->getTileType(ID);
}

std::string Tile::getTileTypeID()
{
	return tileType->getID();
}

void Tile::setSideR(bool s)
{
	sideR = s;
}

bool Tile::getSideR()
{
	return sideR;
}

void Tile::setSideL(bool s)
{
	sideL = s;
}

bool Tile::getSideL()
{
	return sideL;
}

void Tile::setSideU(bool s)
{
	sideU = s;
}

bool Tile::getSideU()
{
	return sideU;
}

void Tile::setSideD(bool s)
{
	sideD = s;
}

bool Tile::getSideD()
{
	return sideD;
}