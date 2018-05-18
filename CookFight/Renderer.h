#pragma once
#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "ShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ResourceManager.h"
#include "Platform.h"
#include "states/StateManager.h"


class Renderer
{
public:
	Renderer(Platform* platform, ResourceManager * rm);
	~Renderer();

	void render(std::vector<State*> states);

	void renderScreenSpace(std::vector<State*> states);

	void renderFrameRate(Text* frameRateText);


protected:

	void addToScreen(std::vector<Entity*> entities, glm::mat4 projMat, glm::mat4 viewMat);

	Platform* platform;

	ResourceManager* rm;

	GLuint VertexArrayID;


	ShaderProgram shaderProg;

	GLuint blendColourID;
	GLuint textureID;
	GLuint mvpID;
	GLuint offsetUVID;

//	GLuint lastTextID = 9999;

	//debug
	ShaderProgram txtShader;
	GLuint Text2DUniformID;

	int renderCount = 0;
};