#include "../ResourceManager.h"
#include "PauseState.h"


PauseState::PauseState(StateManager* manager, Platform *platform, ResourceManager* rm)
	: State(manager, platform), rm(rm)
{
	stateName = "PauseState";
}

PauseState::~PauseState()
{

}

bool PauseState::eventHandler()
{

	if (quitToDesk)
	{
		rm->getAudioManager()->getMusicByName("Ingame")->stopAudio();
		quitToDesk = false;
		return true;
	}

	return false;
}

void PauseState::update(float dt)
{
	std::string actionString = "";
	bool buttonPressed = false;
	bool quitToMenu = false;
	for (int gamePadIndex = 0; gamePadIndex < rm->getNumGamePads(); gamePadIndex++)
	{
		gp = rm->getGamepad(gamePadIndex);
		km = rm->getKeyboardManager();

		if (gp->buttonPress("start") || gp->buttonPress("b") || rm->getKeyboardManager()->keyPressed("esc"))
		{
			removeThisState = true;
			actionString = "resume";
		}

		if (gp->buttonPress("dDown"))
		{
			rm->getAudioManager()->getSFXByName("OptionSelect")->playAudio(0);
			indexHighlighted += 1;
		}
		if (gp->buttonPress("dUp"))
		{
			rm->getAudioManager()->getSFXByName("OptionSelect")->playAudio(0);
			indexHighlighted -= 1;
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
		if (actionString == "resume")
		{
			removeThisState = true;
		}

		if (actionString == "retry")
		{
			removeThisState = true;
		}

		if (actionString == "quitmenu")
		{
			quitToMenu = true;
		}

		if (actionString == "quitdesk")
		{
			quitToDesk = true;
		}
	}
	pauseAction = actionString;

	if (removeThisState)
	{
		removeThisState = false;
		stateManager->popLastStateWithoutDelete();
	}

	if (quitToMenu)
	{
		rm->getAudioManager()->getMusicByName("Ingame")->stopAudio();
		stateManager->popLastStateWithoutDelete();
		stateManager->changeState(new MainMenuState(stateManager, platform, rm));
	}
	
}

void PauseState::load()
{
	Texture *psBackground = new Texture("res/img/pausebackground.png");
	Entity* bgEntity = new Entity(psBackground, glm::vec3(0), glm::vec3(platform->getRenderSize(), 0));


	hudElements.push_back(bgEntity);

	removeThisState = false;


	Texture *resumeTexture = new Texture("res/img/buttons/resume.png");
	Texture *retryTexture = new Texture("res/img/buttons/retry.png");
	Texture *quitMenuTexture = new Texture("res/img/buttons/quittomenu.png");
	Texture *quitDeskTexture = new Texture("res/img/buttons/quittodesktop.png");

	
	float centreRenderX = platform->getRenderSize().x / 2.f;

	Button *resumeBtn = new Button("resume", resumeTexture, glm::vec3(50, 50, 0), glm::vec3(320, 72, 0));
	resumeBtn->setCentre(glm::vec3(centreRenderX, 50, 0));
	buttons.push_back(resumeBtn);

	Button *retryBtn = new Button("retry", retryTexture, glm::vec3(50, 150, 0), glm::vec3(320, 72, 0));
	buttons.push_back(retryBtn);

	retryBtn->setCentre(glm::vec3(centreRenderX, 150, 0));

	Button *quitMenuBtn = new Button("quitmenu", quitMenuTexture, glm::vec3(50, 150, 0), glm::vec3(320, 72, 0));
	buttons.push_back(quitMenuBtn);

	quitMenuBtn->setCentre(glm::vec3(centreRenderX, 250, 0));

	Button *quitDeskBtn = new Button("quitdesk", quitDeskTexture, glm::vec3(50, 150, 0), glm::vec3(320, 72, 0));
	buttons.push_back(quitDeskBtn);

	quitDeskBtn->setCentre(glm::vec3(centreRenderX, 350, 0));


	for (int i = 0; i < buttons.size(); i++)
	{
		hudElements.push_back(buttons[i]);
	}


	indexHighlighted = 0;

	quitToDesk = false;
}

void PauseState::unload()
{

}