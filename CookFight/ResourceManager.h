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
	ResourceManager(KeyboardManager *km, Gamepad *gp);
	~ResourceManager();

	void initResources();


	TextImageManager* getTextImageManager();

	KeyboardManager* getKeyboardManager();

	TileTypeManager* getTileTypeManager();

	MapManager* getMapManager();

	SpriteSheetManager* getSpriteSheetManager();

	BackgroundManager* getBackgroundManager();

	Gamepad* getGamepad();




	FoodTypeManager* getFoodTypeManager() { return ftmng; }

protected:

	TileTypeManager* ttmng;
	TextImageManager* timg;
	KeyboardManager* km;
	MapManager* mmng;
	SpriteSheetManager* ssmng;

	BackgroundManager* bgmng;


	Gamepad* gp;











	//game specific
	FoodTypeManager* ftmng;



};