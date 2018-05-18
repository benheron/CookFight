#pragma once
#include <string>
#include <gl/glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <glm/glm.hpp>

class Texture
{
public:
	Texture();
	Texture(std::string filePath);
	~Texture();

	void init();


	GLuint getTextureID();

	void loadTexture(std::string filePath);

	glm::vec2 getOrigDimens();

	glm::vec2 getPaddedDimens();

protected:
	bool isPowerTwo(int n);

	GLuint textureID;

	glm::vec2 origDimens;

	glm::vec2 paddedDimens;
	
};