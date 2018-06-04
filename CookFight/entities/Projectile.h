#pragma  once

#include "WorldObject.h"
#include "Food/FoodType.h"
#include "Food/Food.h"

class Projectile : public WorldObject
{

public:
	Projectile(Texture* entTexture, Food* foodGiven, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));


	/**
	@brief Entity constructor with  position, dimensions, uvsize of an individual element and whether or not it is a container
	*/
	Projectile(glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0), glm::vec3 offPos = glm::vec3(0), bool container = false);

	~Projectile();

	void projectileInit();

	void setThrown(bool t);
	bool getThrown() { return thrown; }

	
	virtual void update(float dt);

	void setProjectileFood(Food* f) { foodGiven = f; foodTypeGiven = f->getFoodType(); foodState = f->getFoodState(); }
	FoodType* getFoodTypeGiven() { return foodTypeGiven; }

	/**
	@brief
	*/
	virtual glm::vec2 getTextureUVOffset();

protected:

	void calculateYFromHeight();

	FoodType* foodTypeGiven;

	std::string foodState;

	Food* foodGiven;

	bool thrown;

	float height;
};