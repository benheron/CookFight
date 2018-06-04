#include "Button.h"

Button::Button(Texture* buttonTexture, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) : 
	Entity(buttonTexture, pos, dimens, uvSize), action("")
{
	
	initButton();
}

Button::Button(std::string action, Texture* buttonTexture, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize) : 
	Entity(buttonTexture, pos, dimens, uvSize), action(action)
{
	initButton();
}

Button::~Button()
{

}

void Button::initButton()
{
	butState = buttonIdle;
}

glm::vec2 Button::getTextureUVOffset()
{
	glm::vec2 uvo;
	switch (butState)
	{
	case buttonIdle:
		uvo = glm::vec2(0, 0);
		break;
	case buttonHighlight:
		uvo = glm::vec2(0, uvSize.y);
		break;
	default:
		uvo = glm::vec2(0, 0);
		break;
	}

	return uvo;
}