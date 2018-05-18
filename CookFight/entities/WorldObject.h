#pragma  once

#include "Entity.h"

class WorldObject : public Entity
{

public:
	WorldObject(Texture* entTexture, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));

	/**
	@brief Entity constructor with  position, dimensions, uvsize of an individual element and whether or not it is a container
	*/
	WorldObject(glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0), glm::vec3 offPos = glm::vec3(0), bool container = false);

	~WorldObject();

	virtual void update(float dt);


	float getStaticFriction() { return staticFriction; }

	float getDynamicFriction() { return dynamicFriction; }

protected:

	float staticFriction;
	float dynamicFriction;


};