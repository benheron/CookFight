#pragma once
#include "../Entity.h"
#include "../Food/FoodTypeManager.h"
#include "../Food/FoodCollector.h"
#include "../../text/Text.h"

class WinCard : public Entity
{
public:
	WinCard(Texture* scoreCardTex, TextImageManager* timng, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));
	~WinCard();

	void winCardInit();

	void setWinner(int playerNum);

	void resetCard();


protected:
	

	TextImageManager* timng;

	std::vector<float> xStateTextPositions;
	std::vector<float> yStateTextPositions;


	std::vector<Text*> foodTypesTextObj;
	std::vector<Text*> foodStatesTextObj;


	std::unordered_map<std::string, std::unordered_map<std::string, Text*>> foodsText;
	int score;

	Text* playerText;
	Text* winsText;

	Text* drawText;

	int winNum;

};