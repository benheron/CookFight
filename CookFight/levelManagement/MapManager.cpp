#include "MapManager.h"




MapManager::MapManager(std::string filePath, TileTypeManager* tileTypeManager)
{
	loadMapData(filePath, tileTypeManager);
}

MapManager::~MapManager()
{
	for (int i = 0; i < rMaps.size(); i++)
	{
		delete rMaps[i];
	}

	for (int i = 0; i < levelIcons.size(); i++)
	{
		delete levelIcons[i];
	}
}

bool MapManager::loadMapData(std::string filePath, TileTypeManager* tileTypeManager)
{
	//A vector to hold all of the layer IDs.
	std::vector<std::string> layerIDs;

	//A 3D vector that contains all of the tiles. [Layer ID][Y Index][X Index]
	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> mapTiles;



	std::unordered_map<std::string, std::vector<std::vector<std::string>>> mapTileStrings;

	printf("Loading map data : %s \n", filePath.c_str());

	std::ifstream mapFile(filePath);

	if (mapFile.is_open())
	{
		std::string roomID;
		glm::vec2 mapIndexDimensions;
		int numberOfLayers;
		glm::vec2 tileDimensions;

		mapFile >> roomID;
		mapFile >> mapIndexDimensions.x;
		mapFile >> mapIndexDimensions.y;
		mapFile >> numberOfLayers;
		mapFile >> tileDimensions.x;
		mapFile >> tileDimensions.y;


		//store the map ID
		roomIDs.push_back(roomID);

		for (int i = 0; i < numberOfLayers; i++)
		{
			//Store the ID of the layer
			std::string layerID;
			mapFile >> layerID;
			layerIDs.push_back(layerID);

			for (int y = 0; y < mapIndexDimensions.y; y++)
			{
				if (layerID == "O" || layerID == "B")
				{
					std::vector<Tile*> tiles;
					mapTiles[layerID].push_back(tiles);

					//text version
					std::vector<std::string> tileStrings;
					mapTileStrings[layerID].push_back(tileStrings);

					for (int x = 0; x < mapIndexDimensions.x; x++)
					{

						//printf("x: %i ", x);
						//printf("y: %i \n", y);
						//Get the tile
						std::string tileID;
						mapFile >> tileID;

						//Get the data to load into the new tile
						TileType* tileType = tileTypeManager->getTileType(tileID);
						glm::vec2 spriteDimensions = tileType->getSpriteDimensions();
						//glm::vec2 spritePos = tileType->getSpritePos();
						//Texture* tileTexture = tileType->getTexture();

						//Store tile
						/*mapTiles[layerID][y].push_back(
						new Tile(glm::vec3((x * spriteDimensions.x), (y * spriteDimensions.y), 0), glm::vec3(spriteDimensions.x, spriteDimensions.y, 0), tileType)
						);*/



						//store tile text version
						mapTileStrings[layerID][y].push_back(tileID);
					}
				}
			}
		}
	
		roomTemplates[roomID] = new RoomTemplate(mapTileStrings, layerIDs);
		rMaps.push_back(roomTemplates[roomID]);
		

		printf("Map data loaded. \n");

		return true;
	}
	else 
	{
		//Error
		printf("Unable to open map file : %s \n", filePath);
		return false;
	}
}

RoomTemplate* MapManager::getMap(std::string mapID)
{
	return roomTemplates[mapID];
}





int MapManager::getNumberMaps()
{
	return rMaps.size();
}

