#pragma once
#include "../InteractiveObject.h"
#include "FoodCollector.h"




class FoodTable : public InteractiveObject
{
public:
	FoodTable(Texture* entTexture, FoodTypeManager* ftm, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));
	~FoodTable();

	void update(float dt);

	void foodTableInit(FoodTypeManager* ftm);


	bool addFood(Food* f, int player);


	//std::vector<FoodStateType*> getFoodsCollected() { return foodsCollected; }

	void clearFood();

protected:
	std::vector<std::vector<Food*>> foodsOnTable;

	std::vector<std::vector<bool>> foodsPresent;

};