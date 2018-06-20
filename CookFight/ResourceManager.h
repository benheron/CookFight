#pragma once
#include "text/TextImageManager.h"
#include "levelManagement/TileTypeManager.h"
#include "levelManagement/MapManager.h"
#include "Animation/SpriteSheetManager.h"
#include "Background/BackgroundManager.h"

#include "entities/Food/FoodTypeManager.h"

#include "TextureManager.h"
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

	TextureManager* getTextureManager() { return tmng; }

	Gamepad* getGamepad(int index);

	int getNumGamePads() { return gamePads.size(); }




	FoodTypeManager* getFoodTypeManager() { return ftmng; }

	void setPauseState(PauseState* ps) { paState = ps; }
	PauseState* getPauseState() { return paState; }


	void addGamepad(Gamepad* gp);
	void removeGamepad(int index);

	void addGamepadToMap(Gamepad* gp, int key) { gamepadsMap[key] = gp; }
	void removeGamepadFromMap(int key) { gamepadsMap.erase(key); }

	Gamepad* getGamepadFromMap(int key) { return gamepadsMap[key]; }

	std::unordered_map<int, Gamepad*> getGamePadMap() { return gamepadsMap; }

protected:

	TileTypeManager* ttmng;
	TextImageManager* timg;
	KeyboardManager* km;
	MapManager* mmng;
	SpriteSheetManager* ssmng;

	BackgroundManager* bgmng;

	AudioManager* amng;

	TextureManager* tmng;


	std::vector<Gamepad*> gamePads;


	std::unordered_map<int, Gamepad*> gamepadsMap;


	PauseState* paState;






	//game specific
	FoodTypeManager* ftmng;



};