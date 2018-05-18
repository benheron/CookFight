#include "Projectile.h"

Projectile::Projectile(Texture* entTexture, FoodType* foodTypeGiven, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) : WorldObject(entTexture, pos, dimens, uvSize), foodTypeGiven(foodTypeGiven)
{
	projectileInit();
}


Projectile::Projectile(glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize, glm::vec3 offPos, bool container) : WorldObject(pos, dimens, uvSize, offPos, container)
{
	projectileInit();
}

Projectile::~Projectile()
{

}

void Projectile::update(float dt)
{
	WorldObject::update(dt);

	pos += velocity * dt; 

	if (thrown)
	{
		rotRoll += dt * (abs(velocity.x)+abs(velocity.y))/50;
	}
}

void Projectile::projectileInit()
{
	thrown = false;

	hitboxDimensScale *= 0.6f;
}

void Projectile::calculateYFromHeight()
{

}

void Projectile::setThrown(bool t)
{
	thrown = t;

	if (!t)
	{
		rotRoll = 0;
	}
}
