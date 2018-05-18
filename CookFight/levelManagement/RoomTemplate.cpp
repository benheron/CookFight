#include "RoomTemplate.h"

/*
RoomTemplate::RoomTemplate(std::unordered_map<std::string, std::vector<std::vector<Tile*>>> roomTiles, std::vector<Creature*> roomCreatures, std::vector<std::string> layerIDs, Vec2 spawnPoint) : roomTiles(roomTiles), roomCreatures(roomCreatures), layerIDs(layerIDs), spawnPoint(spawnPoint)
{
}*/

RoomTemplate::RoomTemplate(
	std::unordered_map<std::string, std::vector<std::vector<std::string>>> mapTilesData,
	std::vector<std::string> layerIDs) : roomTilesData(mapTilesData), layerIDs(layerIDs)
{

}

/*
RoomTemplate::RoomTemplate(std::unordered_map<std::string, std::vector<std::vector<Tile*>>> roomTiles, std::vector<Creature*> roomCreatures, std::vector<std::string> layerIDs, Vec2 spawnPoint, Vec2 mapPos) : roomTiles(roomTiles), roomCreatures(roomCreatures), layerIDs(layerIDs), spawnPoint(spawnPoint), mapPos(mapPos)
{
}*/


RoomTemplate::~RoomTemplate()
{
}

void RoomTemplate::update(float dt)
{
}


std::unordered_map<std::string, std::vector<std::vector<Tile*>>> RoomTemplate::getRoomTiles()
{
	return roomTiles;
}

std::vector<std::string> RoomTemplate::getLayerIDs()
{
	return layerIDs;
}


std::unordered_map<std::string, std::vector<std::vector<std::string>>> RoomTemplate::getRoomTileData()
{
	return roomTilesData;
}

