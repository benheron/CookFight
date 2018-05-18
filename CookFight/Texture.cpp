#include "Texture.h"


Texture::Texture()
{
	textureID = 0;
	//loadTexture(filePath);
}

Texture::Texture(std::string filePath)
{
	init();
	loadTexture(filePath);
}

Texture::~Texture()
{

}

void Texture::init()
{
	textureID = 0;
}

void Texture::loadTexture(std::string filePath)
{

	//found http://www.sdltutorials.com/sdl-tip-sdl-surface-to-opengl-texture


	SDL_Surface *surface;
	surface = IMG_Load(filePath.c_str());


	

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	int Mode = GL_RGB;

	if (surface->format->BytesPerPixel == 4) {
		Mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, Mode, surface->w, surface->h, 0, Mode, GL_UNSIGNED_BYTE, surface->pixels);

	origDimens.x = surface->w;
	origDimens.y = surface->h;


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



	SDL_FreeSurface(surface);

}

GLuint Texture::getTextureID()
{
	return textureID;
}

glm::vec2 Texture::getOrigDimens()
{
	return origDimens;
}

glm::vec2 Texture::getPaddedDimens()
{
	return paddedDimens;
}


bool Texture::isPowerTwo(int n)
{
	return (n != 0) && ((n & (n - 1)) == 0);
}