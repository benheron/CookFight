#pragma  once

#include "WorldObject.h"
#include "Food/FoodType.h"

class Projectile : public WorldObject
{

public:
	Projectile(Texture* entTexture, FoodType* foodTypeGiven, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));

	/**
	@brief Entity constructor with  position, dimensions, uvsize of an individual element and whether or not it is a container
	*/
	Projectile(glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0), glm::vec3 offPos = glm::vec3(0), bool container = false);

	~Projectile();

	void projectileInit();

	void setThrown(bool t);
	bool getThrown() { return thrown; }

	
	virtual void update(float dt);


	FoodType* getFoodTypeGiven() { return foodTypeGiven; }



protected:

	void calculateYFromHeight();

	FoodType* foodTypeGiven;

	bool thrown;

	float height;
};