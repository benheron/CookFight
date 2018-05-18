#include "FoodBox.h"

FoodBox::FoodBox(Texture* entTexture, FoodType* foodTypeGiven, std::string foodState, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) : InteractiveObject(entTexture, pos, dimens, uvSize), foodTypeGiven(foodTypeGiven), foodState(foodState)
{
	foodBoxInit();
}


FoodBox::FoodBox(glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize, glm::vec3 offPos, bool container) : InteractiveObject(pos, dimens, uvSize, offPos, container)
{
	foodBoxInit();
}

FoodBox::~FoodBox()
{

}

void FoodBox::update(float dt)
{
	InteractiveObject::update(dt);
}

void FoodBox::foodBoxInit()
{
	
}
/*

void FoodBox::updatePickupBoxMatrix()
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
	mm = glm::scale(mm, itemPickUpScale);


	itemPickUpBox->transformByMat4(mm);
}*/