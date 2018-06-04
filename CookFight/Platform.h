#pragma once
#include <glm/glm.hpp>
#include <string>
#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <SDL_image.h>

class Platform
{
public:
	Platform(std::string windowName, glm::vec2 sizeWindow);
	~Platform();

	glm::vec2 getWindowSize();

	glm::vec2 getRenderSize();

	SDL_Window* getWindow();

	bool mixerInit();

	void setIcon();

protected:
	bool init();
	

	std::string windowName;
	glm::vec2 sizeWindow;

	glm::vec2 renderSize;

	SDL_Window* window = NULL;
	SDL_GLContext context;
};