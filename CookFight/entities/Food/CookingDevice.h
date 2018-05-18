#pragma once
#include "../InteractiveObject.h"
#include "FoodTypeManager.h"
#include "Food.h"

#include "../../Utilities/Time/Timer.h"




class CookingDevice : public InteractiveObject
{
public:
	CookingDevice(Texture* entTexture, Texture* iconTexture, FoodTypeManager* ftm, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));
	CookingDevice(FoodTypeManager* ftm, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0), glm::vec3 offPos = glm::vec3(0), bool container = false);
	~CookingDevice();

	void update(float dt);
	
	void cookDevInit(FoodTypeManager* ftm, Texture* iconTexture);


	bool addFood(Food* f);

	void getFood(Food* f);
	




protected:
	bool isCooking;

	std::vector<Food*> foodsInDevice;

	std::vector<Timer*> cookingTimers;
};