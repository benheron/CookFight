#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Platform.h"
#include "states/StateManager.h"
#include "states/MainMenuState.h"
#include "states/PauseState.h"
#include "Renderer.h"
#include "input/Gamepad.h"


#include <time.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int joyStickNum = 0;
ResourceManager* rm;

//Input handler
void handleKeys(SDL_Event keyType, bool bKeyDown, int x, int y);


//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

bool gTimeStop = false;

KeyboardManager *kbManager;

const int JOYSTICK_DEAD_ZONE = 6000;


std::vector<SDL_GameController*> gameControllers;
std::vector<Gamepad*> gamePads;
std::unordered_map<int, int> indexFromInstance;

std::unordered_map<int, Gamepad*> gamepadsMap;


//std::unordered_map



void handleController(Gamepad* gp)
{
	SDL_GameController* gGameController = gp->getGameControllerReference();
	if (SDL_GameControllerGetButton(gGameController,
		SDL_CONTROLLER_BUTTON_A))
	{
		gp->setButtonDown("a", true);
	}
	else {
		gp->setButtonDown("a", false);
	}

	if (SDL_GameControllerGetButton(gGameController,
		SDL_CONTROLLER_BUTTON_B))
	{
		gp->setButtonDown("b", true);
	}
	else {
		gp->setButtonDown("b", false);
	}

	if (SDL_GameControllerGetButton(gGameController,
		SDL_CONTROLLER_BUTTON_X))
	{
		gp->setButtonDown("x", true);
	}
	else {
		gp->setButtonDown("x", false);
	}

	if (SDL_GameControllerGetButton(gGameController,
		SDL_CONTROLLER_BUTTON_Y))
	{
		gp->setButtonDown("y", true);
	}
	else {
		gp->setButtonDown("y", false);
	}


	if (SDL_GameControllerGetButton(gGameController,
		SDL_CONTROLLER_BUTTON_START))
	{
		gp->setButtonDown("start", true);
	}
	else {
		gp->setButtonDown("start", false);
	}


	if (SDL_GameControllerGetButton(gGameController,
		SDL_CONTROLLER_BUTTON_BACK))
	{
		gp->setButtonDown("select", true);
	}
	else {
		gp->setButtonDown("select", false);
	}
	
	if (SDL_GameControllerGetButton(gGameController,
		SDL_CONTROLLER_BUTTON_LEFTSHOULDER))
	{
		gp->setButtonDown("lb", true);
	}
	else {
		gp->setButtonDown("lb", false);
	}

	if (SDL_GameControllerGetButton(gGameController,
		SDL_CONTROLLER_BUTTON_RIGHTSHOULDER))
	{
		gp->setButtonDown("rb", true);
	}
	else {
		gp->setButtonDown("rb", false);
	}


	if (SDL_GameControllerGetButton(gGameController,
		SDL_CONTROLLER_BUTTON_DPAD_UP))
	{
		gp->setButtonDown("dUp", true);
	}
	else {
		gp->setButtonDown("dUp", false);
	}
	if (SDL_GameControllerGetButton(gGameController,
		SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	{
		gp->setButtonDown("dDown", true);
	}
	else {
		gp->setButtonDown("dDown", false);
	}

	if (SDL_GameControllerGetButton(gGameController,
		SDL_CONTROLLER_BUTTON_DPAD_LEFT))
	{
		gp->setButtonDown("dLeft", true);
	}
	else {
		gp->setButtonDown("dLeft", false);
	}

	if (SDL_GameControllerGetButton(gGameController,
		SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		gp->setButtonDown("dRight", true);
	}
	else {
		gp->setButtonDown("dRight", false);
	}

	if (SDL_GameControllerGetButton(gGameController,
		SDL_CONTROLLER_BUTTON_LEFTSTICK))
	{
		gp->setButtonDown("leftThumb", true);
	}
	else {
		gp->setButtonDown("leftThumb", false);
	}

	if (SDL_GameControllerGetButton(gGameController,
		SDL_CONTROLLER_BUTTON_RIGHTSTICK))
	{
		gp->setButtonDown("rightThumb", true);
	}
	else {
		gp->setButtonDown("rightThumb", false);
	}



	int leftThumbX = SDL_GameControllerGetAxis(gGameController,
		SDL_CONTROLLER_AXIS_LEFTX);

	/*if (leftThumbX < JOYSTICK_DEAD_ZONE && 
		leftThumbX > -JOYSTICK_DEAD_ZONE)
	{
		leftThumbX = 0;
		
	}*/
	
	int leftThumbY = SDL_GameControllerGetAxis(gGameController,
		SDL_CONTROLLER_AXIS_LEFTY);

	/*if (leftThumbY < JOYSTICK_DEAD_ZONE && 
		leftThumbY > -JOYSTICK_DEAD_ZONE)
	{
		leftThumbY = 0;
	}*/

	gp->setThumb(leftThumbX, leftThumbY, 0);

	int rightThumbX = SDL_GameControllerGetAxis(gGameController,
		SDL_CONTROLLER_AXIS_RIGHTX);

	int rightThumbY = SDL_GameControllerGetAxis(gGameController,
		SDL_CONTROLLER_AXIS_RIGHTY);

	gp->setThumb(rightThumbX, rightThumbY, 1);


	int leftTrig = SDL_GameControllerGetAxis(gGameController,
		SDL_CONTROLLER_AXIS_TRIGGERLEFT);

	gp->setTriggerValue("left", leftTrig);

	int rightTrig = SDL_GameControllerGetAxis(gGameController,
		SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

	gp->setTriggerValue("right", rightTrig);

	


}


void handleKeys(SDL_Event events, bool bKeyDown, int x, int y)
{

	switch (events.key.keysym.sym)
	{
	case SDLK_a: kbManager->setKeyDown("a", bKeyDown); break;
	case SDLK_b: kbManager->setKeyDown("b", bKeyDown); break;
	case SDLK_c: kbManager->setKeyDown("c", bKeyDown); break;
	case SDLK_d: kbManager->setKeyDown("d", bKeyDown); break;
	case SDLK_e: kbManager->setKeyDown("e", bKeyDown); break;
	case SDLK_f: kbManager->setKeyDown("f", bKeyDown); break;
	case SDLK_g: kbManager->setKeyDown("g", bKeyDown); break;
	case SDLK_h: kbManager->setKeyDown("h", bKeyDown); break;
	case SDLK_i: kbManager->setKeyDown("i", bKeyDown); break;
	case SDLK_j: kbManager->setKeyDown("j", bKeyDown); break;
	case SDLK_k: kbManager->setKeyDown("k", bKeyDown); break;
	case SDLK_l: kbManager->setKeyDown("l", bKeyDown); break;
	case SDLK_m: kbManager->setKeyDown("m", bKeyDown); break;
	case SDLK_n: kbManager->setKeyDown("n", bKeyDown); break;
	case SDLK_o: kbManager->setKeyDown("o", bKeyDown); break;
	case SDLK_p: kbManager->setKeyDown("p", bKeyDown); break;
	case SDLK_q: kbManager->setKeyDown("q", bKeyDown); break;
	case SDLK_r: kbManager->setKeyDown("r", bKeyDown); break;
	case SDLK_s: kbManager->setKeyDown("s", bKeyDown); break;
	case SDLK_t: kbManager->setKeyDown("t", bKeyDown); break;
	case SDLK_u: kbManager->setKeyDown("u", bKeyDown); break;
	case SDLK_v: kbManager->setKeyDown("v", bKeyDown); break;
	case SDLK_w: kbManager->setKeyDown("w", bKeyDown); break;
	case SDLK_x: kbManager->setKeyDown("x", bKeyDown); break;
	case SDLK_y: kbManager->setKeyDown("y", bKeyDown); break;
	case SDLK_z: kbManager->setKeyDown("z", bKeyDown); break;

	case SDLK_0: kbManager->setKeyDown("0", bKeyDown); break;
	case SDLK_1: kbManager->setKeyDown("1", bKeyDown); break;
	case SDLK_2: kbManager->setKeyDown("2", bKeyDown); break;
	case SDLK_3: kbManager->setKeyDown("3", bKeyDown); break;
	case SDLK_4: kbManager->setKeyDown("4", bKeyDown); break;
	case SDLK_5: kbManager->setKeyDown("5", bKeyDown); break;
	case SDLK_6: kbManager->setKeyDown("6", bKeyDown); break;
	case SDLK_7: kbManager->setKeyDown("7", bKeyDown); break;
	case SDLK_8: kbManager->setKeyDown("8", bKeyDown); break;
	case SDLK_9: kbManager->setKeyDown("9", bKeyDown); break;
	case SDLK_SPACE: kbManager->setKeyDown("space", bKeyDown); break;

	case SDLK_UP: kbManager->setKeyDown("up", bKeyDown); break;
	case SDLK_DOWN: kbManager->setKeyDown("down", bKeyDown); break;
	case SDLK_LEFT: kbManager->setKeyDown("left", bKeyDown); break;
	case SDLK_RIGHT: kbManager->setKeyDown("right", bKeyDown); break;
	case SDLK_ESCAPE: kbManager->setKeyDown("esc", bKeyDown); break;
	case SDLK_RETURN: kbManager->setKeyDown("enter", bKeyDown); break;

	case SDLK_LSHIFT: kbManager->setKeyDown("shift", bKeyDown); break;
	case SDLK_RSHIFT: kbManager->setKeyDown("shift", bKeyDown); break;

	}
}

void addController()
{



	SDL_GameController* gc = NULL;
	gc = SDL_GameControllerOpen(joyStickNum);
	SDL_GameControllerEventState(SDL_ENABLE);
	printf("Added controller %i: \n", joyStickNum);

	//gameControllers.push_back(gc);

	Gamepad* gp = new Gamepad(gc);
	rm->addGamepad(gp);
	
	//gamePads.push_back(gp);



	int iid = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gc));
	indexFromInstance[iid] = joyStickNum;

	rm->addGamepadToMap(gp, iid);

	joyStickNum++;





	

}

void removeController(int dInstance)
{

	int deviceIndex = indexFromInstance[dInstance];

	printf("Removing controller: instance: %i, index: %i \n", dInstance, deviceIndex);




	SDL_GameControllerClose(rm->getGamepad(deviceIndex)->getGameControllerReference());
	rm->removeGamepad(deviceIndex);
	//gameControllers[deviceIndex] = NULL;
	//gameControllers.erase(gameControllers.begin() + deviceIndex);
	


	//gamePads.erase(gamePads.begin() + deviceIndex);
	
	joyStickNum--;

	indexFromInstance.erase(dInstance);
}



void close()
{
	for (int i = 0; i < gameControllers.size(); i++)
	{
		SDL_GameControllerClose(gameControllers[i]);
		gameControllers[i] = NULL;
	}

	
	
	//Destroy window	
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}


int main( int argc, char* args[] )
{

	Platform *platform = new Platform("Battle Chefs", glm::vec2(768.f, 432.f));

//	Platform *platform = new Platform("OpenGL project!", glm::vec2(1920.f, 1080.f));

	
	srand(time(NULL));
	
	kbManager = new KeyboardManager();

	
	

	bool pollControllers = false;

	

	int numJoysticks = SDL_NumJoysticks();

	if (SDL_NumJoysticks() < 1)
	{
		printf("Warning: No joysticks connected!\n");
	}
	else
	{
		for (int i = 0; i < numJoysticks; i++)
		{
			/*SDL_GameController* gc = NULL;
			gc = SDL_GameControllerOpen(i);
			SDL_GameControllerEventState(SDL_ENABLE);
			pollControllers = true;

			gameControllers.push_back(gc);

			Gamepad* gp = new Gamepad();
			gamePads.push_back(gp);*/

			


			/*if (gc == NULL)
			{
				printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
			}
			else {
				printf("Found controller!\n");
			}*/
		}
		
	}



	pollControllers = true;

	rm = new ResourceManager(kbManager, gamePads);

	
	StateManager *stateManager = new StateManager();


	PauseState *ps = new PauseState(stateManager, platform, rm);

	rm->setPauseState(ps);
//	GameState *gs = new GameState(stateManager, platform, rm);
	MainMenuState *mms = new MainMenuState(stateManager, platform, rm);
	//stateManager->addState(gs);

	stateManager->addState(mms);

	

	Renderer* renderer = new Renderer(platform, rm);


	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
		
	int x = 0, y = 0;
	SDL_GetMouseState(&x, &y);

	Text *fr = new Text(glm::vec3(10.f, 550.f, 0), "arial", 32, "000", rm->getTextImageManager());


	unsigned int lastTime = SDL_GetTicks();

	//Enable text input
	//SDL_StartTextInput();


	unsigned int startTime = SDL_GetTicks();

	//float dt = 1.f / 60.f;

	//While application is running
	while( !quit )
	{

		unsigned int current = SDL_GetTicks();
		

		float msbf = current - lastTime;
		

		float dt = (float)(current - lastTime) / 1000.0f;
		lastTime = current;

		
		

		


		if (dt > 0.050)
		{
			dt = 0.050;
		}

		int frames = 1 / dt;

		if (frames > 0)
		{
			std::string str = std::to_string(frames);
			fr->changeTextEnd(str);
			//printf("FPS: %i\n", frames);
		}

		//tests for framerate problem
		//turns out Netflix caused them
		/*if (frames > 0 && frames < 60)
		{
			unsigned int timeNow = SDL_GetTicks();

			unsigned int diffSinceStart = timeNow - startTime;
			startTime = timeNow;
			printf("Ticks since last frame problem: %i \n", diffSinceStart);
		}*/
	
		
		//printf("%i ms/frame\n", int(frames));

		//Handle events on queue
		while( SDL_PollEvent( &e ))
		{
			//User requests quit
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_KEYDOWN:
				handleKeys(e, true, x, y);
				break;
			case SDL_KEYUP:
				handleKeys(e, false, x, y);
				break;
			case SDL_JOYDEVICEADDED:
				printf("Controller added. Reference: %i  \n", e.jdevice.which);
				addController();
				break;
			case SDL_JOYDEVICEREMOVED:
				printf("Controller removed \n");
				 
				removeController(e.jdevice.which);
				break;
				
			}
		}

		kbManager->update();
		
		if (pollControllers)
		{
			for (int i = 0; i < rm->getNumGamePads(); i++)
			{
				handleController(rm->getGamepad(i));
			}

			/*std::unordered_map<int, Gamepad*> gpm = rm->getGamePadMap();
			for (auto i : gpm)
			{
				

				Gamepad* currentGamepad = gpm[i.first];
				handleController(currentGamepad);
				//handleController
			}*/
		
		}
		
		if (!quit)
		{
			quit = stateManager->eventHandler();
		}
		stateManager->update(dt);

		


		renderer->render(stateManager->getStates());
		renderer->renderScreenSpace(stateManager->getStates());

	//	renderer->renderFrameRate(fr);
			
		//Update screen
		SDL_GL_SwapWindow( platform->getWindow() );
	}
		

	delete rm;
	delete platform;
	delete stateManager;

	//Free resources and close SDL
	close();

	return 0;
}

