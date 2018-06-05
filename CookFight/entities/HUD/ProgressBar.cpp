#include "ProgressBar.h"

ProgressBar::ProgressBar(Texture* barTexture, Texture* outline, glm::vec3 pos, glm::vec3 dimens, glm::vec2 uvSize)
	: Entity(barTexture, pos, dimens, uvSize), maxDimens(dimens)
{
	progBarInit(outline);
}


ProgressBar::~ProgressBar()
{

}

void ProgressBar::progBarInit(Texture* outline)
{
	setProgressValue(0.f);
	//blendColour = glm::vec4(1.0f, 0.f, 0.f, 1.f);

	

	outlineEnt = new Entity(outline, pos);
	colouredBar = new Entity(entTextures[0], pos);
	colouredBar->setDimens(maxDimens);

	colouredBar->setBlendColour(glm::vec4(.0f, .0f, .0f, 0.5f));

	children.push_back(colouredBar);
	children.push_back(outlineEnt);
	
}

void ProgressBar::update(float dt)
{
	Entity::update(dt);

	
}

void ProgressBar::setProgressValue(float val, bool add)
{
	if (add)
	{
		progressValue += val;
	}
	else
	{
		progressValue = val;
	}

	if (progressValue > 100.f)
	{
		progressValue = 100.f;

	}
	

	glm::vec3 newDimens = glm::vec3(maxDimens.x * (progressValue / 100.f), maxDimens.y, 0);
	setDimens(newDimens);

	

	updateModelMatrix();
	updateBoundingBoxMatrix();
}

void ProgressBar::setCentre(glm::vec3 p)
{
	setPosition(p - (maxDimens / 2.f));
}