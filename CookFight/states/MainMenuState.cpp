#include "MainMenuState.h"


MainMenuState::MainMenuState(StateManager* manager, Platform *platform, ResourceManager* rm)
	: State(manager, platform), rm(rm)
{
	km = rm->getKeyboardManager();
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
	camera->update(dt);
	std::string actionString = "";
	bool buttonPressed = false;
	int newMenuState = -1;
	
	
	bool startGame = false;

	timeSwitchingMode += dt;

	switch (menuState)
	{
	case 0:
		buttonSet = 0;
		break;
	case 1:
		buttonSet = 1;
		break;
	default:
		buttonSet = -1;
		break;
	}

	

	for (int gamePadIndex = 0; gamePadIndex < rm->getNumGamePads(); gamePadIndex++)
	{
		gp = rm->getGamepad(gamePadIndex);
		
	
		switch(menuState)
		{
		case 0:
			if (gp->buttonPress("dDown"))
			{
				indexHighlighted[menuState] += 1;
				rm->getAudioManager()->getSFXByName("OptionSelect")->playAudio(0);
			}
			if (gp->buttonPress("dUp"))
			{
				indexHighlighted[menuState] -= 1;
				rm->getAudioManager()->getSFXByName("OptionSelect")->playAudio(0);
			}
			break;
		case 1:
			if (gp->buttonPress("dLeft"))
			{
				indexHighlighted[menuState] += 1;
				rm->getAudioManager()->getSFXByName("OptionSelect")->playAudio(0);
			}
			if (gp->buttonPress("dRight"))
			{
				indexHighlighted[menuState] -= 1;
				rm->getAudioManager()->getSFXByName("OptionSelect")->playAudio(0);
			}
			break;
		} 
		
		if (buttonSet != -1)
		{
			if (indexHighlighted[buttonSet] < 0)
			{
				indexHighlighted[buttonSet] = buttons[buttonSet].size() - 1;
			}

			if (indexHighlighted[buttonSet] >  buttons[buttonSet].size() - 1)
			{
				indexHighlighted[buttonSet] = 0;
			}
		}




		if (gp->buttonPress("a") || rm->getKeyboardManager()->keyPressed("enter"))
		{
			if (buttonSet != -1)
			{
				actionString = buttons[buttonSet][indexHighlighted[menuState]]->getAction();
				buttonPressed = true;
			}
			if (menuState == 2)
			{
				bool bothConfirm = true;

				for (int j = 0; j < playerConfirm.size(); j++)
				{
					if (!playerConfirm[j])
					{
						bothConfirm = false;
					}
				}

				if (bothConfirm)
				{
					startGame = true;
				}

				playerConfirm[gamePadIndex] = true;
				playersFaces[gamePadIndex]->setAlpha(1.0f);	
				abuttons[gamePadIndex]->setAlpha(0.f);
			}
		}

		if (gp->buttonPress("b") || rm->getKeyboardManager()->keyPressed("esc"))
		{
			buttonPressed = true;
			if (menuState > 0)
			{
				if (playerConfirm[gamePadIndex])
				{
					playerConfirm[gamePadIndex] = false;
					playersFaces[gamePadIndex]->setAlpha(0.6f);
					abuttons[gamePadIndex]->setAlpha(1.f);
				}
				else {
					switch (menuState)
					{
					case 2:
						newMenuState = menuState - 1;
						for (int j = 0; j < playerConfirm.size(); j++)
						{
							playerConfirm[j] = false;
							playersFaces[j]->setAlpha(0.6f);
							pressToPlay->setShouldRender(false);
							abuttons[j]->setAlpha(1.f);
						}
						break;
					case 3:
						newMenuState = 0;
						break;
					case 4:
						newMenuState = 0;
						break;
					default:
						newMenuState = menuState - 1;
						break;
					}
					
					

				}
				
			}
		}

		
	}

	//keyboard
	if (km->keyPressed("down"))
	{
		indexHighlighted[menuState] += 1;
	}
	if (km->keyPressed("up"))
	{
		indexHighlighted[menuState] -= 1;
	}

	if (buttonSet != -1)
	{
		if (indexHighlighted[buttonSet] < 0)
		{
			indexHighlighted[buttonSet] = buttons[buttonSet].size() - 1;
		}

		if (indexHighlighted[buttonSet] > buttons[buttonSet].size() - 1)
		{
			indexHighlighted[buttonSet] = 0;
		}
	}

	

	if (buttonSet != -1)
	{
		for (int i = 0; i < buttons[buttonSet].size(); i++)
		{
			buttons[buttonSet][i]->setButtonState(buttonIdle);

		}
		buttons[buttonSet][indexHighlighted[menuState]]->setButtonState(buttonHighlight);
	}

	bool renderPressText = true;
	for (int i = 0; i < playerConfirm.size(); i++)
	{
		if (!playerConfirm[i])
		{
			renderPressText = false;
			break;
		}
	}
	pressToPlay->setShouldRender(renderPressText);


	if (timeSwitchingMode > 0.1f)
	{
		if (buttonPressed)
		{
			printf("%s \n", actionString.c_str());
			if (actionString == "play")
			{
				//startGame = true;
				newMenuState = 1;

			}


			if (actionString == "quitdesk")
			{
				quitToDesk = true;
			}


			if (actionString == "table")
			{
				//startGame = true;
				modePlay = 0;
				newMenuState = 2;
			}

			if (actionString == "points")
			{
			//	startGame = true;
				modePlay = 1;
				newMenuState = 2;
			}

			if (actionString == "credits")
			{
				newMenuState = 3;
			}

			if (actionString == "howto")
			{
				newMenuState = 4;
			}



			if (newMenuState != -1 && newMenuState != menuState)
			{
				/*
				for (int i = 0; i < buttons.size(); i++)
				{
					for (int j = 0; j < buttons.size(); j++)
					{
						bool renderChange = true;
						/ *if (i == buttonSet)
						{
						renderChange = false;
						}
						else {
						renderChange = true;
						}* /
						switch (i)
						{
						case 0:

							break;
						case 1:

							break;
						}
						if (renderChange)
						{
							//bool r = buttons[i][j]->getShouldRender();
							//buttons[i][j]->setShouldRender(!r);
						}

					}
				}*/
				menuState = newMenuState;
				timeSwitchingMode = 0.f;
				rm->getAudioManager()->getSFXByName("PageFlip")->playAudio(0);
			}
	}
	
		

		switch (menuState)
		{
		case 0:
			camera->moveTo(glm::vec3(0, 0, 0), 2000.f);
			break;
		case 1:
			camera->moveTo(glm::vec3(platform->getRenderSize().x, 0.f, 0.f), 2000.f);
			break;
		case 2:
			camera->moveTo(glm::vec3(platform->getRenderSize().x*2.f, 0.f, 0.f), 2000.f);
			break;
		case 3:
			camera->moveTo(glm::vec3(0.f, -platform->getRenderSize().y, 0.f), 2000.f);
			break;
		case 4:
			camera->moveTo(glm::vec3(0.f, platform->getRenderSize().y, 0.f), 2000.f);
			break;
		default:
			break;
		}

		


	}
	
	if (startGame)
	{
		if (modePlay != -1)
		{
			printf("Playing mode: %i \n", modePlay);
			rm->getAudioManager()->getMusicByName("TitleScreen")->stopAudio();
			GameState *gs = new GameState(stateManager, platform, rm, modePlay);
			stateManager->changeState(gs);

		}
	
	}
}

void MainMenuState::load()
{
	TextureManager* tmng = rm->getTextureManager();


	camera->setDimensions(platform->getRenderSize());
	camera->setPosition(glm::vec3(0));

	std::vector<Button*> mainButtons;
	std::vector<Button*> modeSelectionButtons;
	buttonSet = 0;
	menuState = 0;
	modePlay = -1;
	changeMode = false;

	Texture *psBackground = tmng->getTextureByName("PauseBackground");
	Entity* bgEntity = new Entity(psBackground, glm::vec3(-5000, -5000, 0), glm::vec3(10000.f, 10000.f, 0));


	entities.push_back(bgEntity);
	timeSwitchingMode = 0.f;

	rm->getAudioManager()->getMusicByName("TitleScreen")->playAudio(-1);


	Texture *playTexture = tmng->getTextureByName("MainPlay");
	Texture *creditsTexture = tmng->getTextureByName("MainCredits");
	Texture *howToTexture = tmng->getTextureByName("MainHowTo");
	Texture *quitTexture = tmng->getTextureByName("MainQuit");

	


	//add main logo
	Texture *logoTexture = tmng->getTextureByName("MainLogo");

	Entity *mainLogo = new Entity(logoTexture);
	glm::vec3 logoPos = glm::vec3(platform->getRenderSize().x / 2.f, platform->getRenderSize().y / 25.f + +((mainLogo->getDimensions().y * 0.2)/ 2), 0);

	mainLogo->setCentre(logoPos);
	mainLogo->setScale(glm::vec3(0.2));

	
	entities.push_back(mainLogo);

	////////
	//CHOOSE MODE
	////////
	//add choose mode title
	Texture *chooseModeTexture = tmng->getTextureByName("ChooseModeTitle");

	Entity *chooseModeTitle = new Entity(chooseModeTexture);
	glm::vec3 logoPos2 = glm::vec3((platform->getRenderSize().x / 2.f) + platform->getRenderSize().x, platform->getRenderSize().y / 25.f  +((chooseModeTitle->getDimensions().y * 0.2) / 2), 0);

	chooseModeTitle->setCentre(logoPos2);
	chooseModeTitle->setScale(glm::vec3(0.2));
	

	entities.push_back(chooseModeTitle);

	////////
	//CHOOSE PLAYER
	////////
	//add choose player title
	Texture *choosePlayerTexture = tmng->getTextureByName("ChoosePlayerTitle");

	Entity *choosePlayerTitle = new Entity(choosePlayerTexture);
	glm::vec3 logoPos3 = glm::vec3((platform->getRenderSize().x / 2.f) + (platform->getRenderSize().x*2.f), platform->getRenderSize().y / 25.f  +((choosePlayerTitle->getDimensions().y * 0.2) / 2), 0);

	choosePlayerTitle->setCentre(logoPos3);
	choosePlayerTitle->setScale(glm::vec3(0.2));


	entities.push_back(choosePlayerTitle);

	////////
	//CREDITS TITLE
	////////
	Texture *creditsTitleTexture = tmng->getTextureByName("CreditsTitle");

	Entity *creditsTitle = new Entity(creditsTitleTexture);
	glm::vec3 logoPos4 = glm::vec3((platform->getRenderSize().x / 2.f), -platform->getRenderSize().y + platform->getRenderSize().y / 25.f + +((creditsTitle->getDimensions().y * 0.2) / 2), 0);

	creditsTitle->setCentre(logoPos4);
	creditsTitle->setScale(glm::vec3(0.2));


	entities.push_back(creditsTitle);

	////////
	//CREDITS PAGE
	////////
	Texture *creditsPageTexture = tmng->getTextureByName("CreditsPage");

	Entity *creditsPage = new Entity(creditsPageTexture);
	glm::vec3 credPagePos = glm::vec3((platform->getRenderSize().x / 2.f), -platform->getRenderSize().y + 240.f, 0.f);

	creditsPage->setCentre(credPagePos);
	
	entities.push_back(creditsPage);





	////////
	//HOW TO PLAY TITLE
	////////
	Texture *howPlayTexture = tmng->getTextureByName("HowToPlayTitle");

	Entity *howPlayTitle = new Entity(howPlayTexture);
	glm::vec3 logoPos5 = glm::vec3((platform->getRenderSize().x / 2.f), platform->getRenderSize().y + platform->getRenderSize().y / 25.f +((howPlayTitle->getDimensions().y * 0.2) / 2), 0);

	howPlayTitle->setCentre(logoPos5);
	howPlayTitle->setScale(glm::vec3(0.2));


	entities.push_back(howPlayTitle);



	////////
	//HOW TO PLAY PAGE
	////////
	Texture *howPlayPageTexture = tmng->getTextureByName("Instructions");

	Entity *howPlayPage = new Entity(howPlayPageTexture);
	glm::vec3 hpPagePos = glm::vec3((platform->getRenderSize().x / 2.f), platform->getRenderSize().y + 240.f, 0.f);

	howPlayPage->setCentre(hpPagePos);

	entities.push_back(howPlayPage);



	

	float leftX = platform->getRenderSize().x / 14.f;

	Button *playBtn = new Button("play", playTexture, glm::vec3(0), glm::vec3(160, 62, 0) *0.66f, glm::vec3(160, 62, 0));
	playBtn->setPosition(glm::vec3(leftX, 220, 0));
	mainButtons.push_back(playBtn);

	
	Button *creditsBtn = new Button("credits", creditsTexture, glm::vec3(0), glm::vec3(264, 62, 0) * 0.66f, glm::vec3(264, 62, 0));
	creditsBtn->setPosition(glm::vec3(leftX, 270 , 0));
	mainButtons.push_back(creditsBtn);

	Button *howToBtn = new Button("howto", howToTexture, glm::vec3(0), glm::vec3(440, 62, 0) * 0.66f, glm::vec3(440, 62, 0));
	howToBtn->setPosition(glm::vec3(leftX, 320, 0));
	mainButtons.push_back(howToBtn);

	Button *quitDeskBtn = new Button("quitdesk", quitTexture, glm::vec3(0), glm::vec3(160, 62, 0) * 0.66f, glm::vec3(160, 62, 0));
	mainButtons.push_back(quitDeskBtn);

	quitDeskBtn->setPosition(glm::vec3(leftX, 370, 0));


	

	/*for (int i = 0; i < mainButtons.size(); i++)
	{
		mainButtons[i]->setScale(glm::vec3(0.66f));
	}
*/

	buttons.push_back(mainButtons);



	Texture *tabTexture = tmng->getTextureByName("Delivery");

	Texture *ponTexture = tmng->getTextureByName("HighScore");

	

	float centX = platform->getRenderSize().x / 2.f;
	float centY = platform->getRenderSize().y / 2.f;

	float cvb = chooseModeTitle->getCentrePosition().y;

	glm::vec3 firstModePos = glm::vec3(platform->getRenderSize().x + centX / 2.f , centY + 25.f, 0.f);
	glm::vec3 secModePos = glm::vec3(platform->getRenderSize().x+ (centX / 2.f)*3.f, centY + 25.f, 0.f);

	Button *tableBtn = new Button("table", tabTexture, glm::vec3(0), glm::vec3(280, 314, 0));



	tableBtn->setCentre(firstModePos);
	//tableBtn->setShouldRender(false);
	modeSelectionButtons.push_back(tableBtn);

	Button *pointsBtn = new Button("points", ponTexture, glm::vec3(0), glm::vec3(280, 314, 0));
	
	//pointsBtn->setShouldRender(false);
	modeSelectionButtons.push_back(pointsBtn);

	pointsBtn->setCentre(secModePos);

	buttons.push_back(modeSelectionButtons);









	for (int i = 0; i < buttons.size(); i++)
	{
		indexHighlighted.push_back(0);
		for (int j = 0; j < buttons[i].size(); j++)
		{
			entities.push_back(buttons[i][j]);
		}
	}


	

	quitToDesk = false;

	for (int i = 0; i < 2; i++)
	{
		playerConfirm.push_back(false);
	}

	Texture* portTraitTexture = tmng->getTextureByName("Portrait");
	Entity* p1Port = new Entity(portTraitTexture);
	Entity* p2Port = new Entity(portTraitTexture);

	std::vector<Entity*> portraits;
	portraits.push_back(p1Port);
	portraits.push_back(p2Port);


	Texture* controllerA = tmng->getTextureByName("XboxA");
	Entity* ca1 = new Entity(controllerA);

	Entity* ca2 = new Entity(controllerA);
	

	abuttons.push_back(ca1);
	abuttons.push_back(ca2);
	


	Texture* chefCopDown = tmng->getTextureByName("ChefCopDown");
	Entity* f1 = new Entity(chefCopDown);
	f1->setBlendColour(glm::vec4(1.0f, 1.f, 1.f, 0.6f));

	Entity* f2 = new Entity(chefCopDown);
	f2->setBlendColour(glm::vec4(1.0f, 0.f, 0.f, 0.6f));

	playersFaces.push_back(f1);
	playersFaces.push_back(f2);

	for (int i = 0; i < playersFaces.size(); i++)
	{
		float xPos = (centX / 2.f) * ((2 * i) + 1) +2 * platform->getRenderSize().x;
		playersFaces[i]->setCentre(glm::vec3(xPos, centY, 0));
		portraits[i]->setCentre(glm::vec3(xPos, centY, 0));
		abuttons[i]->setCentre(glm::vec3(xPos, centY + 100.f, 0));

		entities.push_back(portraits[i]);
		entities.push_back(abuttons[i]);
		entities.push_back(playersFaces[i]);
	}

	pressToPlay = new Text(rm->getTextImageManager(), "Press A To Play!");
	float pressTextX = centX + 2 * platform->getRenderSize().x;
	float pressTextY = platform->getRenderSize().y - platform->getRenderSize().y / 15.f;

	pressToPlay->setCentre(glm::vec3(pressTextX, pressTextY, 0));
	pressToPlay->setShouldRender(false);

	entities.push_back(pressToPlay);
}

void MainMenuState::unload()
{
	
}