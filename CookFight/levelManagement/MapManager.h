#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "Tile.h"
#include "TileTypeManager.h"
#include "RoomTemplate.h"

/**
@brief Contains all the data and functions to manage the Map Objects.
*/
class MapManager 
{
public:
	/**
	@brief Creates the MapManager to load in the Map files
	@param filePath The path to the file which holds the initial map data.
	@param tileTypeManager* A pointer to the TileTypeManager.
	@param creatureManager A pointer to the CreatureManager
	*/
	MapManager(std::string filePath, TileTypeManager* tileTypeManager);

	/**
	@brief MapManager destructor.
	*/
	~MapManager();

	/**
	@brief Loads in the Map data.
	@param filePath The path to the file which holds the map data.
	@param tileTypeManager* A pointer to the TileTypeManager.
	*/
	bool loadMapData(std::string filePath, TileTypeManager* tileTypeManager);

	/**
	@brief Gets the Map data.
	@param mapID The ID of the Map to return.
	@return The Map data.
	*/
	RoomTemplate* getMap(std::string mapID);

	/**
	@brief Gets the random Map data
	@return The Map data.
	*/
	RoomTemplate* getRandomMap();

	std::vector<glm::vec2> getRoomPositions();

	RoomTemplate* getRandomMapFromIndex(int i);

	int getNumberMaps();

	Texture* getLevelIcon(std::string id);

private:



	///A vector to hold all of the map IDs.
	std::vector<std::string> roomIDs;
	///A vector to hold all of the maps.
	std::unordered_map<std::string, RoomTemplate*> roomTemplates;

	///A different vector to hold maps for random lookups
	std::vector<RoomTemplate*> rMaps;

	std::vector<glm::vec2> roomPositions;

	std::vector<Texture*> levelIcons;

	std::unordered_map<std::string, Texture*> levelIconsUM;


};