#pragma once
#include "text/TextImageManager.h"
#include "levelManagement/TileTypeManager.h"
#include "levelManagement/MapManager.h"
#include "Animation/SpriteSheetManager.h"
#include "Background/BackgroundManager.h"

#include "entities/Food/FoodTypeManager.h"

#include "Audio/AudioManager.h"


#include "Keyboard.h"
#include "input/Gamepad.h"



class PauseState;


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

	AudioManager* getAudioManager() { return amng; }

	Gamepad* getGamepad(int index);

	int getNumGamePads() { return gamePads.size(); }




	FoodTypeManager* getFoodTypeManager() { return ftmng; }

	void setPauseState(PauseState* ps) { paState = ps; }
	PauseState* getPauseState() { return paState; }

protected:

	TileTypeManager* ttmng;
	TextImageManager* timg;
	KeyboardManager* km;
	MapManager* mmng;
	SpriteSheetManager* ssmng;

	BackgroundManager* bgmng;

	AudioManager* amng;


	std::vector<Gamepad*> gamePads;




	PauseState* paState;






	//game specific
	FoodTypeManager* ftmng;



};