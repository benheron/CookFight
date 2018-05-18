#include "ResourceManager.h"

ResourceManager::ResourceManager(KeyboardManager *km, Gamepad *gp) : km(km), gp(gp)
{
	initResources();
}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::initResources()
{
	timg = new TextImageManager("res/fonts/fontarial.txt");
	ttmng = new TileTypeManager("res/txt/tiles.txt");
	mmng = new MapManager("res/txt/map1.txt", ttmng);

	std::string playerCharSpriteSheet = "res/txt/chefcop.txt";

	ssmng = new SpriteSheetManager(playerCharSpriteSheet);
	
	bgmng = new BackgroundManager("res/txt/backgrounds.txt");




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

Gamepad* ResourceManager::getGamepad()
{
	return gp;
}