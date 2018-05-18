#include "GameState.h"
#include "GameOverState.h"

GameState::GameState(StateManager* manager, Platform *platform, ResourceManager* rm) : State(manager, platform), rm(rm)
{
	km = rm->getKeyboardManager();
	gp = rm->getGamepad();
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

	
	e1->moveActor(dir, mag, dt);
	

	



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

	



	if (km->keyDown("j") || km->keyDown("space") || gp->buttonDown("a"))
	{
		
		
		if (!pressingPickup)
		{
			pressingPickup = true;
			for (int i = 0; i < foodBoxes.size(); i++)
			{
				if (Collision::SATIntersection(e1->getBoundingBox(), foodBoxes[i]->getInteractBoundingBox()))
				{
					//e1->setBlendColour(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
				//	e1->setFoodHeld(new Food(rm->getFoodTypeManager()->getFoodSpriteSheet(), rm->getFoodTypeManager()->getFoodType("Veg"), glm::vec3(0), glm::vec3(22, 22, 0)));
					e1->setFoodHeldType(foodBoxes[i]->getFoodTypeGiven());
					f2->setFoodType(e1->getFoodHeld()->getFoodType());
					e1->setFoodHeldState(foodBoxes[i]->getFoodState());
				}
				else {
				//	e1->setFoodHeldType(rm->getFoodTypeManager()->getFoodType("None"));
				//	f2->setFoodType(e1->getFoodHeld()->getFoodType());
				}
			}



			if (Collision::SATIntersection(e1->getBoundingBox(), cookDev->getInteractBoundingBox()))
			{
				
				//if food is held
				if (e1->getFoodHeld()->getFoodType()->getID() != "None")
				{
					bool addedFoodHeld = cookDev->addFood(e1->getFoodHeld());
					if (addedFoodHeld)
					{
						e1->setFoodHeldType(rm->getFoodTypeManager()->getFoodType("None"));
						//f2->setFoodType(e1->getFoodHeld()->getFoodType());
					}
					
				}
				else
				{
					cookDev->getFood(e1->getFoodHeld());
					
					//f2->setFoodType(e1->getFoodHeld()->getFoodType());
					//f2->setFoodState(e1->getFoodHeldState());

					int cj = 0;

				}
			}

			if (Collision::SATIntersection(e1->getBoundingBox(), foodColl->getInteractBoundingBox()))
			{
				if (e1->getFoodHeld()->getFoodType()->getID() != "None")
				{
					foodColl->addFood(e1->getFoodHeld());
					e1->setFoodHeldType(rm->getFoodTypeManager()->getFoodType("None"));
				}
			}
		}
		
	}
	else {
		pressingPickup = false;
	}

	if (km->keyDown("k") || gp->buttonDown("x"))
	{
		if (!pressingThrowItem)
		{
			if (e1->getFoodHeld()->getFoodType()->getID() != "None")
			{
			
				pressingThrowItem = true;
				
				Projectile *p = projBank.back();
				p->setThrown(true);
				p->setShouldRender(true);
				projectiles.push_back(p);

				projBank.pop_back();

				p->setTextureUVOffset(e1->getFoodHeld()->getFoodType()->getSpriteOffset(e1->getFoodHeld()->getFoodState()));
				p->setPosition(e1->getPosition());

				switch (e1->getActorState())
				{
				case rightState:
					p->setVelocity(glm::vec3(400, 0, 0) + e1->getVelocity() / 2.f);
					break;
				case leftState:
					p->setVelocity(glm::vec3(-400, 0, 0) + e1->getVelocity() / 2.f);
					break;
				case downState:
					p->setVelocity(glm::vec3(0, 400, 0) + e1->getVelocity() / 2.f);
					break;
				case upState:
					p->setVelocity(glm::vec3(0, -400, 0) + e1->getVelocity() / 2.f);
					break;
				}

				e1->setFoodHeldType(rm->getFoodTypeManager()->getFoodType("None"));
			}

		}
	}
	else {
		pressingThrowItem = false;
	}


	
		
	

	e1->update(dt);
	cookDev->update(dt);
	levelTimerText->update(dt);

	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles[i]->update(dt);

		if (mn->collideWithTile(projectiles[i], dt))
		{
			projBank.push_back(projectiles[i]);

			projectiles[i]->setShouldRender(false);
			projectiles[i]->setPosition(glm::vec3(-200, -200, -200));
			projectiles[i]->setVelocity(glm::vec3(0));
			projectiles[i]->setThrown(false);
			projectiles.erase(projectiles.begin() + i);

		}
	}


	
	

	

	for (int i = 0; i < entities.size(); i++)
	{
		//printf("%i\n", i);
		//entities[i]->update(dt);



	


	}
	bool playerCollidedWithTile = mn->collideWithTile(e1, dt);
	collisionWithObjects();
	

	if (cameraFollow)
	{
		

		glm::vec3 camPos = (e1->getCentrePosition()) - glm::vec3(platform->getRenderSize() / 2.f, 0);
		glm::vec2 camDim = camera->getDimensions();


		if (camPos.x < 0)
		{
			camPos.x = 0;
		}
		if ((camPos.x + camDim.x) > mn->getDimensions().x )
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
		camPos *= glm::vec3(-1.f) ;

		camera->setPosition(camPos);



		

		camPos = glm::vec3(round(camPos.x), round(camPos.y), 0);


		//bg->update(dt, camPos);

	}




}


void GameState::load()
{
	
	
	camera->setDimensions(platform->getRenderSize());



	


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

	e1->setPosition(glm::vec3(80, 70, 0));
	//e1->setRoll(Collision::PI/2, false);

	



	collisionObjects.push_back(hob);

	collisionObjects.push_back(table);
	


	
	


	Texture* t1 = new Texture("res/img/chefitemborder.png");
	Entity* ep = new Entity(t1, glm::vec3(16, 16, 0));

	glm::vec3 itemPos = ep->getPosition() + glm::vec3(2, 2, 0);



	
	f2 = new Food(rm->getFoodTypeManager()->getFoodSpriteSheet(), rm->getFoodTypeManager()->getFoodType("None"), "Raw", itemPos, glm::vec3(22, 22, 0));

	e1->setFoodHeld(f2);


	hudElements.push_back(ep);


	hudElements.push_back(f2);


	//meatbox
	FoodBox *fb = new FoodBox(t2,  rm->getFoodTypeManager()->getFoodType("Meat"), "Raw", glm::vec3(35, 300,0));
	fb->setBlendColour(glm::vec4(1.f, 0.43f, 0.78f, 1));

	entities.push_back(fb);
	collisionObjects.push_back(fb);
	foodBoxes.push_back(fb);


	FoodBox *fb2 = new FoodBox(t2, rm->getFoodTypeManager()->getFoodType("Veg"), "Raw", glm::vec3(35, 350, 0));
	fb2->setBlendColour(glm::vec4(0.99f, 0.42f, 0.007f, 1));

	entities.push_back(fb2);
	collisionObjects.push_back(fb2);
	foodBoxes.push_back(fb2);

	FoodBox *fb3 = new FoodBox(t2, rm->getFoodTypeManager()->getFoodType("Fruit"), "Raw", glm::vec3(35, 400, 0));
	fb3->setBlendColour(glm::vec4(1.f, 0, 0, 1));

	entities.push_back(fb3);
	collisionObjects.push_back(fb3);
	foodBoxes.push_back(fb3);

	Texture *iconsText = new Texture("res/img/cookdeviceicon.png");

	cookDev = new CookingDevice(t2, iconsText, rm->getFoodTypeManager(), glm::vec3(400, 380, 0), glm::vec3(50, 50, 0), glm::vec3(24, 34, 0));
	cookDev->setBlendColour(glm::vec4(0.f, 1.f, 0.f, 1.f));
	entities.push_back(cookDev);
	collisionObjects.push_back(cookDev);


	Texture* foodColText = new Texture("res/img/foodcollector.png");
	foodColl = new FoodCollector(foodColText, rm->getFoodTypeManager(), glm::vec3(34, 80, 0), glm::vec3(foodColText->getOrigDimens(), 0));
	entities.push_back(foodColl);
	collisionObjects.push_back(foodColl);

	//add player last so on top of everything else
	entities.push_back(e1);


	int numProj = 100;

	for (int i = 0; i < numProj; i++)
	{
		Projectile *p = new Projectile(e1->getFoodHeld()->getFoodType()->getTexture(), e1->getFoodHeld()->getFoodType(), e1->getPosition(), glm::vec3(22, 22, 0));
		p->setShouldRender(false);
		projBank.push_back(p);
		entities.push_back(p);
	}
	
	
	


	f2->setFoodType(e1->getFoodHeld()->getFoodType());

	
	levelTimer = new Timer(3);

	levelTimerText = new TextTime(rm->getTextImageManager(), levelTimer);

	levelTimerText->startTime();

	hudElements.push_back(levelTimerText);


}

void GameState::unload()
{
	
	delete mn;
}

bool GameState::collisionWithObjects()
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