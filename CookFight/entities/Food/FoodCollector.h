#pragma once
#include "../InteractiveObject.h"
#include "FoodTypeManager.h"
#include "Food.h"




class FoodCollector : public InteractiveObject
{
public:
	FoodCollector(Texture* entTexture, FoodTypeManager* ftm, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));
	~FoodCollector();

	void update(float dt);

	void foodCollInit();


	bool addFood(Food* f);

	
	std::vector<Food*> getFoodsCollected() { return foodsCollected; }



protected:
	std::vector<Food*> foodsCollected;

};