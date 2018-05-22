#include "GameState.h"
#include "GameOverState.h"

GameState::GameState(StateManager* manager, Platform *platform, ResourceManager* rm) : State(manager, platform), rm(rm)
{
	km = rm->getKeyboardManager();
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
	if (!gameFinished)
	{
		for (int gamePadIndex = 0; gamePadIndex < rm->getNumGamePads(); gamePadIndex++)
		{
			Gamepad* gp = rm->getGamepad(gamePadIndex);
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


			currentPlayer->moveActor(dir, mag, dt);






			if (km->keyDown("up"))
			{
				camera->setScale(glm::vec3(2.f*dt, 2.f*dt, 0), true);

			}

			if (km->keyDown("down"))
			{
				camera->setScale(glm::vec3(-2.f*dt, -2.f*dt, 0), true);

			}


			/*
			if (!km->keyDown("a") &&
			!km->keyDown("d") &&
			!km->keyDown("w") &&
			!km->keyDown("s") &&
			!gp->buttonDown("dLeft") &&
			!gp->buttonDown("dRight") &&
			!gp->buttonDown("dUp") &&
			!gp->buttonDown("dDown")
			)
			{
			e1->setMoving(false);

			}*/

			if (km->keyDown("c"))
			{
				cameraFollow = !cameraFollow;
			}

			/*if (km->keyDown("j") || km->keyDown("space") || gp->buttonDown("a"))
			{


			if (!pressingPickup)
			{
			pressingPickup = true;
			pressingPickupBuffer = 0.16f;
			}
			}
			else
			{
			pressingPickupBuffer -= dt;
			if (pressingPickupBuffer < 0.f)
			{
			pressingPickup = false;
			}

			}*/



			if (km->keyDown("j") || km->keyDown("space") || gp->buttonDown("a") || pressingPickupBuffer[gamePadIndex] > 0.f)
			{


				if (!pressingPickup[gamePadIndex] || pressingPickupBuffer[gamePadIndex] > 0.f)
				{
					if (!pressingPickup[gamePadIndex])
					{
						//give player a buffer window if miss the pickup hitbox by a 7th of a second
						pressingPickupBuffer[gamePadIndex] = 0.116f;

					}

					pressingPickup[gamePadIndex] = true;


					for (int i = 0; i < foodBoxes.size(); i++)
					{
						if (Collision::SATIntersection(currentPlayer->getBoundingBox(), foodBoxes[i]->getInteractBoundingBox()))
						{
							currentPlayer->setFoodHeldType(foodBoxes[i]->getFoodTypeGiven());
							currentPlayer->setFoodHeldState(foodBoxes[i]->getFoodState());

							pressingPickupBuffer[gamePadIndex] = 0.f;
						}
						else {
							
						}
					}



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
	

						}
					}
					for (int f = 0; f < foodCollects.size(); f++)
					{
						if (Collision::SATIntersection(currentPlayer->getBoundingBox(), foodCollects[f]->getInteractBoundingBox()))
						{
							if (currentPlayer->getFoodHeld()->getFoodType()->getID() != "None")
							{
								foodCollects[f]->addFood(currentPlayer->getFoodHeld());
								currentPlayer->setFoodHeldType(rm->getFoodTypeManager()->getFoodType("None"));
								pressingPickupBuffer[gamePadIndex] = 0.f;
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

			if (km->keyDown("k") || gp->buttonDown("x"))
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

							p->setTextureUVOffset(currentPlayer->getFoodHeld()->getFoodType()->getSpriteOffset(currentPlayer->getFoodHeld()->getFoodState()));
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





			//update current player
			currentPlayer->update(dt);
			

			std::vector<Projectile*> curPlayProj = currentPlayer->getChefProjectiles();
			std::vector<int> projectileIndexDelete;

			for (int i = 0; i < curPlayProj.size(); i++)
			{
				curPlayProj[i]->update(dt);

				if (mn->collideWithTile(curPlayProj[i], dt))
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




			if (km->keyDown("h"))
			{
				pb->setProgressValue(60.f *dt, true);
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


				glm::vec3 camPos = (e1->getCentrePosition()) - glm::vec3(platform->getRenderSize() / 2.f, 0);
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

				camera->setPosition(camPos);





				camPos = glm::vec3(round(camPos.x), round(camPos.y), 0);


				//bg->update(dt, camPos);

			}
			
		}
		cookDev->update(dt);
		levelTimerText->update(dt);
		if (levelTimer->getTimerFinished())
		{
			//gameFinished = true;
		}

		
	}
	else
	{
		if (!addedToScoreCard)
		{
			for (int i = 0; i < scorCards.size(); i++)
			{
				scorCards[i]->addFoodCollected(foodCollects[i]);
				scorCards[i]->setShouldRender(true);

				addedToScoreCard = true;
			}
			
		}
		
	}

}


void GameState::load()
{
	gameFinished = false;
	
	camera->setDimensions(platform->getRenderSize());

	//initialise player button press booleans
	for (int i = 0; i < rm->getNumGamePads(); i++)
	{
		bool pressPick = false;
		float pickBuff = 0.16f;

		bool pressThrow = false;

		pressingPickup.push_back(pressPick);
		pressingPickupBuffer.push_back(pickBuff);

		pressingThrowItem.push_back(pressThrow);
	}

	
	


	mn = new MapRoom(rm->getMapManager(), rm->getTileTypeManager(), "M01");
 

	/*bg = new Background(rm->getBackgroundManager()->getBackgroundsByID("Grassland"), mn->getDimensions());

	entities.push_back(bg);*/
	entities.push_back(mn);

	std::vector<Entity*> mnb = mn->getTilesEntities("B");
	std::vector<Entity*> mno = mn->getTilesEntities("O");

	
	Texture* t2 = new Texture("res/img/hobLarge.png");

	glm::vec3 hobPos = glm::vec3(140, 90, 0);

	hob = new WorldObject(t2, hobPos);

	entities.push_back(hob);




	Texture* t3 = new Texture("res/img/table.png");

	glm::vec3 tabPos = glm::vec3(250, 140, 0);

	table = new WorldObject(t3, tabPos);

	entities.push_back(table);








	glm::vec3 entPos = glm::vec3(0, 0, 0);
	//glm::vec3 entDimens = glm::vec3(0, 0, 0);
	
	e1 = new Chef(rm->getSpriteSheetManager()->getSpriteSheetByID("Chefcop"), entPos, glm::vec3(28,40,0));

	players.push_back(e1);

	

	e1->setPosition(glm::vec3(80, 70, 0));
	//e1->setRoll(Collision::PI/2, false);

	Chef *e2 = new Chef(rm->getSpriteSheetManager()->getSpriteSheetByID("Chefcop"), entPos, glm::vec3(28, 40, 0));
	e2->setBlendColour(glm::vec4(0.82f, 0.f, 0.f, 1.f));


	e2->setPosition(glm::vec3(500, 70, 0));

	players.push_back(e2);



	collisionObjects.push_back(hob);

	collisionObjects.push_back(table);
	


	
	


	Texture* t1 = new Texture("res/img/chefitemborder.png");
	Entity* ep = new Entity(t1, glm::vec3(16, 16, 0));

	glm::vec3 itemPos = ep->getPosition() + glm::vec3(2, 2, 0);

	glm::vec3 itemPos2 = ep->getPosition() + glm::vec3(400, 2, 0);



	
	f2 = new Food(rm->getFoodTypeManager()->getFoodSpriteSheet(), rm->getFoodTypeManager()->getFoodType("None"), "Raw", itemPos, glm::vec3(22, 22, 0));
	Food * foodPlayer2 = new Food(rm->getFoodTypeManager()->getFoodSpriteSheet(), rm->getFoodTypeManager()->getFoodType("None"), "Raw", itemPos2, glm::vec3(22, 22, 0));

	e1->setFoodHeld(f2);
	e2->setFoodHeld(foodPlayer2);

	hudElements.push_back(ep);


	hudElements.push_back(f2);

	hudElements.push_back(foodPlayer2);

	float rightHandxPos = platform->getRenderSize().x - 34 - t2->getOrigDimens().x;

	//meatbox
	FoodBox *fb = new FoodBox(t2,  rm->getFoodTypeManager()->getFoodType("Meat"), "Raw", glm::vec3(34, 300,0));
	fb->setBlendColour(glm::vec4(1.f, 0.43f, 0.78f, 1));

	foodBoxes.push_back(fb);


	FoodBox *fb2 = new FoodBox(t2, rm->getFoodTypeManager()->getFoodType("Veg"), "Raw", glm::vec3(34, 350, 0));
	fb2->setBlendColour(glm::vec4(0.99f, 0.42f, 0.007f, 1));

	foodBoxes.push_back(fb2);

	FoodBox *fb3 = new FoodBox(t2, rm->getFoodTypeManager()->getFoodType("Fruit"), "Raw", glm::vec3(34, 400, 0));
	fb3->setBlendColour(glm::vec4(1.f, 0, 0, 1));

	foodBoxes.push_back(fb3);

	FoodBox *fb4 = new FoodBox(t2, rm->getFoodTypeManager()->getFoodType("Meat"), "Raw", glm::vec3(rightHandxPos, 300, 0));
	fb4->setBlendColour(glm::vec4(1.f, 0.43f, 0.78f, 1));

	foodBoxes.push_back(fb4);


	FoodBox *fb5 = new FoodBox(t2, rm->getFoodTypeManager()->getFoodType("Veg"), "Raw", glm::vec3(rightHandxPos, 350, 0));
	fb5->setBlendColour(glm::vec4(0.99f, 0.42f, 0.007f, 1));

	foodBoxes.push_back(fb5);

	FoodBox *fb6 = new FoodBox(t2, rm->getFoodTypeManager()->getFoodType("Fruit"), "Raw", glm::vec3(rightHandxPos, 400, 0));
	fb6->setBlendColour(glm::vec4(1.f, 0, 0, 1));

	foodBoxes.push_back(fb6);




	for (int i = 0; i < foodBoxes.size(); i++)
	{
		entities.push_back(foodBoxes[i]);
		collisionObjects.push_back(foodBoxes[i]);
	}

	Texture *ol = new Texture("res/img/outline3.png");
	Texture *barTe = new Texture("res/img/bartex.png");

	pb = new ProgressBar(barTe, ol, glm::vec3(300, 100, 0), glm::vec3(40, 10, 0), glm::vec3(1, 1, 0));

	//hudElements.push_back(pb);




	Texture *iconsText = new Texture("res/img/cookdeviceicon.png");



	//Cooking device
	cookDev = new CookingDevice(t2, iconsText, pb, rm->getFoodTypeManager(), glm::vec3(400, 380, 0), glm::vec3(50, 50, 0), glm::vec3(24, 34, 0));
	cookDev->setBlendColour(glm::vec4(0.f, 1.f, 0.f, 1.f));
	entities.push_back(cookDev);
	collisionObjects.push_back(cookDev);

	
	//Food Collectors
	Texture* foodColText = new Texture("res/img/foodcollector.png");
	foodColl = new FoodCollector(foodColText, rm->getFoodTypeManager(), glm::vec3(34, 80, 0), glm::vec3(foodColText->getOrigDimens(), 0));
	FoodCollector *foodCollRightside = new FoodCollector(foodColText, rm->getFoodTypeManager(), glm::vec3(platform->getRenderSize().x-34- foodColText->getOrigDimens().x, 80, 0), glm::vec3(foodColText->getOrigDimens(), 0));

	foodCollects.push_back(foodColl);
	foodCollects.push_back(foodCollRightside);

	for (int i = 0; i < foodCollects.size(); i++)
	{
		entities.push_back(foodCollects[i]);
		collisionObjects.push_back(foodCollects[i]);
	}

	

	//add player last so on top of everything else
	entities.push_back(e1);
	entities.push_back(e2);


	int numProj = 100;

	for (int i = 0; i < numProj; i++)
	{
		Projectile *p = new Projectile(e1->getFoodHeld()->getFoodType()->getTexture(), e1->getFoodHeld()->getFoodType(), e1->getPosition(), glm::vec3(22, 22, 0));
		p->setShouldRender(false);
		projBank.push_back(p);
		entities.push_back(p);
	}
	
	
	


	//f2->setFoodType(e1->getFoodHeld()->getFoodType());

	
	levelTimer = new Timer(0, 40.f);

	levelTimerText = new TextTime(rm->getTextImageManager(), levelTimer);

	levelTimerText->startTime();

	hudElements.push_back(levelTimerText);

	//score card

	Texture *scBack = new Texture("res/img/scorebackground.png");

	scoreBackground = new Entity(scBack);
	

	glm::vec3 centreScBa;
	centreScBa.x = platform->getRenderSize().x / 4.f;
	centreScBa.y = platform->getRenderSize().y / 2.f;

	scoreBackground->setCentre(centreScBa);

	//scoreBackground->setShouldRender(false);

	//hudElements.push_back(scoreBackground);


	scoCard = new ScoreCard(scBack, rm->getFoodTypeManager(), rm->getTextImageManager());
	scoCard->setCentre(centreScBa);

	ScoreCard* sc = new ScoreCard(scBack, rm->getFoodTypeManager(), rm->getTextImageManager());
	centreScBa.x *= 3;

	sc->setCentre(centreScBa);
	scorCards.push_back(scoCard);
	scorCards.push_back(sc);

	for (int i = 0; i < scorCards.size(); i++)
	{
		scorCards[i]->setShouldRender(false);
		hudElements.push_back(scorCards[i]);
	}
	
	
	
}

void GameState::unload()
{
	
	delete mn;
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