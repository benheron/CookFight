#pragma once
#include "StateManager.h"
#include "../ResourceManager.h"
#include "../text/Text.h"
#include "../Camera.h"
#include "../Collision.h"
#include "../levelManagement/MapRoom.h"
#include "../entities/Chef.h"
#include "../Background/Background.h"

#include "../entities/Food/FoodBox.h"
#include "../entities/Projectile.h"

#include "../entities/Food/CookingDevice.h"
#include "../entities/Food/FoodCollector.h"
#include "../entities/HUD/TextTime.h"

#include "../Utilities/Time/Timer.h"

class GameOverState;

class GameState : public State
{
public:
	GameState(StateManager* manager, Platform *platform, ResourceManager* rm);
	virtual ~GameState();

	/**
	@brief Handles any events such as keyboard/mouse input.

	@return true to exit, false to continue.
	*/
	bool eventHandler();

	/**
	@brief Update any internal values.

	@param dt - delta time.
	*/
	void update(float dt);

	
protected:

	/**
	@brief Loads this State.
	*/
	virtual void load();

	/**
	@brief Unloads this State.
	*/
	virtual void unload();


	bool collisionWithObjects();


	bool cameraFollow = true;



	MapRoom *mn;


	Background *bg;

	ResourceManager* rm;

	KeyboardManager*km;
	Gamepad* gp;


	Chef* e1;

	Food *f2;


	WorldObject *hob;
	WorldObject *table;

	std::vector<WorldObject*> collisionObjects;


	std::vector<FoodBox*> foodBoxes;

	CookingDevice *cookDev;
	FoodCollector *foodColl;

	std::vector<Projectile*> projectiles;
	std::vector<Projectile*> projBank;
	
	bool postVel = false;
	float speedWhenStopped = 0.f;


	bool pressingPickup = false;
	bool pressingThrowItem = false;


	Timer *levelTimer;
	TextTime* levelTimerText;
	
	
};