#pragma once

#include "Tile.h"
#include <Vector>




/**
@brief Contains all the data for the map templates
*/
class RoomTemplate
{
public:

	RoomTemplate(
		std::unordered_map<std::string, std::vector<std::vector<std::string>>> mapTilesData, 
		std::vector<std::string> layerIDs);


	/**
	@brief Map destructor.
	*/
	~RoomTemplate();

	/**
	@brief Update the Map.
	@param dt The delta time.
	*/
	void update(float dt);



	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> getRoomTiles();

	std::vector<std::string> getLayerIDs();


	std::unordered_map<std::string, std::vector<std::vector<std::string>>> getRoomTileData();









private:
	///A vector to hold all of the layer IDs.
	std::vector<std::string> layerIDs;
	///A 3D vector that contains all of the tiles. [Layer ID][Y Index][X Index]
	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> roomTiles;


	///the map's ID
	std::string ID;

	///A 3D vector that contains all of the tiles. [Layer ID][Y Index][X Index]
	std::unordered_map<std::string, std::vector<std::vector<std::string>>> roomTilesData;


	glm::vec3 playerPos;
};