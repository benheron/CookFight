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

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
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

