#pragma once
#include "../Entity.h"
#include "../Food/FoodTypeManager.h"
#include "../Food/FoodCollector.h"
#include "../../text/Text.h"

class ScoreCard : public Entity
{
public:
	ScoreCard(Texture* scoreCardTex, FoodTypeManager* ftm, TextImageManager* timng, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));
	~ScoreCard();

	void scoreCardInit();

	void addFoodCollected(FoodCollector* fc);

	void resetScore() { score = 0; }
	

protected:
	std::vector<FoodType*> foodTypes;
	std::vector<std::string> foodTypesNames;
	std::vector<std::string> foodStates;

	TextImageManager* timng;
	FoodTypeManager* ftm;

	std::vector<float> xStateTextPositions;
	std::vector<float> yStateTextPositions;


	std::vector<Text*> foodTypesTextObj;
	std::vector<Text*> foodStatesTextObj;


	std::unordered_map<std::string, std::unordered_map<std::string, Text*>> foodsText;
	int score;

	Text* scoreTextObj;

};