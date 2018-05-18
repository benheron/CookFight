#pragma once

#include <string>
#include "../entities/WorldObject.h"
#include "TileType.h"
#include "TileTypeManager.h"


/**
@brief Contains all the data and functions dealing with the Tile objects.
*/
class Tile : public WorldObject
{
public:

	Tile(glm::vec3 pos, glm::vec3 dimensions, TileType *tileType);

	Tile(Texture* texture, glm::vec3 pos, glm::vec3 dimensions, TileType *tileType);


	
	/**
	@brief Constructs the Tile object.
	@param texture A pointer to the Tile Texture.
	@param pos The position of the Tile.
	@param dimensions The dimensions of the Tile.
	@param spritePos The position of the sprite in the spritesheet.
	@param spriteDimensions The dimensions of the sprite in the spritesheet.
	@param tileType A pointer to the TileType.
	*/

	//Tile(Texture* texture, glm::vec3 pos, glm::vec3 dimensions, glm::vec2 spritePos, glm::vec2 spriteDimensions, TileType* tileType);

	/**
	@brief Tile destructor.
	*/
	~Tile();

	/**
	@brief Updates the Tile.
	@param dt The delta time.
	*/
	void update(float dt);


	Texture* Tile::getTexture();

	/**
	@brief checks if the TileID is blank
	@return True if ID is XX, False if not
	*/
	bool haveBlankID();


	void setTileType(std::string ID, TileTypeManager *ttmng);

	std::string getTileTypeID();

	bool getCollidable() { return collidable; }

	bool getDestructible() { return destructible; }

	float getFrictionValue() {return frictionValue;}


	float getDamageValue() { return damageValue; }

	bool getClimbable() { return climbable; }

	void setSideR(bool s);
	bool getSideR();

	void setSideL(bool s);
	bool getSideL();

	void setSideU(bool s);
	bool getSideU();

	void setSideD(bool s);
	bool getSideD();

	glm::vec2 getTextureUVOffset();

	std::vector<glm::vec2> getEntityUVs();


private:
	void tileInit();


	


	///Reference to tile type.
	TileType* tileType;

	bool collidable;
	bool destructible;
	float frictionValue;
	float damageValue;
	bool climbable;

	bool sideR;
	bool sideL;
	bool sideU;
	bool sideD;
};