#include "Background.h"


Background::Background(std::vector<Texture*> bgTextures, glm::vec3 dimens) : Entity(glm::vec3(0), dimens, glm::vec2(0), glm::vec3(0), true)
{
	bgInit();
	buildBackgrounds(bgTextures);
}

Background::~Background()
{

}

void Background::bgInit()
{
	
}

void Background::update(float dt, glm::vec3 cameraPos)
{

	//printf("Camera X: %f \n", cameraPos.x);

	for (int i = 0; i < children.size(); i++)
	{

		float scrollSpeed = 1.f;

		//glm::vec3 newCentre;

		switch (i)
		{
		case 0:
			scrollSpeed = 1.f;
			//newCentre = glm::vec3(c->getPosition().x*scrollSpeed, c->getPosition().y*scrollSpeed, 0);
			break;
		case 1:
			scrollSpeed = 0.8f;
			//newCentre = glm::vec3(c->getPosition().x*scrollSpeed, c->getPosition().y*scrollSpeed, 0);
			break;
		case 2:
			scrollSpeed = 0.5f;
			break;
		default:
			scrollSpeed = 0;
			break;
		}
		scrollSpeed = 1.f;
		glm::vec3 newCentre = glm::vec3(cameraPos.x*(1.f / (i+1)), cameraPos.y*(1.f /(i+1)), 0);

	//	printf("Child %i X: %f \n", i + 1, newCentre.x);

		children[i]->setPosition(-newCentre);
		
	}


	Entity::update(dt);
	
}


void Background::buildBackgrounds(std::vector<Texture*> bgTextures)
{
	for (int i = 0; i < bgTextures.size(); i++)
	{
		Entity *bge = new Entity(bgTextures[i], glm::vec3(0), dimens, glm::vec2(1));

		Model *mo = bge->getModels()[0];
			
			
			//= new Model(bge->getEntityVertices(), bge->getEntityUVs());

		entTextures.push_back(bgTextures[i]);
		entModels.push_back(mo);

		children.push_back(bge);
	}
	updateModelMatrix();


	float f = lerpf(7, 5, 0.5);

}




void Background::addBackgroundImage(Texture* b)
{
	Entity *be = new Entity(b);
	backgrounds.push_back(be);
}


float Background::lerpf(float a, float b, float c)
{
	return a + (b - a)*c;
}

/*
std::vector<Texture*> Background::getTextures()
{
	
}*/