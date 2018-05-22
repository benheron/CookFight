#pragma once

#include "FoodType.h"
#include "../../Texture.h"
#include "../../Animation/SpriteSheet.h"
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream> 

/**
@brief Creates a TileTypeManager for dealing with the TileType objects.
*/
class FoodTypeManager
{
public:
	/**
	@brief TileTypeManager constructor.
	@param filePath The file path of the tiles data.
	@param renderer A pointer to the renderer.
	*/
	FoodTypeManager(std::string filePath);

	/**
	@brief TileManager destructor.
	*/
	~FoodTypeManager();

	/**
	@brief Gets a pointer to the TileType associated with the ID.
	@param tileTypeID The ID of wanted FoodType.
	@returns A pointer to the FoodType.
	*/
	FoodType* getFoodType(std::string tileTypeID);


	/**
	@brief Gets all the food types
	@returns All the food types pointers
	*/
	std::unordered_map<std::string, FoodType*> getFoodTypes();


	/**
	@brief Gets all the food types
	@returns All the food types pointers in a vector
	*/
	std::vector<FoodType*>  getFoodTypesVector();


	/**
	@brief Gets the food texture
	@returns The food texture specified
	*/
	Texture* getFoodTypeTexture(std::string foodTypeID);


	/**
	@brief Gets the food size
	@returns The food size
	*/
	glm::vec3 getFoodTypeSize() { return foodDimens; }

	SpriteSheet* getFoodSpriteSheet() { return foodSpriteSheet; }

	std::vector<std::string> getFoodStates() { return foodStates; }

	std::vector<std::string> getFoodTypeNames() { return foodTypeNames; }

private:
	///The number of different spritesheets.
	int numOfSpritesheets;
	///The number of food types.
	int numOfTypes;
	///The loaded tiles. Contains the food data.
	std::unordered_map<std::string, FoodType*> foodTypes;
	///The spritesheets.
	Texture* foodTexture;
	///The dimensions of the sprites for each spritesheet.
	std::unordered_map<std::string, glm::vec2> spriteDimensions;

	///The food dimensions
	glm::vec3 foodDimens;

	SpriteSheet* foodSpriteSheet;


	std::vector<FoodType*> foodTypesVector;
	/**
	@brief Loads the food data from the file.
	@param filePath The file path of the food data.
	*/
	void loadFoodData(std::string filePath);


	std::vector<std::string> foodStates;

	std::vector<std::string> foodTypeNames;
};