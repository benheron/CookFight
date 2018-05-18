#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "../Texture.h"
#include "TextCharacterType.h"



class TextImageManager {
public:
	TextImageManager(std::string filePath);
	~TextImageManager();

	TextCharacterType* getTextCharacterTypeByAscii(int ID);
	TextCharacterType* getTextCharacterTypeByLetter(std::string l);

	Texture* getFontByName(std::string n);

protected:
	bool loadTextImageData(std::string filePath);

	std::unordered_map<int, TextCharacterType*> TextCharacterTypesAsciiID;
	std::unordered_map<std::string, TextCharacterType*> TextCharacterTypesAsciiLetter;

	std::unordered_map<std::string, Texture*> fonts;


};