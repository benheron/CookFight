#pragma once

#include "TileType.h"
#include "../Texture.h"
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream> 

/**
@brief Creates a TileTypeManager for dealing with the TileType objects.
*/
class TileTypeManager
{
public:
	/**
	@brief TileTypeManager constructor.
	@param filePath The file path of the tiles data.
	@param renderer A pointer to the renderer.
	*/
	TileTypeManager(std::string filePath);

	/**
	@brief TileManager destructor.
	*/
	~TileTypeManager();

	/**
	@brief Gets a pointer to the TileType associated with the ID.
	@param tileTypeID The ID of wanted TileType.
	@returns A pointer to the TileType.
	*/
	TileType* getTileType(std::string tileTypeID);


	/**
	@brief Gets all the tile types
	@returns All the tile types pointers
	*/
	std::unordered_map<std::string, TileType*> getTileTypes();


	/**
	@brief Gets all the tile types
	@returns All the tile types pointers in a vector
	*/
	std::unordered_map<std::string, std::vector<TileType*>> getTileTypesVector();


	/**
	@brief Gets the tilesheet texture
	@returns The tilesheet texture specified
	*/
	Texture* getTileTypeTexture(std::string tileTypeID);


	/**
	@brief Gets the tile size
	@returns The tile size
	*/
	glm::vec3 getTileTypeSize() { return tileDimens; }

private:
	///The number of different spritesheets.
	int numOfSpritesheets;
	///The number of tile types.
	int numOfTypes;
	///The loaded tiles. Contains the tile data.
	std::unordered_map<std::string, TileType*> tileTypes;
	///The spritesheets.
	std::unordered_map<std::string, Texture*> spritesheets;
	///The dimensions of the sprites for each spritesheet.
	std::unordered_map<std::string, glm::vec2> spriteDimensions;

	///The tile dimensions
	glm::vec3 tileDimens;




	std::unordered_map<std::string, std::vector<TileType*>> tileTypesVector;
	/**
	@brief Loads the tile data from the file.
	@param filePath The file path of the tiles data.
	@param renderer A pointer to the renderer.
	*/
	void loadTileData(std::string filePath);

};