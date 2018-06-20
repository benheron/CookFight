#include "TextTime.h"

TextTime::TextTime(TextImageManager *timng, TimeTracker* timeTracked, bool colonSpaces, bool showMills) : Entity(), timeTracked(timeTracked), colonSpaces(colonSpaces), showMills(showMills)
{
	textTimeInit(timng);
}

TextTime::~TextTime()
{
	delete timeText;
}

void TextTime::textTimeInit(TextImageManager *timng)
{
	
	timeString = "00 : 00";

	if (showMills)
	{
		timeString += " : 000";
	}

	if (!colonSpaces)
	{
		removeSpaces();
	}
	

	//timeString = "00 : 00 : 000";
	timeText = new Text(pos, "arial", 32, timeString, timng);

	dimens = timeText->getDimensions();
}

void TextTime::update(float dt)
{
	Entity::update(dt);
	timeTracked->update(dt);


	
	float timeToText = timeTracked->getTimeValue();

	int min = timeToText / 60;
	int sec = int(timeToText) % 60;
	int mil = int(timeToText * 1000) % 1000;

	std::string stringMin = min < 10 ? "0" + std::to_string(min) : std::to_string(min);
	std::string stringSec = sec < 10 ? "0" + std::to_string(sec) : std::to_string(sec);
	std::string stringMil;

	if (mil < 10)
	{
		stringMil = "00" + std::to_string(mil);

	}
	else if (mil < 100)
	{
		stringMil = "0" + std::to_string(mil);
	}
	else {
		stringMil = std::to_string(mil);
	}


	timeString = stringMin + " : " + stringSec + " : " + stringMil;

	if (!colonSpaces)
	{
		removeSpaces();
	}

	std::string curDisplayTime = timeText->getText();
	for (int i = 0; i < timeString.length(); i++)
	{
		if (i < curDisplayTime.size())
		{
			std::string cdt = curDisplayTime.substr(i, 1);
			std::string ets = timeString.substr(i, 1);

			if (cdt != ets)
			{
				timeText->changeCharacter(i, timeString.substr(i, 1));
			}
		}
	}
	

}

std::vector<Model*> TextTime::getModels() {
	return timeText->getModels();
}

void TextTime::removeSpaces()
{
	for (int i = 0; i < timeString.size(); i++)
	{
		if (timeString[i] == ' ')
		{
			timeString.erase(i, 1);
		}
	}
}


