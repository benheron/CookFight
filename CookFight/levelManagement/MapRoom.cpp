#include "MapRoom.h"

MapRoom::MapRoom()
{
	
}

MapRoom::MapRoom(MapManager *mpmng, TileTypeManager *ttmng, std::string id) : Entity(glm::vec3(0), glm::vec3(0), glm::vec2(0), glm::vec3(0) / 2.f, true)
{


	RoomTemplate *rt = mpmng->getMap(id);
	roomTiles = rt->getRoomTiles();

	layerIDs = rt->getLayerIDs();
	//roomPos = pos;

	roomTilesStrings = rt->getRoomTileData();


//	exists = true;

	//explicit tile size
	tileSize = glm::vec2(32, 32);

	createRoom(mpmng, ttmng);
}


MapRoom::~MapRoom()
{

	for (int i = 0; i < layerIDs.size(); i++)
	{
		//Store the ID of the layer
		std::string layerID = layerIDs[i];


		int ySize = roomTiles["B"].size();



		for (int y = 0; y < ySize; y++)
		{
			int xSize = roomTiles["B"][0].size();

			if (layerID == "O" || layerID == "B")
			{

				for (int x = 0; x < xSize; x++)
				{
					delete roomTiles[layerID][y][x];
				}
			}
		}
	}





}


//this one
void MapRoom::createRoom(MapManager *mpmng, TileTypeManager *ttmng)
{
	//generate new room from the template data
	//this allows the same room to be used but hold different data incase some is changed mid-gameplay

	


	//temp
	ttm = ttmng;

	int numLayers = layerIDs.size();

	std::unordered_map<std::string, std::vector<std::vector<Tile*>>> roomys;
	std::vector<std::string> creatureys;

	int c = 0;

	for (int i = 0; i < numLayers; i++)
	{
		std::vector<glm::vec2> verts;
		std::vector<glm::vec2> us;


		//Store the ID of the layer
		std::string layerID = layerIDs[i];


		int ySize = roomTilesStrings["B"].size();

		int zVal;


		for (int y = 0; y < ySize; y++)
		{
			int xSize = roomTilesStrings["B"][0].size();

			if (layerID == "O" || layerID == "B")
			{
				std::vector<Tile*> tiles;
				roomTiles[layerID].push_back(tiles);

				for (int x = 0; x < xSize; x++)
				{
					//Get the tile
					std::string tileID = roomTilesStrings[layerID][y][x];

					
					//Get the data to load into the new tile
					TileType* tileType = ttmng->getTileType(tileID);

					Tile *t = new Tile(glm::vec3((x * tileSize.x), (y * tileSize.y), 0), glm::vec3(tileSize.x, tileSize.y, 0), tileType);

					if (tileID == "XX")
					{
						t->setShouldRender(false);
					}

					if (tileID != "XX")
					{
						//get vertices and uvs from tile
						std::vector<glm::vec2> v = t->getEntityVertices();
						std::vector<glm::vec2> u = t->getEntityUVs();


						verts.insert(std::end(verts), std::begin(v), std::end(v));
						us.insert(std::end(us), std::begin(u), std::end(u));

						if (!t->haveBlankID() && !t->getClimbable())
						{

							t->setSideL(true);
							t->setSideR(true);
							t->setSideU(true);
							t->setSideD(true);
						}


						if (t->getTileTypeID() == "L2")
						{
							t->setSideU(true);
						}
					}

					roomTiles[layerID][y].push_back(t);
					
				}
			}

		}
		if (verts.size() > 0)
		{
			Model * mo = new Model(verts, us);

			entModels.push_back(mo);

			entTextures.push_back(ttmng->getTileTypeTexture(layerID));
			
		}
		

	}



	dimens.x = roomTiles["O"][0].size() * tileSize.x;
	dimens.y = roomTiles["O"].size() * tileSize.y;


	labelTileSides();

	
	

}

void MapRoom::labelTileSides()
{
	std::vector<std::vector<Tile*>> objectLayerTiles = roomTiles["O"];
	int h = objectLayerTiles.size();
	int l = objectLayerTiles[0].size();

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < l; j++)
		{

			Tile *thisTile = objectLayerTiles[i][j];

			int befX = j - 1;
			int befY = i - 1;
			int afX = j + 1;
			int afY = i + 1;
			

			/*if (befX > -1 && befY > -1 &&
				afX < l && afY < h)*/
			{
				if (!thisTile->haveBlankID() || !thisTile->getCollidable())
				{
					if (befX > -1)
					{
						//check left side
						if (thisTile->getSideL() && objectLayerTiles[i][j - 1]->getSideR())
						{
							thisTile->setSideL(false);
							objectLayerTiles[i][j - 1]->setSideR(false);
						}
					}
					
					if (afX < l)
					{
						//check right side
						if (thisTile->getSideR() && objectLayerTiles[i][j + 1]->getSideL())
						{
							thisTile->setSideR(false);
							objectLayerTiles[i][j + 1]->setSideL(false);
						}
					}
					
					if (befY < -1)
					{
						//check above
						if (thisTile->getSideU() && objectLayerTiles[i - 1][j]->getSideD())
						{
							thisTile->setSideU(false);
							objectLayerTiles[i - 1][j]->setSideD(false);
						}
					}
				
					
					if (afY < h)
					{
						//check below
						if (thisTile->getSideD() && objectLayerTiles[i + 1][j]->getSideU())
						{
							thisTile->setSideD(false);
							objectLayerTiles[i + 1][j]->setSideU(false);
						}
					}
					
				}
			}
		}
	}
}

bool MapRoom::collideWithTile(Actor* e, float dt)
{
	bool collision = false;


	glm::vec3 entPos = e->getPosition();
	glm::vec3 entPosDim = entPos + e->getDimensions();

	int minTileX = floor(entPos.x / tileSize.x);
	int minTileY = floor(entPos.y / tileSize.y);


	int maxTileX = floor(entPosDim.x / tileSize.x);
	int maxTileY = floor(entPosDim.y / tileSize.y);

	int xLimit = roomTiles["O"][0].size() - 1;
	int yLimit = roomTiles["O"].size() - 1;
	

	//e->setBlendColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	glm::vec4 blendCol = glm::vec4(1.0f, .0f, .0f, 1.0f);

	bool usedFriction = false;
	

	for (int i = minTileY - 1; i < maxTileY + 1; i++)
	{
		for (int j = minTileX - 1; j < maxTileX + 1; j++)
		{
			if (i > -1 && i <= yLimit &&
				j > -1 && j <= xLimit)
			{
				Tile* curTile = roomTiles["O"][i][j];
				if (!curTile->haveBlankID())
				{
					std::vector<glm::vec3> vTests;


					if (!curTile->getSideU())
					{
						vTests.push_back(glm::vec3(0, -1, 0));
					}

					if (!curTile->getSideL())
					{
						vTests.push_back(glm::vec3(-1, 0, 0));
					}

					if (!curTile->getSideR())
					{
						vTests.push_back(glm::vec3(1, 0, 0));
					}

					if (!curTile->getSideD())
					{
						vTests.push_back(glm::vec3(0, 1, 0));
					}




					PenDir pdEnt;
					PenDir pdTile;
					//if (Collision::SATSupportAxes(e->getBoundingBox(), curTile->getBoundingBox(), pdEnt, pdTile, vTests))
					if (Collision::SATSupport(e->getBoundingBox(), curTile->getBoundingBox(), pdEnt, pdTile))
					{
						

						
						bool onFloor = false;
						collision = true;

						
						
						glm::vec3 changPos;
						glm::vec3 colDir;

						//check which collision to us
						if (pdEnt.penetration < pdTile.penetration)
						{
							//use pdEnt 
							changPos = pdEnt.penetration * -pdEnt.dir;
							colDir = -pdEnt.dir;
						}
						else {
							//use pdTile
							changPos = pdTile.penetration * pdTile.dir;
							colDir = pdTile.dir;
						}
						
						//make sure they're going towards each other
						//get relative velocity along collision direction

						glm::vec3 relativeVelocity =  e->getVelocity() - curTile->getVelocity();
						glm::vec3 relVelAlongNormal = relativeVelocity * colDir;
						float relVelNorm = relVelAlongNormal.x + relVelAlongNormal.y;

						//make sure tile and actor are actually going towards each other
						//stops rare bugs when velocity stops after colliding with a wall not actual moving towards
						if (relVelNorm > 0)
						{
							continue;
						}


						
				


						glm::vec3 tileDir = pdTile.dir;

						

						bool collideWithThisTile = false;

						if (curTile->getSideU())
						{
							if ((tileDir.y == -1.f && tileDir.x == 0.f)||
								(colDir.y == -1.f && colDir.x == 0.f)
								)
							{
								collideWithThisTile = true;
							}
						}

						if (curTile->getSideD())
						{
							if ((tileDir.y == 1.f && tileDir.x == 0.f)||
								(colDir.y == -1.f && colDir.x == 0.f)
								)
							{
								collideWithThisTile = true;
							}
						}

						if (curTile->getSideL())
						{
							if ((tileDir.x == -1.f && tileDir.y == 0.f)||
								(colDir.y == 0.f && colDir.x == 1.f)
								)
							{
								collideWithThisTile = true;
							}
						}

						if (curTile->getSideR())
						{
							if (tileDir.x == 1.f && tileDir.y == 0.f ||
								colDir.y == 0.f && colDir.x == -1.f
								)
							{
								
								collideWithThisTile = true;
							}
						}


						glm::vec3 tangent = relativeVelocity - colDir*relVelNorm;


						glm::vec3 tnorm;
						glm::vec3 frictionVel;


						if (tangent.x < 0.01 &&
							tangent.x > -0.01)
						{
							tangent.x = 0;
						}

						if (tangent.y < 0.01 &&
							tangent.y > -0.01)
						{
							tangent.y = 0;
						}

						if (e->getVelocity().x < 0.f)
						{
							tnorm = glm::vec3(-1, 0, 0);
						}
						else {
							tnorm = glm::vec3(1, 0, 0);
						}
						 
					

						//glm::vec3(abs(tangent.x), abs(tangent.y), 0)

						if (glm::vec3(abs(tangent.x), abs(tangent.y), 0) != glm::vec3(0, 0, 0))
						{
							//tnorm = glm::normalize(tangent);



							frictionVel = tnorm * glm::vec3(e->getVelocity().x, 0, 0);
							float pbf = (frictionVel.x + frictionVel.y);

							pbf *= 0.8f;

							frictionVel *= curTile->getDynamicFriction() *1;// *pbf;

							//float pushBackFriction = -(frictionVel.x + frictionVel.y);
						} else{
							frictionVel = glm::vec3(0);
						}
						






						
						if (collideWithThisTile)
						{


							e->hitTile(colDir, tangent, frictionVel, dt);
							e->setPosition(changPos, true);

							//collision direction is positive y
							//there is a tile underneath
							if (onFloor)
							{
								//e->setBlendColour(glm::vec4(.0f, 1.0f, .0f, 1.0f));
								//e->setOnFloor(true);
								if (!usedFriction)
								{
									//e->hitTileFriction(tangent, frictionVel, dt);
								//	usedFriction = true;
								}
								
								

							} else {
								//e->setBlendColour(blendCol);
							}
							
						}
					


				

					}
				}
			}
		}
	}


	return collision;
}


bool MapRoom::collideWithTile(Entity* e, float dt, bool isProjectile)
{
	bool collision = false;


	glm::vec3 entPos = e->getPosition();
	glm::vec3 entPosDim = entPos + e->getDimensions();

	int minTileX = floor(entPos.x / tileSize.x);
	int minTileY = floor(entPos.y / tileSize.y);


	int maxTileX = floor(entPosDim.x / tileSize.x);
	int maxTileY = floor(entPosDim.y / tileSize.y);

	int xLimit = roomTiles["O"][0].size() - 1;
	int yLimit = roomTiles["O"].size() - 1;


	//e->setBlendColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	glm::vec4 blendCol = glm::vec4(1.0f, .0f, .0f, 1.0f);

	bool usedFriction = false;


	for (int i = minTileY - 1; i < maxTileY + 1; i++)
	{
		for (int j = minTileX - 1; j < maxTileX + 1; j++)
		{
			if (i > -1 && i <= yLimit &&
				j > -1 && j <= xLimit)
			{
				Tile* curTile = roomTiles["O"][i][j];
				if (!curTile->haveBlankID())
				{
					std::vector<glm::vec3> vTests;


					if (!curTile->getSideU())
					{
						vTests.push_back(glm::vec3(0, -1, 0));
					}

					if (!curTile->getSideL())
					{
						vTests.push_back(glm::vec3(-1, 0, 0));
					}

					if (!curTile->getSideR())
					{
						vTests.push_back(glm::vec3(1, 0, 0));
					}

					if (!curTile->getSideD())
					{
						vTests.push_back(glm::vec3(0, 1, 0));
					}




					PenDir pdEnt;
					PenDir pdTile;
					//if (Collision::SATSupportAxes(e->getBoundingBox(), curTile->getBoundingBox(), pdEnt, pdTile, vTests))
					if (Collision::SATSupport(e->getBoundingBox(), curTile->getBoundingBox(), pdEnt, pdTile))
					{



						bool onFloor = false;
						



						glm::vec3 changPos;
						glm::vec3 colDir;

						//check which collision to us
						if (pdEnt.penetration < pdTile.penetration)
						{
							//use pdEnt 
							changPos = pdEnt.penetration * -pdEnt.dir;
							colDir = -pdEnt.dir;
						}
						else {
							//use pdTile
							changPos = pdTile.penetration * pdTile.dir;
							colDir = pdTile.dir;
						}

						//make sure they're going towards each other
						//get relative velocity along collision direction

						glm::vec3 relativeVelocity = e->getVelocity() - curTile->getVelocity();
						glm::vec3 relVelAlongNormal = relativeVelocity * colDir;
						float relVelNorm = relVelAlongNormal.x + relVelAlongNormal.y;

						//make sure tile and actor are actually going towards each other
						//stops rare bugs when velocity stops after colliding with a wall not actual moving towards
						if (relVelNorm > 0)
						{
							continue;
						}






						glm::vec3 tileDir = pdTile.dir;



						bool collideWithThisTile = false;

						if (curTile->getSideU())
						{
							if ((tileDir.y == -1.f && tileDir.x == 0.f) ||
								(colDir.y == -1.f && colDir.x == 0.f)
								)
							{
								collideWithThisTile = true;
							}
						}

						if (curTile->getSideD())
						{
							if ((tileDir.y == 1.f && tileDir.x == 0.f) ||
								(colDir.y == -1.f && colDir.x == 0.f)
								)
							{
								collideWithThisTile = true;
							}
						}

						if (curTile->getSideL())
						{
							if ((tileDir.x == -1.f && tileDir.y == 0.f) ||
								(colDir.y == 0.f && colDir.x == 1.f)
								)
							{
								collideWithThisTile = true;
							}
						}

						if (curTile->getSideR())
						{
							if (tileDir.x == 1.f && tileDir.y == 0.f ||
								colDir.y == 0.f && colDir.x == -1.f
								)
							{

								collideWithThisTile = true;
							}
						}

						if (collideWithThisTile)
						{
							collision = true;
						}

						if (isProjectile && curTile->getTileTypeID() == "U0")
						{
							collision = false;
						}
						else if (isProjectile)
						{
							collision = true;
						}

					}
				}
			}
		}
	}


	return collision;
}





std::vector<Entity*> MapRoom::getTilesEntities(std::string layer)
{
	std::vector<Entity*> tmp;

	for (int i = 0; i < roomTiles[layer].size(); i++)
	{
		for (int j = 0; j < roomTiles[layer][i].size(); j++)
		{
			if (!roomTiles[layer][i][j]->haveBlankID())
			{
				tmp.push_back(roomTiles[layer][i][j]);
			}
			
		}
	}


	return tmp;
}



Tile* MapRoom::getTile(glm::vec2 xy)
{
	return roomTiles["O"][xy.y][xy.x];
}



void MapRoom::changeTileType(std::string layer, glm::vec2 tilePos, std::string tileID, TileTypeManager *ttmng)
{
	if (layer == "O" || layer == "B")
	{
		roomTiles[layer][tilePos.y][tilePos.x]->setTileType(tileID, ttmng);
		roomTilesStrings[layer][tilePos.y][tilePos.x] = tileID;
	}
	
}



std::unordered_map<std::string, std::vector<std::vector<std::string>>> MapRoom::getRoomTilesStrings()
{
	return roomTilesStrings;
}


std::vector<std::string> MapRoom::getLayerIDs()
{
	return layerIDs;
}
