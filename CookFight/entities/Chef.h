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

	virtual void update(float dt);

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

	bool getHit() { return hit; }

	void setHit(bool h) { hit = h; invincible = true; invinTimer = 1.5f; }

	bool getInvincible() { return invincible; }

	void setInvincible(bool i) { invincible = i; }

	void setHitStunTimer(float hst) { hitStunTimer = hst; }

	float getHitStunTimer() { return hitStunTimer; }


	

protected:
	Food *foodHeld;

	int maxHealth;

	int health;

	std::vector<Projectile*> projectiles;

	bool hit;

	bool invincible;

	float hitTimer;

	float invinTimer;

	float flashTimer;

	float hitStunTimer;


	
	
};