#pragma once
#include "../Entity.h"

class ProgressBar : public Entity
{
public:
	ProgressBar(Texture* barTexture, Texture* outline, glm::vec3 pos = glm::vec3(0), glm::vec3 dimens = glm::vec3(0), glm::vec2 uvSize = glm::vec2(0));
	~ProgressBar();

	void progBarInit(Texture* barTexture);

	void setProgressValue(float val, bool add = false);

	virtual void update(float dt);

	virtual void setCentre(glm::vec3 p);

	virtual void setBlendColour(glm::vec4 bc) { colouredBar->setBlendColour(bc); }

	void setBackgroundBlendColour(glm::vec4 bc) { blendColour = bc; }

protected:
	Entity *outlineEnt;
	Entity *colouredBar;

	float progressValue;

	glm::vec3 maxDimens;

};