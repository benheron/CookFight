#pragma  once

#include "../InteractiveObject.h"
#include "FoodType.h"

class FoodBox : public InteractiveObject
{

public:
	FoodBox(Texture* entTexture, FoodType* foodTypeGiven, std::string foodState, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));

	/**
	@brief Entity constructor with  position, dimensions, uvsize of an individual element and whether or not it is a container
	*/
	FoodBox(glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0), glm::vec3 offPos = glm::vec3(0), bool container = false);

	~FoodBox();

	void foodBoxInit();

	//void updatePickupBoxMatrix();

	virtual void update(float dt);

	//BoundingBox* getItemPickUpBox() { return itemPickUpBox; }

	FoodType* getFoodTypeGiven() { return foodTypeGiven; }

	void setFoodState(std::string fs) { foodState = fs; }

	std::string getFoodState() { return foodState; }

protected:
	glm::vec3 itemPickUpScale;

	BoundingBox *itemPickUpBox;

	FoodType* foodTypeGiven;

	std::string foodState;
};