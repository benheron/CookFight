#pragma once
#include "Actor.h"
#include "Food/Food.h"
#include "Projectile.h"

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

	void addProjectile(Projectile* p) { projectiles.push_back(p); }

	void removeProjectile(int index) { projectiles.erase(projectiles.begin() + index); }

	std::vector<Projectile*> getChefProjectiles() { return projectiles; }

	int getHealth() { return health; }

	int getMaxHealth() { return maxHealth; }


	void setHealth(int h, bool add = false);

	void setFullHealth() { health = maxHealth; }

	void reduceHealth(int h) { health -= h; }

	void addHealth(int h) { health += h; }

protected:
	Food *foodHeld;

	int maxHealth;

	int health;

	std::vector<Projectile*> projectiles;

	
};