#include "Food.h"

Food::Food(SpriteSheet* foodSpriteSheet, FoodType* foodType, std::string foodState, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) : Entity(foodSpriteSheet->getTexture(), pos, dimens, uvSize), foodSpriteSheet(foodSpriteSheet), foodType(foodType), foodState(foodState)
{

}


Food::Food(glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize, glm::vec3 offPos, bool container) : Entity(pos, dimens, uvSize, offPos, container)
{

}

Food::~Food()
{

}

void Food::update(float dt)
{
	Entity::update(dt);
}

glm::vec2 Food::getTextureUVOffset()
{
	return foodType->getSpriteOffset(foodState);
}

void Food::setFoodType(FoodType* ft)
{
	foodType = ft;

	if (ft->getID() == "None")
	{
		shouldRender = false;
	}
	else {
		shouldRender = true;
	}
}