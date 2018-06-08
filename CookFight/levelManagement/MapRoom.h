#pragma once

#include "../entities/Entity.h"
#include "Tile.h"
#include <Vector>
#include "MapManager.h"
#include "RoomTemplate.h"
#include <math.h>
#include "../Collision.h"

#include "../entities/Actor.h"


//for textmodmat
#include "../states/State.h"

/**
@brief Contains the data for a single room on the map
*/
class MapRoom : public Entity
{
public:
	/**
	@brief Creates a blank MapRoom
	*/
	MapRoom();

	/**
	@brief Creates a MapRoom using the map
	*/
	MapRoom(MapManager *mpmng, TileTypeManager *ttmng, std::string id);


	/**
	@brief Room destructor
	*/
	~MapRoom();

	/**
	@brief Update the Map.
	@param dt The delta time.
	*/
	//void update(float dt);



	/**
	@brief
	*/

	void createRoom(MapManager *mpmng, TileTypeManager *ttmng);

	void labelTileSides();


	bool collideWithTile(Actor* e, float dt);

	bool collideWithTile(Entity* e, float dt, bool isProjectile = false);



	
	/**
	@brief Get tile object at position xy
	@returns Tile object at position xy
	*/
	Tile* getTile(glm::vec2 xy);

	


	void changeTileType(std::string layer, glm::vec2 tilePos, std::string tileID, TileTypeManager *ttmng);

	std::unordered_map<std::string, std::vector<std::vector<std::string>>> getRoomTilesStrings();

	std::vector<std::string> getLayerIDs();


	std::vector<Entity*> getTilesEntities(std::string layer);

	

	bool tileDebug;







private:

	///A vector to hold all of the layer IDs.
	std::vector<std::string> layerIDs;
	///A 3D vector that contains all of the tiles. [Layer ID][Y Index][X Index]
	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> roomTiles;

	std::vector<Entity*> roomItems;

	std::unordered_map<std::string, std::vector<std::vector<std::string>>> roomTilesStrings;
	std::vector<std::string> roomCreatureStrings;

	///the map's ID
	std::string ID;

	glm::vec2 roomPos;


	bool playerLoaded = false;


	glm::vec2 mapPos;


	int change = 0;
	TileTypeManager *ttm;


	bool levelComplete = false;


	glm::vec2 tileSize;


	TextModMat* tmm;
};