#include "ItemSlot.h"

ItemSlot::ItemSlot(Texture* entTexture, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) : Entity(entTexture, pos, dimens, uvSize)
{

}


ItemSlot::ItemSlot(Texture* entTexture, Food* foodItem, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) :
	Entity(entTexture, pos, dimens, uvSize), foodItem(foodItem)
{
	children.push_back(foodItem);
}

ItemSlot::~ItemSlot()
{

}

void ItemSlot::update(float dt)
{
	Entity::update(dt);
}

void ItemSlot::itemSlotInit()
{
	foodItem = new Food();
}

/*
glm::vec2 ItemSlot::getTextureUVOffset()
{
	return glm::vec2(0);
}*/