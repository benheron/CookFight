#pragma once

#include "../../Texture.h"
#include <vector>
#include <unordered_map>
#include "glm/glm.hpp"

/**
@brief Creates a TileType Object.
*/
class FoodType
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
	FoodType(Texture* spritesheet, std::string iD, std::unordered_map<std::string, glm::vec2> uvOffsets, glm::vec2 spriteDimensions);

	/**
	@brief TileType destructor.
	*/
	~FoodType();




	/**
	@brief Gets a pointer to the FoodType Texture.
	@return A pointer to the Texture.
	*/
	Texture* getTexture();

	/**
	@brief Gets the FoodType ID.
	@return The FoodType ID.
	*/
	std::string getID();

	/**
	@brief Gets the UV position (its offset) in the spritesheet.
	@return The sprites position.
	*/


	glm::vec2 getSpriteOffset(std::string foodState);

	/**
	@brief Gets the sprites dimension in the spritesheet.
	@return The sprites dimensions.
	*/
	glm::vec2 getSpriteDimensions();




	std::vector<glm::vec2> getTypeUVs() { return UVs; }

private:
	void generateUVs();



	///A pointer to the spritesheet.
	Texture* spritesheet;
	///The ID of the FoodType.
	std::string iD;


	///The position of the sprite on the spritesheet.
	glm::vec2 uvOffset;

	std::unordered_map<std::string, glm::vec2> uvOffsets;

	///The dimensions of the sprite.
	glm::vec2 spriteDimensions;


	std::vector<glm::vec2> UVs;


	std::unordered_map<std::string, glm::vec2> typesUVOffsets;


};