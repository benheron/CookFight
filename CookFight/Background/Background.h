#pragma once
#include "../entities/Entity.h"
#include "../Camera.h"


class Background : public Entity
{
public:
	Background(std::vector<Texture*> bgTextures, glm::vec3 dimens = glm::vec3(0));
	~Background();

	void bgInit();

	

	void update(float dt, glm::vec3 cameraPos);


	void buildBackgrounds(std::vector<Texture*> bgTextures);


	void addBackgroundImage(Texture* b);


	//virtual std::vector<Texture*> getTextures();
	//Texture


private:
	float lerpf(float a, float b, float c);


	int numBackgrounds;


	std::vector<Entity*> backgrounds;
};