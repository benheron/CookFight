#include "Platform.h"

Platform::Platform(std::string windowName, glm::vec2 sizeWindow) : windowName(windowName), sizeWindow(sizeWindow)
{
	init();
}

Platform::~Platform()
{

}




bool Platform::init()
{
	renderSize = glm::vec2(768.f, 432.f);

	//renderSize = glm::vec2(960.f, 540.f);


	//renderSize = glm::vec2(1920.f, 1080.f);



	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialise! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		//create the window
		window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, sizeWindow.x, sizeWindow.y, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		//check if window created
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			context = SDL_GL_CreateContext(window);

			//check context
			if (context == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{

				glewExperimental = GL_TRUE;

				GLenum err = glewInit();

				if (err != GLEW_OK)
				{
					printf("Unable to initialize GLEW!%s\n", glewGetErrorString(err));
				}

				//use vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				glDisable(GL_DEPTH_TEST);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


				if (!mixerInit())
				{
					printf("Unable to initialise mixer. SDL Error: %s\n", SDL_GetError());
				}

				setIcon();
				//controller mappings
				//SDL_GameControllerAddMappingsFromFile("res/controller/gamecontrollerdb_204.txt");

				
			}
		}
	}
	return success;
	
}

glm::vec2 Platform::getWindowSize()
{
	return sizeWindow;
}

glm::vec2 Platform::getRenderSize()
{
	return renderSize;
}

SDL_Window* Platform::getWindow()
{
	return window;
}

bool Platform::mixerInit()
{

	int inF  = MIX_INIT_MP3 | MIX_INIT_OGG;

	int flags = Mix_Init(inF);

	//Check if all formats were loaded
	if ((flags&inF) != inF)
	{
		printf("SDL_mixer failed to initialise itself or some requested formats: %s \n", Mix_GetError());
		return false;
	}

	//Open audio with some standard audio formats/freqs. Also set channels to 2 for stereo sound.
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer open audio failed: %s \n", Mix_GetError());
		return false;
	}

	return true;
}

void Platform::setIcon()
{

	std::string filePath = "res/img/icon.png";

	SDL_Surface *surface = IMG_Load(filePath.c_str());

	SDL_SetWindowIcon(window, surface);


	SDL_FreeSurface(surface);



}