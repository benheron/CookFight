#include "FoodCollector.h"

FoodCollector::FoodCollector(Texture* entTexture, FoodTypeManager* ftm, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) : InteractiveObject(entTexture, pos, dimens, uvSize)
{
	foodCollInit();
}

FoodCollector::~FoodCollector()
{
	clearFood();
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

	FoodStateType *f2 = new FoodStateType(f->getFoodState(), f->getFoodType());



	foodsCollected.push_back(f2);

	return true;
}

void FoodCollector::clearFood()
{

	for (int i = foodsCollected.size()-1; i > -1; i--)
	{
		delete foodsCollected[i];
		//foodsCollected.pop_back();
	}
	foodsCollected.clear();

/*
	for (auto i = foodsCollected.begin(); i != foodsCollected.end(); ) 
	{
		delete foodsCollected[i];
		i = foodsCollected.erase(i);
	}*/
}