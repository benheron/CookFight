#pragma once
#include "../../text/Text.h"
#include "../../Utilities/Time/TimeTracker.h"

class TextTime : public Entity
{
public:
	TextTime(TextImageManager *timng, TimeTracker* tt);
	~TextTime();

	void textTimeInit(TextImageManager *timng);

	virtual void update(float dt);

	virtual std::vector<Model*> getModels();

	virtual Texture* getTexture(int index) { return timeText->getTexture(index); }

	void startTime() { timeTracked->startTrackingTime(); }

	void stopTime() { timeTracked->stopTrackingTime(); }

private:
	std::string timeString;
	Text* timeText;

	TimeTracker* timeTracked;
};