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

	hit = false;
	invincible = false;

	flashTimer = 0.f;
	hitStunTimer = 0.f;

}

void Chef::update(float dt)
{
	Actor::update(dt);
	if (invincible)
	{
		invinTimer -= dt;
		flashTimer += dt;
		if (invinTimer <= 0.f)
		{
			invincible = false;
		}

		if (flashTimer > 3.f/60.f)
		{
			flashTimer = 0.f;
			shouldRender = !shouldRender;
		}
		
	}
	else {
		shouldRender = true;
	}

	if (hitStunTimer > 0.f)
	{
		hitStunTimer -= dt;
	}
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