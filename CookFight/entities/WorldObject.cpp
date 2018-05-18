#include "WorldObject.h"

WorldObject::WorldObject(Texture* entTexture, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) : Entity(entTexture, pos, dimens, uvSize)
{

}


WorldObject::WorldObject(glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize, glm::vec3 offPos, bool container) : Entity(pos, dimens, uvSize, offPos, container)
{

}

WorldObject::~WorldObject()
{

}

void WorldObject::update(float dt)
{
	Entity::update(dt);
}