#include "TextImageManager.h"

TextImageManager::TextImageManager(std::string filePath)
{
	loadTextImageData(filePath);
}

TextImageManager::~TextImageManager()
{

}

bool TextImageManager::loadTextImageData(std::string filePath)
{

//	Utility::log(Utility::I, "Loading Text Image Data : " + filePath);

	std::ifstream textImgFile(filePath);

	if (textImgFile.is_open())
	{
		std::string fontName;
		std::string imgFile;
		glm::vec3 imgDimens;
		int fontSize;
		bool bold;
		bool italic;
		int numOfLetters;


		textImgFile >> fontName;
		textImgFile >> imgFile;
		textImgFile >> imgDimens.x;
		textImgFile >> imgDimens.y;
		textImgFile >> fontSize;
		textImgFile >> bold;
		textImgFile >> italic;
		textImgFile >> numOfLetters;

	//	Utility::log(Utility::I, "Loading the font image : " + imgFile);
		Texture *t = new Texture();
		t->loadTexture(imgFile);
		fonts[fontName] = t;
		

		for (int i = 0; i < numOfLetters; i++)
		{
			int asciiID;
			glm::vec3 pos;
			glm::vec3 dimens;

			textImgFile >> asciiID;
			textImgFile >> pos.x;
			textImgFile >> pos.y;
			textImgFile >> dimens.x;
			textImgFile >> dimens.y;


			//change values to be from 0-1 for OpenGL texture
			/*pos.x = pos.x / imgDimens.x;
			pos.y = pos.y / imgDimens.y;
			dimens.x = dimens.x / imgDimens.x;
			dimens.y = dimens.y / imgDimens.y;*/

		

			

			std::stringstream ss;
			char c = asciiID;
			std::string textChar;
			ss << c;
			ss >> textChar;

			if (textChar == "")
			{
				std::string tmp = "a b";
				
				textChar = tmp.substr(1, 1);
			}
			//Utility::log(Utility::I, "Text character is: " + textChar);
			
			//std::string ID = Utility::intToString(asciiID);

			glm::vec3 oglPos = pos / imgDimens;
			glm::vec3 oglDimens = dimens / imgDimens;
			


			TextCharacterType *tct = new TextCharacterType(t, asciiID, textChar, oglPos, dimens, oglDimens);

			TextCharacterTypesAsciiID[asciiID] = tct;
			TextCharacterTypesAsciiLetter[textChar] = tct;
			
		}

		textImgFile.close();


		return true;
	}
	else
	{
		//Error
	
		return false;
	}
}

TextCharacterType* TextImageManager::getTextCharacterTypeByAscii(int ID)
{
	return TextCharacterTypesAsciiID[ID];
}

TextCharacterType* TextImageManager::getTextCharacterTypeByLetter(std::string l)
{
	return TextCharacterTypesAsciiLetter[l];
}

Texture* TextImageManager::getFontByName(std::string n)
{
	return fonts[n];
}