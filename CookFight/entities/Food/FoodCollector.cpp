#include "FoodCollector.h"

FoodCollector::FoodCollector(Texture* entTexture, FoodTypeManager* ftm, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) : InteractiveObject(entTexture, pos, dimens, uvSize)
{
	foodCollInit();
}

FoodCollector::~FoodCollector()
{

}

void FoodCollector::foodCollInit()
{
	
}

void FoodCollector::update(float dt)
{
	InteractiveObject::update(dt);
}

bool FoodCollector::addFood(Food* f)
{

	Food *f2 = new Food(*f);

	foodsCollected.push_back(f2);

	return true;
}

