#include "FoodTable.h"

FoodTable::FoodTable(Texture* entTexture, FoodTypeManager* ftm, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) : InteractiveObject(entTexture, pos, dimens, uvSize)
{
	foodTableInit(ftm);
}

FoodTable::~FoodTable()
{
	clearFood();
}

void FoodTable::foodTableInit(FoodTypeManager* ftm)
{
	int numPlayers = 2;
	int tableFoods = 3;
	for (int i = 0; i < numPlayers; i++)
	{
		std::vector<Food*> f;
		foodsOnTable.push_back(f);

		std::vector<bool> b;
		foodsPresent.push_back(b);

		for (int j = 0; j < tableFoods; j++)
		{
			std::string foodType;

			switch (j)
			{
			case 0:
				foodType = "Meat";
				break;
			case 1:
				foodType = "Veg";
				break;

			case 2:
				foodType = "Fruit";
				break;
			default:

				break;
			}

			foodsOnTable[i].push_back(new Food(ftm->getFoodSpriteSheet(),
				ftm->getFoodType(foodType), "Cooked", glm::vec3(0), glm::vec3(22, 22, 0)));

			float feetHeight = 17.f;

			glm::vec3 foodPosCent = glm::vec3(pos.x + (dimens.x / 4.f) * ((2 * i) + 1) -0.5f, pos.y + ((dimens.y- feetHeight)/ 6.f) * ((2 * j) + 1), 0);
			foodsOnTable[i][j]->setCentre(foodPosCent);

			foodsOnTable[i][j]->setBlendColour(glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));

			children.push_back(foodsOnTable[i][j]);

			foodsPresent[i].push_back(false);
		}
	}
	
	
}

void FoodTable::update(float dt)
{
	InteractiveObject::update(dt);
}

bool FoodTable::addFood(Food* f, int player)
{
	bool retVal = false;

	if (f->getFoodState() == "Cooked")
	{
		std::string foodName = f->getFoodType()->getID();

		if (foodName == "Meat")
		{
			if (foodsPresent[player][0] == false)
			{
				foodsOnTable[player][0]->setBlendColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
				foodsPresent[player][0] = true;
				retVal = true;
			}
		}
		else if (foodName == "Veg")
		{
			if (foodsPresent[player][1] == false)
			{
				foodsOnTable[player][1]->setBlendColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
				foodsPresent[player][1] = true;
				retVal = true;
			}
		}
		else if (foodName == "Fruit")
		{
			if (foodsPresent[player][2] == false)
			{
				foodsOnTable[player][2]->setBlendColour(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
				foodsPresent[player][2] = true;
				retVal = true;
			}
		}
	}


	return retVal;
}

void FoodTable::clearFood()
{
	for (int i = 0; i < foodsOnTable.size(); i++)
	{
		for (int j = 0; j < foodsOnTable[0].size(); j++)
		{
			foodsOnTable[i][j]->setBlendColour(glm::vec4(1.0f, 1.0f, 1.0f, 0.5f));
			foodsPresent[i][j] = false;
		}
	}

}