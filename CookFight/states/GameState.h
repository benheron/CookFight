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

#include "../entities/HUD/ScoreCard.h"

#include "../Utilities/Time/Timer.h"

#include "../entities/HUD/ProgressBar.h"

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


	bool collisionWithObjects(Actor *e1);


	bool cameraFollow = true;



	MapRoom *mn;


	Background *bg;

	ResourceManager* rm;

	KeyboardManager*km;
	Gamepad* gp;


	Chef* e1;

	std::vector<Chef*> players;

	std::vector<Food*> playerFood;
	Food *f2;


	WorldObject *hob;
	WorldObject *table;

	std::vector<WorldObject*> collisionObjects;


	std::vector<FoodBox*> foodBoxes;

	CookingDevice *cookDev;
	FoodCollector *foodColl;

	std::vector<FoodCollector*> foodCollects;

	std::vector<Projectile*> projBank;
	
	bool postVel = false;
	float speedWhenStopped = 0.f;

	std::vector<bool> pressingPickup;
	std::vector<float> pressingPickupBuffer;
	//bool pressingPickup = false;
	
	std::vector<bool> pressingThrowItem;


	Timer *levelTimer;
	TextTime* levelTimerText;
	

	std::vector<Entity*> shadows;


	bool gameFinished;



	Entity* scoreBackground;
	
	ScoreCard* scoCard;

	std::vector<ScoreCard*> scorCards;
	

	bool addedToScoreCard = false;

	ProgressBar *pb;
};