#include "GameState.h"
#include "GameOverState.h"
#include "PauseState.h"

GameState::GameState(StateManager* manager, Platform *platform, ResourceManager* rm, int mode) : State(manager, platform), rm(rm), mode(mode)
{
	km = rm->getKeyboardManager();
	stateName = "GameState";
//	gp = rm->getGamepad();
}

GameState::~GameState()
{
	
}

bool GameState::eventHandler()
{



	return false;
}

void GameState::update(float dt)
{ 
	std::string pauseAction = rm->getPauseState()->getPauseAction();
	if (pauseAction == "retry")
	{
		resetGame();
	}
	else if (pauseAction == "resume")
	{
		for(int i = 0; i < sounds.size(); i++)
		{
			sounds[i]->resumeAudio();
		}
		currentBgMusic->resumeAudio();

	}

	
	


	for (int i = 0; i < foodBoxes.size(); i++)
	{
		foodBoxes[i]->update(dt);
	}

	if (!gameFinished)
	{
		
			
		if (startOfGame)
		{
			if (beginGameTimer == 0.f)
			{
				getReady->setShouldRender(true);
				rm->getAudioManager()->getSFXByName("GetReady")->playAudio(0);
			}
			

			if (beginGameTimer > 1.5f)
			{
				getReady->setShouldRender(false);
				startCook->setShouldRender(true);
				startOfGame = false;
				bgMusic->playAudio(-1);
			}
		}
		else {

			if (beginGameTimer > 2.3f)
			{
				startCook->setShouldRender(false);
			}
			cookDev->update(dt);
			levelTimerText->update(dt);
			for (int gamePadIndex = 0; gamePadIndex < rm->getNumGamePads(); gamePadIndex++)
			{
				int otherPlayerIndex;

				if (gamePadIndex == 0)
				{
					otherPlayerIndex = rm->getNumGamePads() - 1;
				}
				else {
					otherPlayerIndex = 0;
				}




				gp = rm->getGamepad(gamePadIndex);
				Chef* currentPlayer = players[gamePadIndex];
				float xDir = 0;
				float yDir = 0;
				float mag = 0;

				if (km->keyDown("a") || gp->buttonDown("dLeft"))
				{
					xDir -= 1;
					mag = 1;
				}

				if (km->keyDown("d") || gp->buttonDown("dRight"))
				{
					xDir += 1;
					mag = 1;
				}

				if (km->keyDown("w") || gp->buttonDown("dUp"))
				{

					yDir -= 1;
					mag = 1;
				}

				if (km->keyDown("s") || gp->buttonDown("dDown"))
				{
					yDir += 1;
					mag = 1;
				}



				float gpxDir = gp->getLeftStick().x;
				float gpyDir = gp->getLeftStick().y;



				if (gpxDir || gpyDir)
				{
					xDir = gpxDir;
					yDir = gpyDir;


					//printf("Dir val x: %f, Dir val y: %f \n", xDir, yDir);


					//glm::vec2 tdir=  normalize(glm::vec2(xDir, yDir));



					//mag = (abs(xDir) + abs(yDir)) / 32767;

					mag = gp->getMagnitude();

					//printf("Magnitude %f \n", mag);
					/*int fthing = int(xDir) << 14;
					int gthing = int(yDir) << 14;

					printf("Bit val x: %i, Bit val y: %i \n", xDir, yDir);*/
				}





				glm::vec2 dir;
				if (xDir || yDir)
				{
					dir = normalize(glm::vec2(xDir, yDir));
				}
				else {
					dir = glm::vec2(0);
				}


				//dir *= 1.15f;
				if (dir.x > 1)
				{
					dir.x = 1;
				}
				if (dir.x < -1)
				{
					dir.x = -1;
				}

				if (dir.y > 1)
				{
					dir.y = 1;
				}
				if (dir.y < -1)
				{
					dir.y = -1;
				}



				//	printf("Dir val x: %f, Dir val y: %f \n", dir.x, dir.y);



				if (mag > 1)
				{
					mag = 1;
				}
				if (mag < -1)
				{
					mag = -1;
				}

				if (currentPlayer->getHitStunTimer() <= 0.f)
				{
					currentPlayer->moveActor(dir, mag, dt);
				}






				//zoom
			/*	if (km->keyDown("up"))
				{
					camera->setScale(glm::vec3(2.f*dt, 2.f*dt, 0), true);

				}

				if (km->keyDown("down"))
				{
					camera->setScale(glm::vec3(-2.f*dt, -2.f*dt, 0), true);

				}*/



				if (km->keyDown("c"))
				{
					cameraFollow = !cameraFollow;
				}
				int foodBoxSelectionIndex = -1;
				for (int i = 0; i < foodBoxes.size(); i++)
				{
					
					if (Collision::SATIntersection(currentPlayer->getBoundingBox(), foodBoxes[i]->getInteractBoundingBox()))
					{
						foodBoxSelectionIndex = i;
						break;
					}
					
					
				}
				if (foodBoxSelectionIndex != -1)
				{
					foodBoxes[foodBoxSelectionIndex]->setSelected(true);
					foodBoxes[foodBoxSelectionIndex]->setBrightnessModifier(1.25f);
				}
				if (Collision::SATIntersection(currentPlayer->getBoundingBox(), cookDev->getInteractBoundingBox()))
				{
					cookDev->setBrightnessModifier(1.4f);
				}


				//picking up and putting down food
				if (km->keyPressed("j") || km->keyPressed("space") || gp->buttonPress("a") || pressingPickupBuffer[gamePadIndex] > 0.f)
				{


					if (!pressingPickup[gamePadIndex] || pressingPickupBuffer[gamePadIndex] > 0.f)
					{
						if (!pressingPickup[gamePadIndex])
						{
							//give player a buffer window if miss the pickup hitbox by a 7th of a second
							pressingPickupBuffer[gamePadIndex] = 0.116f;

						}

						pressingPickup[gamePadIndex] = true;

						//picking up food from foodbox
						for (int i = 0; i < foodBoxes.size(); i++)
						{
							if (Collision::SATIntersection(currentPlayer->getBoundingBox(), foodBoxes[i]->getInteractBoundingBox()))
							{
								//if food is held
								if (currentPlayer->getFoodHeld()->getFoodType()->getID() == "None")
								{
									currentPlayer->setFoodHeldType(foodBoxes[i]->getFoodTypeGiven());
									currentPlayer->setFoodHeldState(foodBoxes[i]->getFoodState());

									pressingPickupBuffer[gamePadIndex] = 0.f;
									rm->getAudioManager()->getSFXByName("Bop")->playAudio(0);
									break;
								}
							}
							else {

							}
						}


						//placing or picking up food from food device
						if (Collision::SATIntersection(currentPlayer->getBoundingBox(), cookDev->getInteractBoundingBox()))
						{

							//if food is held
							if (currentPlayer->getFoodHeld()->getFoodType()->getID() != "None")
							{
								bool addedFoodHeld = cookDev->addFood(currentPlayer->getFoodHeld());
								if (addedFoodHeld)
								{
									currentPlayer->setFoodHeldType(rm->getFoodTypeManager()->getFoodType("None"));
									pressingPickupBuffer[gamePadIndex] = 0.f;

								}

							}
							else
							{

								cookDev->getFood(currentPlayer->getFoodHeld());
								pressingPickupBuffer[gamePadIndex] = 0.f;
								if (currentPlayer->getFoodHeld()->getFoodType()->getID() != "None")
								{
									rm->getAudioManager()->getSFXByName("Bop")->playAudio(0);

								}


							}
						}

						//checking food collectors
						for (int f = 0; f < foodCollects.size(); f++)
						{
							//if collision with the interaction bounding box of food collector
							if (Collision::SATIntersection(currentPlayer->getBoundingBox(), foodCollects[f]->getInteractBoundingBox()))
							{
								//if player is holding something
								if (currentPlayer->getFoodHeld()->getFoodType()->getID() != "None")
								{
									//add the food!
									
									
									std::string ft = currentPlayer->getFoodHeld()->getFoodType()->getID();
									std::string fs = currentPlayer->getFoodHeld()->getFoodState();

									if (ft == "Meat")
									{
										if (fs == "Raw")
										{
											playerPoints[f] -= 4;
										}

										if (fs == "Cooked")
										{
											playerPoints[f] += 10;
										}
									}
									else if (ft == "Veg")
									{
										if (fs == "Raw")
										{
											playerPoints[f] -= 1;
										}

										if (fs == "Cooked")
										{
											playerPoints[f] += 3;
										}
									}
									else if (ft == "Fruit")
									{
										if (fs == "Raw")
										{
											playerPoints[f] += 1;
										}

										if (fs == "Cooked")
										{
											playerPoints[f] += 4;
										}
									}


									foodCollects[f]->addFood(currentPlayer->getFoodHeld());
									currentPlayer->setFoodHeldType(rm->getFoodTypeManager()->getFoodType("None"));
									pressingPickupBuffer[gamePadIndex] = 0.f;
									rm->getAudioManager()->getSFXByName("Ding")->playAudio(0);

									if (playerPoints[f] < 0)
									{
										playerPoints[f] = 0;
									}


								}
							}
						}

						if (Collision::SATIntersection(currentPlayer->getBoundingBox(), fodTab->getInteractBoundingBox()))
						{
							if (currentPlayer->getFoodHeld()->getFoodType()->getID() != "None")
							{
								if (fodTab->addFood(currentPlayer->getFoodHeld(), gamePadIndex))
								{
									currentPlayer->setFoodHeldType(rm->getFoodTypeManager()->getFoodType("None"));
									pressingPickupBuffer[gamePadIndex] = 0.f;
									rm->getAudioManager()->getSFXByName("Ding")->playAudio(0);
								}

							}
						}

					}

				}
				else {
					pressingPickup[gamePadIndex] = false;

				}

				if (pressingPickupBuffer[gamePadIndex] > 0.f)
				{
					pressingPickupBuffer[gamePadIndex] -= dt;
				}
				else {
					pressingPickupBuffer[gamePadIndex] = 0.f;
				}

				//throwing item

				if (km->keyPressed("k") || gp->buttonPress("x"))
				{
					if (!pressingThrowItem[gamePadIndex])
					{
						if (currentPlayer->getFoodHeld()->getFoodType()->getID() != "None")
						{
							if (projBank.size() > 0) {
								pressingThrowItem[gamePadIndex] = true;

								Projectile *p = projBank.back();
								p->setThrown(true);
								p->setShouldRender(true);
								currentPlayer->addProjectile(p);

								projBank.pop_back();

								//p->setTextureUVOffset(currentPlayer->getFoodHeld()->getFoodType()->getSpriteOffset(currentPlayer->getFoodHeld()->getFoodState()));
								p->setProjectileFood(currentPlayer->getFoodHeld());
								p->setPosition(currentPlayer->getPosition());

								switch (currentPlayer->getActorState())
								{
								case rightState:
									p->setVelocity(glm::vec3(400, 0, 0) + currentPlayer->getVelocity() / 2.f);
									break;
								case leftState:
									p->setVelocity(glm::vec3(-400, 0, 0) + currentPlayer->getVelocity() / 2.f);
									break;
								case downState:
									p->setVelocity(glm::vec3(0, 400, 0) + currentPlayer->getVelocity() / 2.f);
									break;
								case upState:
									p->setVelocity(glm::vec3(0, -400, 0) + currentPlayer->getVelocity() / 2.f);
									break;
								}

								currentPlayer->setFoodHeldType(rm->getFoodTypeManager()->getFoodType("None"));
							}
						}

					}
				}
				else {
					pressingThrowItem[gamePadIndex] = false;
				}


				if (gp->buttonDown("lb") || gp->getTriggerNormalised("left") > 0.3f)
				{
					currentPlayer->setLockDir(true);
				}
				else {
					currentPlayer->setLockDir(false);
				}


				/*if (gp->buttonPress("y"))
				{
					gameFinished = true;
					if (!takenAway[gamePadIndex])
					{
						takenAway[gamePadIndex] = true;
					}

				}
				else {
					takenAway[gamePadIndex] = false;
				}*/


				//update current player
				currentPlayer->update(dt);

				float healthPercent = float((currentPlayer->getHealth()) / float(currentPlayer->getMaxHealth()) *100.f);

				healthBars[gamePadIndex]->setProgressValue(healthPercent);

				std::vector<Projectile*> curPlayProj = currentPlayer->getChefProjectiles();
				std::vector<int> projectileIndexDelete;

				//go through projectiles per player
				for (int i = 0; i < curPlayProj.size(); i++)
				{
					//update projectile's position
					curPlayProj[i]->update(dt);

					//check if colliding with the other player
					if (Collision::SATIntersection(curPlayProj[i]->getBoundingBox(), players[otherPlayerIndex]->getHurtBox()))
					{
						glm::vec3 projVel = curPlayProj[i]->getVelocity() / 1.7f;

						projBank.push_back(curPlayProj[i]);

						curPlayProj[i]->setShouldRender(false);
						curPlayProj[i]->setPosition(glm::vec3(-200, -200, -200));
						curPlayProj[i]->setVelocity(glm::vec3(0));
						curPlayProj[i]->setThrown(false);
						curPlayProj.erase(curPlayProj.begin() + i);
						currentPlayer->removeProjectile(i);
						i--;

						//take health away
						//apply knockback and hitstun
						if (!players[otherPlayerIndex]->getInvincible())
						{
							players[otherPlayerIndex]->setHealth(-4, true);
							players[otherPlayerIndex]->setHit(true);
							players[otherPlayerIndex]->setVelocity(projVel);
							players[otherPlayerIndex]->setHitStunTimer(0.2f);
						}


						int  ranNum = rand() % 3;

						switch (ranNum)
						{
						case 0:
							rm->getAudioManager()->getSFXByName("FoodExplode1")->playAudio(0);
							break;
						case 1:
							rm->getAudioManager()->getSFXByName("FoodExplode3")->playAudio(0);
							break;
						case 2:
							rm->getAudioManager()->getSFXByName("FoodExplode4")->playAudio(0);
							break;
						default:
							break;
						}
					}
					else
						//colliding with tile
						if (mn->collideWithTile(curPlayProj[i], dt, true))
						{
							projBank.push_back(curPlayProj[i]);

							curPlayProj[i]->setShouldRender(false);
							curPlayProj[i]->setPosition(glm::vec3(-200, -200, -200));
							curPlayProj[i]->setVelocity(glm::vec3(0));
							curPlayProj[i]->setThrown(false);
							curPlayProj.erase(curPlayProj.begin() + i);
							currentPlayer->removeProjectile(i);
							i--;
						}
				}







				for (int i = 0; i < entities.size(); i++)
				{
					//printf("%i\n", i);
					//entities[i]->update(dt);






				}
				bool playerCollidedWithTile = mn->collideWithTile(currentPlayer, dt);
				collisionWithObjects(currentPlayer);


				if (cameraFollow)
				{


					glm::vec3 camPos = (players[0]->getCentrePosition()) - glm::vec3(platform->getRenderSize() / 2.f, 0);
					glm::vec2 camDim = camera->getDimensions();


					if (camPos.x < 0)
					{
						camPos.x = 0;
					}
					if ((camPos.x + camDim.x) > mn->getDimensions().x)
					{
						camPos.x = mn->getDimensions().x - camDim.x;
					}


					if (camPos.y < 0)
					{
						camPos.y = 0;
					}
					if ((camPos.y + camDim.y) > mn->getDimensions().y)
					{
						camPos.y = mn->getDimensions().y - camDim.y;

					}
					camPos *= glm::vec3(-1.f);

					//camera->setPosition(camPos);





					camPos = glm::vec3(round(camPos.x), round(camPos.y), 0);



				}

				if (fodTab->allFoodCollected(gamePadIndex))
				{
					gameFinished = true;
				}

				if (currentPlayer->getHealth() == 0)
				{
					gameFinished = true;
				}





				//pause game
				if (gp->buttonPress("start") || km->keyPressed("esc"))
				{
					pause = true;
				}


				if (mode == 1)
				{
					
					std::string str = std::to_string(playerPoints[gamePadIndex]);

					playerPointsText[gamePadIndex]->changeTextEnd(str);


				}






			}
			
			if (levelTimer->getTimerFinished())
			{
				gameFinished = true;
			}

			if (pause)
			{
				pause = false;
				std::vector<int> channelsUsed;
				for (int i = 0; i < sounds.size(); i++)
				{
					sounds[i]->pauseAudio();
				}
				currentBgMusic->pauseAudio();
				stateManager->addState(rm->getPauseState());
				rm->getPauseState()->pauseStateReference(pauseAction);




			}


			


			float tf = levelTimer->getTimeLeft();

			if (tf < 15)
			{
				if (!playingBGSpedUp)
				{
					currentBgMusic->stopAudio();
					currentBgMusic = bgMusic2x;
					currentBgMusic->playAudio(-1);
					playingBGSpedUp = true;
				}



				//printf("Time left: %f \n", tf);
			}
		}
		if (beginGameTimer < 2.3f)
		{
			beginGameTimer += dt;
		}
		
	}
	else
	{
		if (!endChime)
		{
			startCook->setShouldRender(false);
			rm->getAudioManager()->getSFXByName("PanLid")->playAudio(0);
			currentBgMusic->stopAudio();
			endChime = true;
			finishGame->setShouldRender(true);

			int platesMax = -1;

			for (int i = 0; i < players.size(); i++)
			{
				if (players[i]->getHealth() > 0)
				{
					//classic table delivery mode
					if (mode == 0)
					{
						int np = fodTab->getNumFoodFromSide(i);
						if (np > platesMax)
						{
							platesMax = np;
							playerWinner = i;
						}
						else if (np == platesMax)
						{
							playerWinner = -1;
						}
					}
					//points
					else if (mode == 1)
					{
						int np = playerPoints[i];

						if (np > platesMax)
						{
							platesMax = np;
							playerWinner = i;
						}
						else if (np == platesMax)
						{
							playerWinner = -1;
						}
					}
					
				}
				
			}
			winningCard->setWinner(playerWinner);
		}
		if (restartTimer < 2.1f)
		{
			restartTimer += dt;
		}
		else {
			pointsWinnerTimer += dt;
			if (!addedToScoreCard)
			{
				finishGame->setShouldRender(false);

				for (int i = 0; i < foodCollects.size(); i++)
				{
					scorCards[i]->addFoodCollected(foodCollects[i], playerPoints[i]);
					scorCards[i]->setShouldRender(true);
				}
				
				addedToScoreCard = true;


				if (mode == 0)
				{
					winningCard->setShouldRender(true);
					playAgainText->setShouldRender(true);
					returnMenuText->setShouldRender(true);
					canRestartGameEnd = true;
				}

				

			}
			
			if (canRestartGameEnd)
			{
				
				
				for (int gamePadIndex = 0; gamePadIndex < players.size(); gamePadIndex++)
				{
					gp = rm->getGamepad(gamePadIndex);
					//reset values
					//if (restartTimer > 0.6f)
					{
						if (km->keyPressed("h") || gp->buttonPress("start") || gp->buttonPress("a"))
						{
							resetGame();
						}

						if (km->keyPressed("esc") || gp->buttonPress("y"))
						{
							toMenu = true;
						}
					}

				}
			}
			else
			{
				if (pointsWinnerTimer > 1.f)
				{
					winningCard->setShouldRender(true);
					playAgainText->setShouldRender(true);
					returnMenuText->setShouldRender(true);
					canRestartGameEnd = true;
				}
			}

			if (toMenu)
			{
				rm->getAudioManager()->getMusicByName("Ingame")->stopAudio();
				stateManager->changeState(new MainMenuState(stateManager, platform, rm));
			}
		}
		
		
	}

}

/////////
//ON STATE LOAD
/////////
void GameState::load()
{
	TextureManager* tmng = rm->getTextureManager();

	startOfGame = true;
	gameFinished = false;
	pause = false;
	toMenu = false;
	
	pauseAction = "";
	endChime = false;

	origTimerValue = glm::vec3(2.0f, 0.f, 0.f);
	restartTimer = 0.f;
	pointsWinnerTimer = 0.f;

	canRestartGameEnd = false;


//	origTimerValue = glm::vec3(0.0f, 7.f, 0.f);

	camera->setDimensions(platform->getRenderSize());

	float centreRenderX = platform->getRenderSize().x / 2.f;

	playerWinner = -1;

	Texture* getR = tmng->getTextureByName("GetReady");
	Texture* startT = tmng->getTextureByName("CookExc");
	Texture* finishT = tmng->getTextureByName("Finish");


	getReady = new Entity(getR);
	getReady->setCentre(platform->getRenderSize() / 2.f);
	getReady->setShouldRender(false);

	startCook = new Entity(startT);
	startCook->setCentre(platform->getRenderSize() / 2.f);
	startCook->setShouldRender(false);

	finishGame = new Entity(finishT);
	finishGame->setCentre(platform->getRenderSize() / 2.f);
	finishGame->setShouldRender(false);




	hudElements.push_back(getReady);
	hudElements.push_back(startCook);
	hudElements.push_back(finishGame);

	beginGameTimer = 0.f;



	playingBGSpedUp = false;

	bgMusic = rm->getAudioManager()->getMusicByName("Ingame");
	

	bgMusic2x = rm->getAudioManager()->getMusicByName("Ingame2x");

	currentBgMusic = bgMusic;

	//sounds.push_back(currentBgMusic);
	sounds.push_back(rm->getAudioManager()->getSFXByName("CookGrowl"));
	sounds.push_back(rm->getAudioManager()->getSFXByName("Bop"));
	sounds.push_back(rm->getAudioManager()->getSFXByName("Ding"));

	//initialise player button press booleans
	for (int i = 0; i < rm->getNumGamePads(); i++)
	{
		bool pressPick = false;
		float pickBuff = 0.16f;

		bool pressThrow = false;

		

		

		pressingPickup.push_back(pressPick);
		pressingPickupBuffer.push_back(pickBuff);

		pressingThrowItem.push_back(pressThrow);







		bool takAway = false;

		takenAway.push_back(takAway);
	}

	
	


	mn = new MapRoom(rm->getMapManager(), rm->getTileTypeManager(), "M01");
 

	entities.push_back(mn);

	std::vector<Entity*> mnb = mn->getTilesEntities("B");
	std::vector<Entity*> mno = mn->getTilesEntities("O");

	
	Texture* t2 = tmng->getTextureByName("HobLarge");





	Texture* t3 = tmng->getTextureByName("Table");

	glm::vec3 tabPos = glm::vec3(centreRenderX, 140, 0);

	table = new WorldObject(t3, tabPos);
	table->setCentre(tabPos);

	//entities.push_back(table);

	Texture* plateTex = tmng->getTextureByName("Plate");
	fodTab = new FoodTable(t3, plateTex, rm->getFoodTypeManager());
	fodTab->setCentre(tabPos);
	
	if (mode == 0)
	{
		entities.push_back(fodTab);
		collisionObjects.push_back(fodTab);
	}
	


	/////////
	//PLAYER POSITIONS
	/////////

	float players1X = centreRenderX / 2.f;
	float players2X = players1X * 3.f;

	float playersY = platform->getRenderSize().y / 4.f;
	

	glm::vec3 player1Pos = glm::vec3(players1X, playersY, 0);
	glm::vec3 player2Pos = glm::vec3(players2X, playersY, 0);

	playerStartingPositions.push_back(player1Pos);
	playerStartingPositions.push_back(player2Pos);

	std::vector<glm::vec4> blendColours;

	glm::vec4 bc1 = glm::vec4(1.f, 1.f, 1.f, 1.f);
	glm::vec4 bc2 = glm::vec4(0.82f, 0.f, 0.f, 1.f);
	
	blendColours.push_back(bc1);
	blendColours.push_back(bc2);

	//glm::vec3 entDimens = glm::vec3(0, 0, 0);
	
//	e1 = new Chef(rm->getSpriteSheetManager()->getSpriteSheetByID("Chefcop"), entPos, glm::vec3(28,40,0));





	for (int i = 0; i < rm->getNumGamePads(); i++)
	{
		Chef *ch = new Chef(rm->getSpriteSheetManager()->getSpriteSheetByID("Chefcop"), playerStartingPositions[i], glm::vec3(28, 40, 0));
		ch->setBlendColour(blendColours[i]);
		players.push_back(ch);
	}

	for (int i = 0; i < players.size(); i++)
	{
		//players[i]->update(0.f);
	}



	////////
	//TEMS DISPLAY
	////////
	


	Texture* t1 = tmng->getTextureByName("ChefItemBorder");
	Entity* ep = new Entity(t1, glm::vec3(16, 16, 0));

	glm::vec3 ogPos = glm::vec3(16, 16, 0);
	glm::vec3 rightItemSlotPos = glm::vec3(platform->getRenderSize().x, 16, 0) - glm::vec3(t1->getOrigDimens().x +16.f, 0, 0);

	

	glm::vec3 itemPos = ep->getPosition() + glm::vec3(2, 2, 0);

	glm::vec3 itemPos2 = rightItemSlotPos + glm::vec3(2, 2, 0);


	

	
	f2 = new Food(rm->getFoodTypeManager()->getFoodSpriteSheet(), rm->getFoodTypeManager()->getFoodType("None"), "Raw", itemPos, glm::vec3(22, 22, 0));
	Food * foodPlayer2 = new Food(rm->getFoodTypeManager()->getFoodSpriteSheet(), rm->getFoodTypeManager()->getFoodType("None"), "Raw", itemPos2, glm::vec3(22, 22, 0));



	ItemSlot *is1 = new ItemSlot(t1, f2, ogPos);
	ItemSlot *is2 = new ItemSlot(t1, foodPlayer2, rightItemSlotPos);

	std::vector<Food*> foodieThings;
	foodieThings.push_back(f2);
	foodieThings.push_back(foodPlayer2);

	for (int i = 0; i < players.size(); i++)
	{
		players[i]->setFoodHeld(foodieThings[i]);
	}


	//e1->setFoodHeld(f2);
	//e2->setFoodHeld(foodPlayer2);

	//hudElements.push_back(ep);


	hudElements.push_back(is1);

	hudElements.push_back(is2);

	float rightHandxPos = platform->getRenderSize().x - 34 - t2->getOrigDimens().x;

	//meatbox
	FoodBox *fb = new FoodBox(t2,  rm->getFoodTypeManager()->getFoodType("Meat"), "Raw", glm::vec3(34, 250,0));
	fb->setBlendColour(glm::vec4(1.f, 0.43f, 0.78f, 1));

	foodBoxes.push_back(fb);


	FoodBox *fb2 = new FoodBox(t2, rm->getFoodTypeManager()->getFoodType("Veg"), "Raw", glm::vec3(34, 300, 0));
	fb2->setBlendColour(glm::vec4(0.99f, 0.42f, 0.007f, 1));

	foodBoxes.push_back(fb2);

	FoodBox *fb3 = new FoodBox(t2, rm->getFoodTypeManager()->getFoodType("Fruit"), "Raw", glm::vec3(34, 350, 0));
	fb3->setBlendColour(glm::vec4(1.f, 0, 0, 1));

	foodBoxes.push_back(fb3);

	FoodBox *fb4 = new FoodBox(t2, rm->getFoodTypeManager()->getFoodType("Meat"), "Raw", glm::vec3(rightHandxPos, 250, 0));
	fb4->setBlendColour(glm::vec4(1.f, 0.43f, 0.78f, 1));

	foodBoxes.push_back(fb4);


	FoodBox *fb5 = new FoodBox(t2, rm->getFoodTypeManager()->getFoodType("Veg"), "Raw", glm::vec3(rightHandxPos, 300, 0));
	fb5->setBlendColour(glm::vec4(0.99f, 0.42f, 0.007f, 1));

	foodBoxes.push_back(fb5);

	FoodBox *fb6 = new FoodBox(t2, rm->getFoodTypeManager()->getFoodType("Fruit"), "Raw", glm::vec3(rightHandxPos, 350, 0));
	fb6->setBlendColour(glm::vec4(1.f, 0, 0, 1));

	foodBoxes.push_back(fb6);




	for (int i = 0; i < foodBoxes.size(); i++)
	{
		entities.push_back(foodBoxes[i]);
		collisionObjects.push_back(foodBoxes[i]);
	}

	Texture *ol = tmng->getTextureByName("Outline3");
	Texture *barTe = tmng->getTextureByName("BarTexture");

	pb = new ProgressBar(barTe, ol, glm::vec3(300, 100, 0), glm::vec3(40, 10, 0), glm::vec3(1, 1, 0));

	//hudElements.push_back(pb);




	Texture *iconsText = tmng->getTextureByName("CookDeviceIcon");


	

	//Cooking device
	cookDev = new CookingDevice(t2, iconsText, pb, rm->getAudioManager()->getSFXByName("CookGrowl"), rm->getFoodTypeManager(), glm::vec3(400, 380, 0), glm::vec3(50, 50, 0), glm::vec3(24, 34, 0));
	cookDev->setBlendColour(glm::vec4(0.f, 1.f, 0.f, 1.f));
	cookDev->setCentre(glm::vec3(centreRenderX, 300, 0));
	entities.push_back(cookDev);
	collisionObjects.push_back(cookDev);



	

	
	//Food Collectors
	Texture* foodColText = tmng->getTextureByName("FoodCollector");
	foodColl = new FoodCollector(foodColText, rm->getFoodTypeManager(), glm::vec3(34, 80, 0), glm::vec3(foodColText->getOrigDimens(), 0));
	FoodCollector *foodCollRightside = new FoodCollector(foodColText, rm->getFoodTypeManager(), glm::vec3(platform->getRenderSize().x-34- foodColText->getOrigDimens().x, 80, 0), glm::vec3(foodColText->getOrigDimens(), 0));

	if (mode == 1)
	{
		foodCollects.push_back(foodColl);
		foodCollects.push_back(foodCollRightside);
	}
	

	for (int i = 0; i < foodCollects.size(); i++)
	{
		entities.push_back(foodCollects[i]);
		collisionObjects.push_back(foodCollects[i]);
	}

	

	//add player last so on top of everything else

	for (int i = 0; i < players.size(); i++)
	{
		entities.push_back(players[i]);
	}
	


	Food* projFood = new Food(rm->getFoodTypeManager()->getFoodSpriteSheet(), rm->getFoodTypeManager()->getFoodType("None"), "Raw", itemPos, glm::vec3(-400, -400, 0));

	int numProj = 100;

	for (int i = 0; i < numProj; i++)
	{
		Projectile *p = new Projectile(rm->getFoodTypeManager()->getFoodTypeTexture(), projFood, glm::vec3(-400,-400,0), glm::vec3(22, 22, 0));
		p->setShouldRender(false);
		projBank.push_back(p);
		entities.push_back(p);
	}
	
	
	


	//f2->setFoodType(e1->getFoodHeld()->getFoodType());

	

	
	levelTimer = new Timer(origTimerValue.x, origTimerValue.y, origTimerValue.z);

	levelTimerText = new TextTime(rm->getTextImageManager(), levelTimer);
	levelTimerText->setCentre(glm::vec3(centreRenderX, 26, 0));

	levelTimerText->startTime();
	levelTimerText->update(0.f);

	hudElements.push_back(levelTimerText);



	Text* timeText = new Text(rm->getTextImageManager(), "TIME", 32, "arial");


	timeText->setScale(glm::vec3(0.55f, 0.5f, 0.f));
	timeText->setCentre(glm::vec3(levelTimerText->getCentrePosition()));
	timeText->setPosition(glm::vec3(0, -17, 0), true);

	hudElements.push_back(timeText);






	//score card



	Texture *ol2 = new Texture("res/img/outline.png");
	//Texture *barTe = new Texture("res/img/bartex.png");


	

	ProgressBar* pb2 = new ProgressBar(barTe, ol2, glm::vec3(ogPos.x + 44 , 19, 0), glm::vec3(80, 20, 0), glm::vec3(1, 1, 0));

	ProgressBar* pb3 = new ProgressBar(barTe, ol2, glm::vec3(600, 19, 0), glm::vec3(80, 20, 0), glm::vec3(1, 1, 0));

	float rightBarPosX = is2->getPosition().x + is2->getDimensions().x - 44 - pb3->getDimensions().x;
	pb3->setPosition(glm::vec3(rightBarPosX, pb3->getPosition().y, 0));

	healthBars.push_back(pb2);
	healthBars.push_back(pb3);


	

	

	//hudElements.push_back(pb2);
	for (int i = 0; i < healthBars.size(); i++)
	{
		hudElements.push_back(healthBars[i]);
		
	}

	for (int i = 0; i < players.size(); i++)
	{
		float healthPercent = float((players[i]->getHealth()) / float(players[i]->getMaxHealth()) *100.f);
		healthBars[i]->setProgressValue(healthPercent);

		playerPoints.push_back(0);
	}

	Text* healthText1 = new Text(rm->getTextImageManager(), "Health", 32, "arial");
	Text* healthText2 = new Text(rm->getTextImageManager(), "Health", 32, "arial");

	healthText1->setPosition(glm::vec3(pb2->getPosition().x, pb2->getPosition().y - 15.f, 0));
	healthText2->setPosition(glm::vec3(pb3->getPosition().x, pb3->getPosition().y - 15.f, 0));

	healthText1->setScale(glm::vec3(0.55f));
	healthText2->setScale(glm::vec3(0.55f));
	

	hudElements.push_back(healthText1);
	hudElements.push_back(healthText2);


	if (mode == 1)
	{
		//score in text
		Text* scoreNumText1 = new Text(rm->getTextImageManager(), "0000");
		Text* scoreNumText2 = new Text(rm->getTextImageManager(), "0000");

		float sct1X = pb2->getPosition().x + pb2->getDimensions().x + 18.f;
		float sct1Y = pb2->getPosition().y - (scoreNumText1->getDimensions().y / 4.f) + 6.f;

		scoreNumText1->setPosition(glm::vec3(sct1X, sct1Y, 0.f));

		playerPointsText.push_back(scoreNumText1);


		float sct2X = pb3->getPosition().x - 18.f - scoreNumText2->getDimensions().x;


		scoreNumText2->setPosition(glm::vec3(sct2X, sct1Y, 0.f));



		playerPointsText.push_back(scoreNumText2);


		for (int i = 0; i < playerPointsText.size(); i++)
		{

			hudElements.push_back(playerPointsText[i]);
			playerPointsText[i]->setScale(glm::vec3(0.8f));
		}




		Text* scoreText1 = new Text(rm->getTextImageManager(), "Score");
		Text* scoreText2 = new Text(rm->getTextImageManager(), "Score");

		scoreText1->setPosition(glm::vec3(scoreNumText1->getPosition().x, pb2->getPosition().y - 15.f, 0));
		scoreText2->setPosition(glm::vec3(scoreNumText2->getPosition().x, pb3->getPosition().y - 15.f, 0));

		scoreText1->setScale(glm::vec3(0.55f));
		scoreText2->setScale(glm::vec3(0.55f));


		hudElements.push_back(scoreText1);
		hudElements.push_back(scoreText2);
	}


















	Texture *scBack = tmng->getTextureByName("ScoreBackground");

	scoreBackground = new Entity(scBack);
	

	glm::vec3 centreScBa;
	centreScBa.x = platform->getRenderSize().x / 4.f;
	centreScBa.y = platform->getRenderSize().y / 2.f;
	centreScBa.z = 0;

	scoreBackground->setCentre(centreScBa);

	//scoreBackground->setShouldRender(false);

	//hudElements.push_back(scoreBackground);


	scoCard = new ScoreCard(scBack, rm->getFoodTypeManager(), rm->getTextImageManager());
	scoCard->setCentre(centreScBa);

	ScoreCard* sc = new ScoreCard(scBack, rm->getFoodTypeManager(), rm->getTextImageManager());
	centreScBa.x *= 3.f;

	sc->setCentre(centreScBa);
	scorCards.push_back(scoCard);
	scorCards.push_back(sc);


	for (int i = 0; i < scorCards.size(); i++)
	{
		scorCards[i]->setShouldRender(false);
		hudElements.push_back(scorCards[i]);
	}

	Texture* wnBack = tmng->getTextureByName("WinBackground");

	winningCard = new WinCard(wnBack, rm->getTextImageManager());
	winningCard->setCentre(platform->getRenderSize() / 2.f);
	winningCard->setShouldRender(false);
	hudElements.push_back(winningCard);
	addedWinCard = false;
	
	//float textYP = platform->getRenderSize().y - (platform->getRenderSize().y / 10.f);

	float textYP = winningCard->getPosition().y + winningCard->getDimensions().y - (winningCard->getDimensions().y / 6.f)*2.f;
	float textYP2 = winningCard->getPosition().y + winningCard->getDimensions().y - (winningCard->getDimensions().y / 8.f);

	//textYP = 450.f;
	playAgainText = new Text(rm->getTextImageManager(), "A to play again!",  32, "arial", glm::vec3(0, 0, 0));
	playAgainText->setCentre(glm::vec3(centreRenderX, textYP, 0));
	playAgainText->setBlendColour(glm::vec4(1.0f, 1.f, 0.f, 1.0f));
	playAgainText->setShouldRender(false);
	hudElements.push_back(playAgainText);

	returnMenuText = new Text(rm->getTextImageManager(), "Y to return to menu!", 32, "arial", glm::vec3(0, 0, 0));
	returnMenuText->setCentre(glm::vec3(centreRenderX, textYP2, 0));
	returnMenuText->setBlendColour(glm::vec4(1.0f, 1.f, 0.f, 1.0f));
	returnMenuText->setShouldRender(false);
	hudElements.push_back(returnMenuText);



	








	
}

void GameState::unload()
{
/*
	for (int i = entities.size() -1; i > -1; i--)
	{
		delete entities[i];
	}
	entities.clear();
	

	for (int i = hudElements.size() -1; i > -1; i--)
	{
		delete hudElements[i];
	}
	delete camera;
	hudElements.clear();*/
	delete levelTimer;
	
}

bool GameState::collisionWithObjects(Actor *e1)
{
	bool collision = false;
	for (int i = 0; i < collisionObjects.size(); i++)
	{
		PenDir pdEnt;
		PenDir pdTile;

		if (Collision::SATSupport(e1->getBoundingBox(), collisionObjects[i]->getBoundingBox(), pdEnt, pdTile))
		{

			glm::vec3 changPos;
			glm::vec3 colDir;

			//check which collision to us
			if (pdEnt.penetration < pdTile.penetration)
			{
				//use pdEnt 
				changPos = pdEnt.penetration * -pdEnt.dir;
				colDir = -pdEnt.dir;
			}
			else {
				//use pdTile
				changPos = pdTile.penetration * pdTile.dir;
				colDir = pdTile.dir;
			}

			//make sure they're going towards each other
			//get relative velocity along collision direction

			glm::vec3 relativeVelocity = e1->getVelocity() - collisionObjects[i]->getVelocity();
			glm::vec3 relVelAlongNormal = relativeVelocity * colDir;
			float relVelNorm = relVelAlongNormal.x + relVelAlongNormal.y;

			//make sure tile and actor are actually going towards each other
			//stops rare bugs when velocity stops after colliding with a wall not actual moving towards
			if (relVelNorm > 0)
			{
				continue;
			}

			e1->hitStaticObject(colDir);
			e1->setPosition(changPos, true);
			collision = true;
		}

	}
	return collision;

}


void GameState::resetGame()
{
	

	for (int i = 0; i < foodCollects.size(); i++)
	{
		foodCollects[i]->clearFood();
	}
	cookDev->resetCookDevice(rm->getFoodTypeManager());

	gameFinished = false;

	for (int i = 0; i < scorCards.size(); i++)
	{
		scorCards[i]->resetScore();
		scorCards[i]->setShouldRender(false);

		addedToScoreCard = false;
	}
	winningCard->setShouldRender(false);
	addedWinCard = false;

	for (int i = 0; i < players.size(); i++)
	{


		players[i]->setPosition(playerStartingPositions[i]);
		players[i]->setFoodHeldType(rm->getFoodTypeManager()->getFoodType("None"));
		players[i]->setInvincible(false);

		
		players[i]->setFullHealth();
		players[i]->setActorState(downState);
		players[i]->setVelocity(glm::vec3(0));
		std::vector<Projectile*> curPlayProj = players[i]->getChefProjectiles();
		std::vector<int> projectileIndexDelete;

		for (int j = 0; j < curPlayProj.size(); j++)
		{
			curPlayProj[j]->setShouldRender(false);
			curPlayProj[j]->setPosition(glm::vec3(-200, -200, -200));
			curPlayProj[j]->setVelocity(glm::vec3(0));
			curPlayProj[j]->setThrown(false);
			players[i]->removeProjectile(j);
			curPlayProj.erase(curPlayProj.begin() + j);
			
			j--;
		}
		players[i]->update(0.f);

		healthBars[i]->setProgressValue(100.f);
	}

	for (int i = 0; i < playerPoints.size(); i++)
	{
		playerPoints[i] = 0;
		if (mode == 1)
		{

			std::string str = std::to_string(playerPoints[i]);

			playerPointsText[i]->changeTextEnd(str);


		}
	}
	


	levelTimer->setTimer(origTimerValue.x, origTimerValue.y, origTimerValue.z);
	levelTimerText->update(0.f);

	fodTab->clearFood();

	playAgainText->setShouldRender(false);
	returnMenuText->setShouldRender(false);

	currentBgMusic->stopAudio();
	currentBgMusic = bgMusic;
	
	playingBGSpedUp = false;
	endChime = false;

	restartTimer = 0.f;
	toMenu = false;

	getReady->setShouldRender(false);
	startCook->setShouldRender(false);
	finishGame->setShouldRender(false);

	startOfGame = true;
	beginGameTimer = 0.f;

	playerWinner = -1;
	winningCard->resetCard();


	pointsWinnerTimer = 0.f;

	canRestartGameEnd = false;


}