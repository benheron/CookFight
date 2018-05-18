#pragma  once

#include "WorldObject.h"

class InteractiveObject : public WorldObject
{

public:
	InteractiveObject(Texture* entTexture, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));

	/**
	@brief Entity constructor with  position, dimensions, uvsize of an individual element and whether or not it is a container
	*/
	InteractiveObject(glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0), glm::vec3 offPos = glm::vec3(0), bool container = false);

	~InteractiveObject();

	/**
	@brief Initialise interactive object variables
	*/
	void interactInit();

	/**
	@brief Updates the interactive hitbox size, rotation and scale
	*/
	void updateInteractHitboxMatrix();

	/**
	@brief
	*/
	virtual void update(float dt);

	/**
	@brief Gets the bounding box for the interactive element
	@returns The interactive bounding box
	*/
	BoundingBox* getInteractBoundingBox() { return interactHitbox; }


protected:
	///The scale of the interactive bounding box
	glm::vec3 interactHitboxScale;

	///Boundingbox for the interactive zone
	BoundingBox *interactHitbox;


};