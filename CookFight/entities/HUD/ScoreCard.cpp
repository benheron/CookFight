#include "ScoreCard.h"

ScoreCard::ScoreCard(Texture* scoreCardTex, FoodTypeManager* ftm, TextImageManager* timng, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) 
	: Entity(scoreCardTex, pos, dimens, uvSize), timng(timng), ftm(ftm)
{
	scoreCardInit();
}

ScoreCard::~ScoreCard()
{

}

void ScoreCard::scoreCardInit()
{
	score = 0;
	foodTypes = ftm->getFoodTypesVector();
	foodTypesNames = ftm->getFoodTypeNames();

	for (int i = 0; i < foodTypes.size()-1; i++)
	{
		std::string foodTypeName = foodTypes[i]->getID();

		Text* t = new Text(timng, foodTypeName);
		float centX = ((i + 1)*(dimens.x / foodTypes.size())) + pos.x + (dimens.x/25.f);
		float centY = (dimens.y / 8.f);
		t->setCentre(glm::vec3(centX, centY, 0));
		
		t->setBlendColour(glm::vec4(0.f, 0.f, 0.f, 1.f));

		

		children.push_back(t);
		foodTypesTextObj.push_back(t);
	}


	foodStates = ftm->getFoodStates();

	//std::vector<std::string>

	for (int i = 0; i < foodStates.size(); i++)
	{
		std::string foodStateName = foodStates[i];

		Text* t = new Text(timng, foodStateName + ":");
		float centX = (dimens.x / 50.f) + pos.x;
		float centY = ((i + 1)*(dimens.y / 12.f)) + pos.y + (dimens.y / 10.f);
		
		
		t->setPosition(glm::vec3(centX, centY, 0));

		yStateTextPositions.push_back(t->getPosition().y);

		t->setBlendColour(glm::vec4(0.f, 0.f, 0.f, 1.f));

		t->setScale(glm::vec3(0.6));

		children.push_back(t);
		foodStatesTextObj.push_back(t);
	}

	
}

void ScoreCard::addFoodCollected(FoodCollector* fc)
{
	std::vector<Food*> foodsCollected = fc->getFoodsCollected();

	std::unordered_map<std::string, std::vector<Food*>> foodsOrdered;

	std::unordered_map<std::string, std::unordered_map<std::string, int>> foodNums;

	for (int i = 0; i < foodStates.size(); i++)
	{
		for (int j = 0; j < foodTypes.size() - 1; j++)
		{
			foodNums[foodStates[i]][foodTypes[j]->getID()] = 0;
		}
	}

	for (int i = 0; i < foodsCollected.size(); i++)
	{
		foodsOrdered[foodsCollected[i]->getFoodType()->getID()] = foodsCollected;

		//foodNums[foodsCollected[i]->getFoodType()->getID()]++;
		foodNums[foodsCollected[i]->getFoodState()][foodsCollected[i]->getFoodType()->getID()]++;

		std::string ft = foodsCollected[i]->getFoodType()->getID();
		std::string fs = foodsCollected[i]->getFoodState();


		if (ft == "Meat")
		{
			if (fs == "Raw")
			{
				score -= 4;
			}

			if (fs == "Cooked")
			{
				score += 10;
			}
		}
		else if (ft == "Veg")
		{
			if (fs == "Raw")
			{
				score -= 1;
			}

			if (fs == "Cooked")
			{
				score += 3;
			}
		}
		else if (ft == "Fruit")
		{
			if (fs == "Raw")
			{
				score += 1;
			}

			if (fs == "Cooked")
			{
				score += 4;
			}
		}

	}

	std::unordered_map<std::string, std::string> foodNumsText;



	for (int i = 0; i < foodStates.size(); i++)
	{
		//float yPos = ((i + 1)*(dimens.y / 12.f)) + pos.y + (dimens.y / 10.f);
		float yPos = foodStatesTextObj[i]->getPosition().y -7.f;
		//yPos -= (dimens.y / 6.f);
		for (int j = 0; j < foodTypes.size() - 1; j++)
		{
			//float xPos = ((j + 1)*(dimens.x / foodTypes.size())) + pos.x + (dimens.x / 25.f);
			float xPos = foodTypesTextObj[j]->getPosition().x +15.f;
			
			
			std::string xNums = "x" + std::to_string(foodNums[foodStates[i]][foodTypes[j]->getID()]);

			Text* t = new Text(timng, xNums);

			t->setPosition(glm::vec3(xPos, yPos, 0));
			t->setBlendColour(glm::vec4(1.f, 0.f, 0.f, 1.f));
			t->setScale(glm::vec3(0.8f));

			children.push_back(t);
		}
	}


	float centX = (dimens.x / 8.f) + pos.x;
	float centY = (pos.y+dimens.y) - (dimens.y / 8.f);
	std::string scoreText = "Score: " + std::to_string(score);
	
	Text* t = new Text(timng, scoreText);
	t->setPosition(glm::vec3(centX, centY,0));

	children.push_back(t);
}



