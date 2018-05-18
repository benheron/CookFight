#pragma once
#include "../Entity.h"
#include "../../Animation/SpriteSheet.h"
#include "FoodType.h"

class Food : public Entity
{
public:
	Food(SpriteSheet* foodSpriteSheet, FoodType* foodType, std::string foodState, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));

	/**
	@brief Entity constructor with  position, dimensions, uvsize of an individual element and whether or not it is a container
	*/
	Food(glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0), glm::vec3 offPos = glm::vec3(0), bool container = false);

	~Food();

	virtual void update(float dt);

	void setFoodType(FoodType* ft);

	FoodType* getFoodType() { return foodType; }

	void setFoodState(std::string fs) { foodState = fs; }

	std::string getFoodState() { return foodState; }

	virtual glm::vec2 getTextureUVOffset();

protected:
	SpriteSheet* foodSpriteSheet;

	FoodType* foodType;

	std::string foodState;

};