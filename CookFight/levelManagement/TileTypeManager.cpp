#include "TileTypeManager.h"


TileTypeManager::TileTypeManager(std::string filePath)
{
	loadTileData(filePath);
}

TileTypeManager::~TileTypeManager()
{

}

void TileTypeManager::loadTileData(std::string filePath)
{
	//File loading message
	printf("Loading tile data \n");

	//Open the file using a ifstream
	std::ifstream file(filePath);

	//If the file successfully opens
	if (file.is_open())
	{
		//Load the number of different spritesheets.
		file >> numOfSpritesheets;

		//loop for the number of spritesheets
		for (int i = 0; i < numOfSpritesheets; i++)
		{
			//variables for the loaded string data
			std::string spritesheetID;
			std::string filePath;
			glm::vec3 dimensions;

			//load in the data
			file >> spritesheetID;
			file >> filePath;
			file >> dimensions.x;
			file >> dimensions.y;

			//store the data
			spritesheets[spritesheetID] = new Texture(filePath);
			spriteDimensions[spritesheetID] = dimensions;

			tileDimens = glm::vec3(dimensions.x, dimensions.y, 0);
		}

		//Load the number of tile types.
		file >> numOfTypes;

		//loop for the number of tile types
		for (int i = 0; i < numOfTypes; i++)
		{
			//variables for the loaded string data
			std::string spritesheetID;
			std::string iD;
			glm::vec2 spriteIndex;
			bool collidable, destructible;
			float frictionValue;
			float bounciness;
			int damageValue;
			bool climbable;
			
			

			//load in the data
			file >> spritesheetID;
			file >> iD;
			file >> spriteIndex.x;
			file >> spriteIndex.y;
			file >> collidable;
			file >> destructible;
			file >> frictionValue;
			file >> bounciness;
			file >> damageValue;
			file >> climbable;

			glm::vec2 spriteSheetDimens = (spritesheets[spritesheetID]->getOrigDimens());

			glm::vec2 tilePos = spriteIndex * spriteDimensions[spritesheetID];

			glm::vec2 uvOffset = (0.5f +tilePos) / spriteSheetDimens;
			glm::vec2 uvDimens = (spriteDimensions[spritesheetID]-1.f)/ spriteSheetDimens;

			//glm::vec2 uvOffset = ( tilePos) / spriteSheetDimens;
		//	glm::vec2 uvDimens = (spriteDimensions[spritesheetID]) / spriteSheetDimens;



			//glm::vec2 uvOffset = (2.f*tilePos + 1.f) / (2.f*spriteSheetDimens);

			//stops texture bleeding
			//forces corodinates to be inside pixel boundaries rather than on the edge
			//uvOffset += glm::vec2(0.001f, 0.001f);
			//uvDimens -= glm::vec2(0.002f, 0.002f);


			//store the data
			tileTypes[iD] = new TileType(spritesheets[spritesheetID], iD, uvOffset, uvDimens,
				collidable, destructible, frictionValue, bounciness, damageValue, climbable);

			tileTypesVector[spritesheetID].push_back(tileTypes[iD]);
		}
		//Close the file
		file.close();

		//File loaded message
		printf( "Tile data loaded. \n");
	}
	else
	{
		//Error message
		printf("Unable to open file : %s \n", filePath);
	}
}

TileType* TileTypeManager::getTileType(std::string tileTypeID)
{
	return tileTypes[tileTypeID];
}

std::unordered_map<std::string, TileType*> TileTypeManager::getTileTypes() {
	return tileTypes;
}

std::unordered_map<std::string, std::vector<TileType*>> TileTypeManager::getTileTypesVector() {
	return tileTypesVector;
}

Texture* TileTypeManager::getTileTypeTexture(std::string tileTypeID)
{
	return spritesheets[tileTypeID];
}