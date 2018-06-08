#pragma once
#include "../Entity.h"

///Button States
enum ButtonState
{
	buttonHighlight,
	buttonIdle
};


class Button : public Entity
{
public:
	Button(Texture* buttonTexture, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));
	Button(std::string action, Texture* buttonTexture, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));
	~Button();

	void initButton();

	virtual glm::vec2 getTextureUVOffset();


	void setButtonState(ButtonState bs) { butState = bs; }
	ButtonState getButtonState() { return butState; }

	std::string getAction() { return action;  }
protected:
	///The state of the button
	ButtonState butState;

	///String of the action of the button
	std::string action;
};