#pragma once
#include "Actor.h"
#include "Food/Food.h"

class Chef : public Actor
{
public:
	Chef(SpriteSheet* actorSpriteSheet, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));

	Chef(glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0), glm::vec3 offPos = glm::vec3(0), bool container = false);
	~Chef();

	void chefInit();
	void setFoodHeldType(FoodType* ft);

	void setFoodHeld(Food *f);

	Food* getFoodHeld() { return foodHeld; }

	void setFoodHeldState(std::string fs) { foodHeld->setFoodState(fs); }

	std::string getFoodHeldState() { return foodHeld->getFoodState(); }


protected:
	Food *foodHeld;

};