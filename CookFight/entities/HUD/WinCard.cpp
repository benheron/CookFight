#include "WinCard.h"

WinCard::WinCard(Texture* scoreCardTex, TextImageManager* timng, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize)
	: Entity(scoreCardTex, pos, dimens, uvSize), timng(timng)
{
	winCardInit();
}

WinCard::~WinCard()
{

}

void WinCard::winCardInit()
{
	std::string playerString = "PLAYER 0";
	std::string winsString = "WINS!";

	std::string drawString = "DRAW!";

	
	playerText = new Text(timng, playerString);
	float ptCentX = (pos.x + dimens.x) / 2.f;
	float ptCentY = pos.y + (dimens.y / 9.f);
	playerText->setCentre(glm::vec3(ptCentX, ptCentY, 0));

	children.push_back(playerText);

	winsText = new Text(timng, winsString);
	float wCentY = playerText->getPosition().y + playerText->getDimensions().y + (dimens.y / 16.f);
	winsText->setCentre(glm::vec3(ptCentX, wCentY, 0));

	children.push_back(winsText);


	drawText = new Text(timng, drawString);
	//float dCentY = playerText->getPosition().y + playerText->getDimensions().y + (dimens.y / 16.f);
	drawText->setCentre(glm::vec3(ptCentX, ptCentY, 0));

	children.push_back(drawText);

	resetCard();
}

void WinCard::setWinner(int playerNum)
{
	if (playerNum == -1)
	{
		drawText->setShouldRender(true);

		playerText->setShouldRender(false);
		winsText->setShouldRender(false);
	}
	else {
		playerText->setShouldRender(true);
		winsText->setShouldRender(true);

		drawText->setShouldRender(false);

		playerText->changeCharacter(7, std::to_string(playerNum + 1));
	}
	
}

void WinCard::resetCard()
{
	playerText->setShouldRender(false);
	winsText->setShouldRender(false);
	drawText->setShouldRender(false);

	//playerText->changeCharacter(7,"0");
}

