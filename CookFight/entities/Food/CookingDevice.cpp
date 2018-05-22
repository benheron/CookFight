#include "CookingDevice.h"

CookingDevice::CookingDevice(Texture* entTexture, Texture* iconTexture, ProgressBar* pb, FoodTypeManager* ftm,  glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) : InteractiveObject(entTexture, pos, dimens, uvSize), cookProgBar(pb)
{
	cookDevInit(ftm, iconTexture);
}

CookingDevice::CookingDevice(FoodTypeManager* ftm, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize, glm::vec3 offPos, bool container) : InteractiveObject(pos, dimens, uvSize, offPos, container)
{
	///cookDevInit(ftm);
}

CookingDevice::~CookingDevice()
{

}

void CookingDevice::cookDevInit(FoodTypeManager* ftm, Texture* iconTexture)
{
	cookingTimer = new Timer();

	int maxNumFood = 1;
	for (int i = 0; i < maxNumFood; i++)
	{
		foodsInDevice.push_back(new Food(ftm->getFoodSpriteSheet(), 
			ftm->getFoodType("None"), "Raw", glm::vec3(-20, -20, -20), ftm->getFoodTypeSize()));		
	}

	for (int i = 0; i < maxNumFood; i++)
	{
		Entity* ico = new Entity(iconTexture, pos + glm::vec3((20+2) * i, -30, 0));
		ico->setShouldRender(false);
		children.push_back(ico);


	}

	isCooking = false;


	cookProgBar->setCentre(getCentrePosition());

	cookProgBar->setPosition(glm::vec3(0, -25, 0), true);
	cookProgBar->setShouldRender(false);
	cookProgBar->setBlendColour(glm::vec4(1.0f, 0.f, 0.f, 1.f));
	children.push_back(cookProgBar);
	
}

void CookingDevice::update(float dt)
{
	InteractiveObject::update(dt);

	for (int i = 0; i < foodsInDevice.size(); i++)
	{
		cookingTimer->update(dt);
		cookProgBar->setProgressValue(100.f-cookingTimer->getPercentLeft());

		if (cookingTimer->getTimerFinished())
		{
			foodsInDevice[i]->setFoodState("Cooked");
			cookingTimer->stopTrackingTime();
			cookProgBar->setBlendColour(glm::vec4(0.0f, 1.f, 0.f, 1.f));
		}

		if (foodsInDevice[i]->getFoodState() == "Cooked")
		{
			std::string id = foodsInDevice[i]->getFoodType()->getID();
			Entity *thisChild = children[i];

			if (id == "Meat")
			{
				thisChild->setBlendColour(glm::vec4(0.737f, 0.462f, 0.122f, 1));
			}
			else if (id == "Veg")
			{
				thisChild->setBlendColour(glm::vec4(0.62f, 0.31f, 0.0f, 1));
			}
			else if (id == "Fruit")
			{
				thisChild->setBlendColour(glm::vec4(0.478f, 0.0f, 0.0f, 1));
			}
		}
	}
}

bool CookingDevice::addFood(Food* f)
{

	std::string fs = f->getFoodState();
	FoodType* ft = f->getFoodType();
	bool addedFood = false;
	if (fs == "Raw")
	{
		for (int i = 0; i < foodsInDevice.size(); i++)
		{
			if (foodsInDevice[i]->getFoodType()->getID() == "None")
			{
				foodsInDevice[i]->setFoodType(ft);
				foodsInDevice[i]->setFoodState(fs);




				addedFood = true;

				std::string id = ft->getID();
				Entity *thisChild = children[i];



				if (id == "Meat")
				{
					thisChild->setBlendColour(glm::vec4(1.f, 0.43f, 0.78f, 1));
					cookingTimer->setTimer(0, 5, 0);
				}
				else if (id == "Veg")
				{
					thisChild->setBlendColour(glm::vec4(0.99f, 0.42f, 0.007f, 1));
					cookingTimer->setTimer(0, 5, 0);
				}
				else if (id == "Fruit")
				{
					thisChild->setBlendColour(glm::vec4(1.f, 0, 0, 1));
					cookingTimer->setTimer(0, 5, 0);
				}
				thisChild->setShouldRender(true);
				cookProgBar->setShouldRender(true);
				cookProgBar->setBlendColour(glm::vec4(1.0f, 0.f, 0.f, 1.f));

				cookingTimer->startTrackingTime();

				break;
			}
		}
	}
	
	return addedFood;
}


void CookingDevice::getFood(Food* f)
{

	std::string fs = f->getFoodState();
	FoodType* ft = f->getFoodType();

	f->setFoodType(foodsInDevice[0]->getFoodType());
	f->setFoodState(foodsInDevice[0]->getFoodState());


	cookingTimer->setTimer();
	cookProgBar->setShouldRender(false);

	foodsInDevice[0]->setFoodType(ft);
	foodsInDevice[0]->setFoodState(fs);

	children[0]->setShouldRender(false);

}
