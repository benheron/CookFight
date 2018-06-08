#include "InteractiveObject.h"

InteractiveObject::InteractiveObject(Texture* entTexture, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) : WorldObject(entTexture, pos, dimens, uvSize)
{
	interactInit();
}


InteractiveObject::InteractiveObject(glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize, glm::vec3 offPos, bool container) : WorldObject(pos, dimens, uvSize, offPos, container)
{
	interactInit();
}

InteractiveObject::~InteractiveObject()
{

}

void InteractiveObject::update(float dt)
{
	WorldObject::update(dt);
	updateInteractHitboxMatrix();
}

void InteractiveObject::interactInit()
{
	interactHitboxScale = dimensScale*1.2f;

	interactHitbox = new BoundingBox(glm::vec3(-1.f, -1.f, 0), glm::vec3(1.f, 1.f, 0));

	updateInteractHitboxMatrix();
}

void InteractiveObject::updateInteractHitboxMatrix()
{
	glm::mat4 mm = glm::mat4(1.0);

	glm::vec3 jointPos = pos + offsetPos + hitboxPosRel;

	mm = glm::translate(mm, jointPos);

	//rotate x
	mm = glm::rotate(mm, rotPitch, glm::vec3(1, 0, 0));
	//rotate y
	mm = glm::rotate(mm, rotYaw, glm::vec3(0, 1, 0));
	//rotate z
	mm = glm::rotate(mm, rotRoll, glm::vec3(0, 0, 1));

	//scale
	mm = glm::scale(mm, interactHitboxScale);


	interactHitbox->transformByMat4(mm);
}


void InteractiveObject::setPosition(glm::vec3 p, bool add)
{
	Entity::setPosition(p, add);
	updateInteractHitboxMatrix();
}


void InteractiveObject::setCentre(glm::vec3 p)
{
	Entity::setCentre(p);
	updateInteractHitboxMatrix();
}