
#pragma once
#include "../Entity.h"
#include "../../Animation/SpriteSheet.h"
#include "../Food/Food.h"

class ItemSlot : public Entity
{
public:
	ItemSlot(Texture* entTexture, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));

	/**
	@brief Entity constructor with  position, dimensions, uvsize of an individual element and whether or not it is a container
	*/
	ItemSlot(Texture* entTexture, Food* foodItem, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));

	~ItemSlot();

	void itemSlotInit();

	virtual void update(float dt);

	
	//virtual glm::vec2 getTextureUVOffset();

	Food *getFoodItem() { return foodItem; }

protected:
	Food *foodItem;


};