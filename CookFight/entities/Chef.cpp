#include "Chef.h"

Chef::Chef(SpriteSheet* actorSpriteSheet, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) : Actor(actorSpriteSheet, pos, dimens, uvSize)
{
	chefInit();
}


Chef::Chef(glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize, glm::vec3 offPos, bool container) : Actor(pos, dimens, uvSize, offPos, container)
{
	chefInit();
}

Chef::~Chef()
{

}

void Chef::chefInit()
{
	maxHealth = 50;
	health = maxHealth;


}

void Chef::setFoodHeld(Food *f)
{
	foodHeld = f;
	if (foodHeld->getFoodType()->getID() == "None")
	{
		foodHeld->setShouldRender(false);
	} else {
		foodHeld->setShouldRender(true);
	}
}

void Chef::setFoodHeldType(FoodType* ft) 
{ 
	foodHeld->setFoodType(ft); 

	if (ft->getID() == "None")
	{
		foodHeld->setShouldRender(false);
	}
	else {
		foodHeld->setShouldRender(true);
	}
}

void Chef::setHealth(int h, bool add)
{
	if (add)
	{
		health += h;
	}
	else {
		health = h;
	}

	if (health > maxHealth)
	{
		health = maxHealth;
	}

	if (health < 0)
	{
		health = 0;
	}
}