
#include "states/PauseState.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager(KeyboardManager *km, std::vector<Gamepad*> gamePads) : km(km), gamePads(gamePads)
{
	initResources();
}

ResourceManager::~ResourceManager()
{
	delete ttmng;
	delete timg;
	delete km;
	delete mmng;
	delete ssmng;
	delete bgmng;

	for (int i = gamePads.size() - 1; i > -1; i--)
	{
		delete gamePads[i];
	}
}

void ResourceManager::initResources()
{
	timg = new TextImageManager("res/fonts/fontarial.txt");
	ttmng = new TileTypeManager("res/txt/tiles.txt");
	mmng = new MapManager("res/txt/map1.txt", ttmng);

	std::string playerCharSpriteSheet = "res/txt/chefcop.txt";

	ssmng = new SpriteSheetManager(playerCharSpriteSheet);

	bgmng = new BackgroundManager("res/txt/backgrounds.txt");


	amng = new AudioManager("res/txt/audio.txt");

	ftmng = new FoodTypeManager("res/txt/food.txt");

}

TextImageManager* ResourceManager::getTextImageManager()
{
	return timg;
}


KeyboardManager* ResourceManager::getKeyboardManager()
{
	return km;
}

TileTypeManager* ResourceManager::getTileTypeManager()
{
	return ttmng;
}

MapManager* ResourceManager::getMapManager()
{
	return mmng;
}

SpriteSheetManager* ResourceManager::getSpriteSheetManager()
{
	return ssmng;
}

BackgroundManager* ResourceManager::getBackgroundManager()
{
	return bgmng;
}

Gamepad* ResourceManager::getGamepad(int index)
{
	return gamePads[index];
}