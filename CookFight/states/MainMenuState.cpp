#include "MainMenuState.h"


MainMenuState::MainMenuState(StateManager* manager, Platform *platform, ResourceManager* rm)
	: State(manager, platform), rm(rm)
{

}

MainMenuState::~MainMenuState()
{

}

bool MainMenuState::eventHandler()
{
	if (quitToDesk)
	{
		rm->getAudioManager()->getMusicByName("TitleScreen")->stopAudio();
		quitToDesk = false;
		return true;
	}

	return false;
}

void MainMenuState::update(float dt)
{
	std::string actionString = "";
	bool buttonPressed = false;
	bool startGame = false;

	for (int gamePadIndex = 0; gamePadIndex < rm->getNumGamePads(); gamePadIndex++)
	{
		gp = rm->getGamepad(gamePadIndex);
		km = rm->getKeyboardManager();
	

		if (gp->buttonPress("dDown"))
		{
			indexHighlighted += 1;
			rm->getAudioManager()->getSFXByName("OptionSelect")->playAudio(0);
		}
		if (gp->buttonPress("dUp"))
		{
			indexHighlighted -= 1;
			rm->getAudioManager()->getSFXByName("OptionSelect")->playAudio(0);
		}

		if (gp->buttonPress("a") || rm->getKeyboardManager()->keyPressed("enter"))
		{
			actionString = buttons[indexHighlighted]->getAction();
			buttonPressed = true;
		}
	}

	//keyboard
	if (km->keyPressed("down"))
	{
		indexHighlighted += 1;
	}
	if (km->keyPressed("up"))
	{
		indexHighlighted -= 1;
	}



	if (indexHighlighted < 0)
	{
		indexHighlighted = buttons.size() - 1;
	}

	if (indexHighlighted > buttons.size() - 1)
	{
		indexHighlighted = 0;
	}

	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->setButtonState(buttonIdle);
	}
	buttons[indexHighlighted]->setButtonState(buttonHighlight);



	if (buttonPressed)
	{
		if (actionString == "play")
		{
			startGame = true;
		}


		if (actionString == "quitdesk")
		{
			quitToDesk = true;
		}
	}
	
	if (startGame)
	{
		rm->getAudioManager()->getMusicByName("TitleScreen")->stopAudio();
		GameState *gs = new GameState(stateManager, platform, rm);
		stateManager->changeState(gs);
		
	}
}

void MainMenuState::load()
{
	Texture *psBackground = new Texture("res/img/pausebackground.png");
	Entity* bgEntity = new Entity(psBackground, glm::vec3(0), glm::vec3(platform->getRenderSize(), 0));


	hudElements.push_back(bgEntity);


	rm->getAudioManager()->getMusicByName("TitleScreen")->playAudio(0);


	Texture *playTexture = new Texture("res/img/buttons/mainPlay.png");
	Texture *retryTexture = new Texture("res/img/buttons/retry.png");
	Texture *quitTexture = new Texture("res/img/buttons/mainQuit.png");


	float leftX = platform->getRenderSize().x / 8.f;

	Button *resumeBtn = new Button("play", playTexture, glm::vec3(50, 50, 0), glm::vec3(160, 62, 0));
	resumeBtn->setPosition(glm::vec3(leftX, 150, 0));
	buttons.push_back(resumeBtn);

	Button *quitDeskBtn = new Button("quit", quitTexture, glm::vec3(50, 150, 0), glm::vec3(160, 62, 0));
	buttons.push_back(quitDeskBtn);

	quitDeskBtn->setPosition(glm::vec3(leftX, 220, 0));


	for (int i = 0; i < buttons.size(); i++)
	{
		hudElements.push_back(buttons[i]);
	}


	indexHighlighted = 0;

	quitToDesk = false;

}

void MainMenuState::unload()
{

}