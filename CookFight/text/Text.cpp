#include "Text.h"

Text::Text(glm::vec3 pos, std::string fontName, int fontSize, std::string theText, TextImageManager *timng) : Entity(pos),
fontName(fontName), fontSize(fontSize), theText(theText), timng(timng)
{
	textInit();
}

Text::Text(TextImageManager *timng, std::string theText, int fontSize, std::string fontName, glm::vec3 pos) : Entity(pos),
fontName(fontName), fontSize(fontSize), theText(theText), timng(timng)
{
	textInit();
}

Text::~Text()
{
	for (int i = 0; i < textString.size(); i++)
	{
		delete textString[i];
	}
}

void Text::textInit()
{
	spacing = 0;
	writeText();
	origPos = pos;
	alignment = leftAlign;


	entTextures.push_back(timng->getFontByName(fontName));
}

void Text::writeText()
{
	int stringLength = theText.length();



	for (int i = 0; i < stringLength; i++)
	{
		TextCharacter *tc;
		std::string id = theText.substr(i, 1);
		glm::vec3 newPosVec;
		TextCharacterType *tct = timng->getTextCharacterTypeByLetter(id);
		if (i != 0)
		{
			float newPosX = textString[i - 1]->getPosition().x + textString[i - 1]->getDimensions().x + spacing;

			newPosVec = glm::vec3(newPosX, textString[i - 1]->getPosition().y, 0);
		}
		else {
			newPosVec = pos;
		}
		tc = new TextCharacter(newPosVec, tct->getTextCharacterDimensions() /*/ 32 * fontSize*/, tct);
		textString.push_back(tc);

		dimens.x += tct->getTextCharacterDimensions().x /*/ 32 * fontSize*/;
		dimens.y = tct->getTextCharacterDimensions().y;

		std::vector<glm::vec2> v = tc->getTextCharacterVertices();
		std::vector<glm::vec2> u = tc->getTextCharacterUVs();

		vertices.insert(std::end(vertices), std::begin(v), std::end(v));
		UVs.insert(std::end(UVs), std::begin(u), std::end(u));

		//vertices.insert(vertices.end(), v.begin(), v.end());
		//UVs.insert(UVs.end(), u.begin(), u.end());


		//offsetPos = glm::vec3(dimens.x / 2, dimens.y / 2, 0);

	}

	model = new Model(vertices, UVs);
	entModels.push_back(model);
}

void Text::update(float dt)
{

}

/*
void Text::render(SDL_Renderer* renderer)
{
	for (int i = 0; i < textString.size(); i++)
	{
		textString[i]->render(renderer);
	}
}
*/

void Text::changeCharacter(int index, std::string textChar)
{
	textString[index]->setTextCharacterType(timng->getTextCharacterTypeByLetter(textChar));
	theText.replace(index, 1, textChar);

	int uvsPerCharacter = 6;

	std::vector<glm::vec2> cUVs = textString[index]->getTextCharacterUVs();
	model->changeUVBUffer(index * uvsPerCharacter, cUVs);
	/*for (int i = 0; i < uvsPerCharacter; i++)
	{
		std::vector<glm::vec2> cUVs = textString[i]->getTextCharacterUVs();
		

		UVs.at(uvsPerCharacter*index + i) = cUVs[2];
	}*/
}

std::string Text::getText()
{
	return theText;
}

void Text::setAlign(Align a)
{
	if (alignment != a)
	{
		alignment = a;

		if (alignment == leftAlign)
		{
			pos = origPos;
			for (int i = 0; i < textString.size(); i++)
			{
				glm::vec3 ts = textString[i]->getPosition();
				ts.x += dimens.x / 2;

				textString[i]->setPosition(ts);
			}

		}
		else if (alignment == centreAlign) {
			pos.x = origPos.x - dimens.x / 2;
			for (int i = 0; i < textString.size(); i++)
			{
				glm::vec3 ts = textString[i]->getPosition();
				ts.x -= dimens.x / 2;

				textString[i]->setPosition(ts);
			}
		}
	}
}

void Text::changeTextPosition(glm::vec3 changeVec)
{
	for (int i = 0; i < textString.size(); i++)
	{
		glm::vec3 tPos = textString[i]->getPosition();
		tPos += changeVec;
		textString[i]->setPosition(tPos);
	}
}

void Text::changeTextEnd(std::string s)
{
	int stringLength = s.length();

	int c = 0;
	for (int i = s.length()-1; i > -1; i--)
	{
		std::string newS = s.substr(i, 1);
		std::string ogS = theText.substr(theText.length() - 1 - c, 1);

		if (newS != ogS)
		{
			//theText.replace(i, 1, newS);


			changeCharacter(theText.length() - 1 - c, newS);
		}
		c += 1;
	}
}

void Text::changeTextStart(std::string s)
{
	int newStringLength = s.length();

	if (newStringLength > textString.size())
	{
		int newCharsToAdd = newStringLength - textString.size();
		for (int i = newCharsToAdd; i > 0; i--)
		{
			std::string id = theText.substr(i, 1);
			glm::vec3 newPosVec;
			TextCharacterType *tct = timng->getTextCharacterTypeByLetter(id);
			TextCharacter *tc;
			

			float newPosX = textString[i + 1]->getPosition().x - tct->getTextCharacterDimensions().x - spacing;
			newPosVec = glm::vec3(newPosX, textString[i + 1]->getPosition().y, 0);
			
			
			tc = new TextCharacter(newPosVec, tct->getTextCharacterDimensions() /*/ 32 * fontSize*/, tct);
			//textString.push_back(tc);
			textString.insert(textString.begin(), tc);
			theText.insert(0, id);

			dimens += tct->getTextCharacterDimensions() /*/ 32 * fontSize*/;
		}
	}
	else {
		for (int i = 0; i < s.length(); i++)
		{
			std::string newS = s.substr(i, 1);
			std::string ogS = theText.substr(i, 1);

			if (newS != ogS)
			{
				theText.replace(i, 1, newS);


				changeCharacter(i, newS);
			}
		}
	}
}







std::vector<glm::vec2> Text::getTextVertices()
{
	return vertices;
}

std::vector<glm::vec2> Text::getTextUVs()
{
	return UVs;
}

Texture* Text::getFontTexture()
{
	return timng->getFontByName(fontName);
}

Texture* Text::getTexture(int index)
{
	return timng->getFontByName(fontName);
}

