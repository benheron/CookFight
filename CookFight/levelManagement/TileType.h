#pragma once

#include "../Texture.h"
#include <vector>
#include "glm/glm.hpp"

/**
@brief Creates a TileType Object.
*/
class TileType
{
public:
	/**
	@brief TileType constructor.
	@param spritesheet A pointer to the Tile spritesheet.
	@param iD The ID of the TileType.
	@param collidable A boolean for if the TileType is collidable.
	@param destructible A boolean for if the TileType is destructible.
	@param spriteIndexPositions The index positions of the TileType sprite on the spritesheet.
	@param spriteDimensions The dimensions of the TileType sprite on the spritesheet.
	*/
	TileType(Texture* spritesheet, std::string iD, glm::vec2 uvOffset, glm::vec2 spriteDimensions,
		bool collidable, bool destructible, float frictionValue, float bounciness, float damageValue, bool climbable);

	/**
	@brief TileType destructor.
	*/
	~TileType();



	/**
	@brief Gets if the TileType is collidable.
	@return If the TileType is collidable.
	*/
	bool getCollidable();

	/**
	@brief Gets if the TileType is destructible.
	@return If the TileType is destructible.
	*/
	bool getDestructible();

	/**
	@brief Gets a pointer to the TileType Texture.
	@return A pointer to the Texture.
	*/
	Texture* getTexture();

	/**
	@brief Gets the TileType ID.
	@return The TileType ID.
	*/
	std::string getID();

	/**
	@brief Gets the UV position (its offset) in the spritesheet.
	@return The sprites position.
	*/
	glm::vec2 getSpriteOffset();

	/**
	@brief Gets the sprites dimension in the spritesheet.
	@return The sprites dimensions.
	*/
	glm::vec2 getSpriteDimensions();


	float getFrictionValue();

	float getBounciness();

	float getDamageValue();

	bool getClimbable();

	std::vector<glm::vec2> getTileTypeUVs() { return UVs; }

private:
	void generateTileUVs();



	///A pointer to the spritesheet.
	Texture* spritesheet;
	///The ID of the TileType.
	std::string iD;
	///A boolean for if the TileType is collidable.
	bool collidable;
	///A boolean for if the TileType is destructible.
	bool destructible;
	///The position of the sprite on the spritesheet.
	glm::vec2 uvOffset;


	///The dimensions of the sprite.
	glm::vec2 spriteDimensions;


	std::vector<glm::vec2> UVs;


	float frictionValue;
	float bounciness;
	float damageValue;
	bool climbable;
};