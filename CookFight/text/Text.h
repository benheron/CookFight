#pragma once
#include <string>
#include "../entities/Entity.h"
#include "TextImageManager.h"
#include "TextCharacter.h"
#include "../Model.h"

enum Align {
	leftAlign,
	centreAlign
};

class Text : public Entity {
public:


	Text(glm::vec3 pos, std::string fontName, int fontSize, std::string theText, TextImageManager *timng);
	Text(TextImageManager *timng, std::string theText, int fontSize = 32, std::string fontName = "arial",  glm::vec3 pos = glm::vec3(0));
	~Text();

	void textInit();

	char operator[](const std::size_t position)
	{ return theText[position];	}

	void update(float dt);

	//void render(SDL_Renderer* renderer);

	void changeCharacter(int index, std::string textChar);

	Texture* getFontTexture();

	virtual std::vector<Model*> getModels() { return entModels; }

	virtual Texture* getTexture(int index);

	std::string getText();

	void setAlign(Align a);

	void changeTextPosition(glm::vec3 changeVec);

	std::vector<glm::vec2> getTextVertices();
	std::vector<glm::vec2> getTextUVs();

	void changeTextEnd(std::string s);
	void changeTextStart(std::string s);


protected:
	void writeText();

	///The test itself in string value
	std::string theText;
	std::string fontName;
	int fontSize;
	TextImageManager *timng;

	int spacing;

	///The Text using text characters
	std::vector<TextCharacter*> textString;



	Align alignment;
	glm::vec3 origPos;

	glm::vec3 diffX;


	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> UVs;

	Model* m;
};