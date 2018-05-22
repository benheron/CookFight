#pragma once
#include "text/TextImageManager.h"
#include "levelManagement/TileTypeManager.h"
#include "levelManagement/MapManager.h"
#include "Animation/SpriteSheetManager.h"
#include "Background/BackgroundManager.h"

#include "entities/Food/FoodTypeManager.h"


#include "Keyboard.h"
#include "input/Gamepad.h"

class ResourceManager
{
public:
	ResourceManager(KeyboardManager *km, std::vector<Gamepad*> gamePads);
	~ResourceManager();

	void initResources();


	TextImageManager* getTextImageManager();

	KeyboardManager* getKeyboardManager();

	TileTypeManager* getTileTypeManager();

	MapManager* getMapManager();

	SpriteSheetManager* getSpriteSheetManager();

	BackgroundManager* getBackgroundManager();

	Gamepad* getGamepad(int index);

	int getNumGamePads() { return gamePads.size(); }




	FoodTypeManager* getFoodTypeManager() { return ftmng; }

protected:

	TileTypeManager* ttmng;
	TextImageManager* timg;
	KeyboardManager* km;
	MapManager* mmng;
	SpriteSheetManager* ssmng;

	BackgroundManager* bgmng;


	std::vector<Gamepad*> gamePads;











	//game specific
	FoodTypeManager* ftmng;



};