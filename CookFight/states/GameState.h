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
#include "../entities/Food/FoodTable.h"
#include "../entities/HUD/TextTime.h"

#include "../entities/HUD/ScoreCard.h"
#include "../entities/HUD/WinCard.h"

#include "../Utilities/Time/Timer.h"

#include "../entities/HUD/ProgressBar.h"
#include "../entities/HUD/ItemSlot.h"


class PauseState;
class GameOverState;

class GameState : public State
{
public:
	GameState(StateManager* manager, Platform *platform, ResourceManager* rm, int mode);
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


	void resetGame();

	bool collisionWithObjects(Actor *e1);


	int mode;


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



	std::vector<ProgressBar*> healthBars;

	std::vector<bool> takenAway;





	std::vector<glm::vec3> playerStartingPositions;

	bool pause;

	std::string pauseAction;

	Text* playAgainText;
	Text* returnMenuText;

	glm::vec3 origTimerValue;




	std::vector<Audio*> sounds;
	Audio* bgMusic;

	Audio* bgMusic2x;

	Audio* currentBgMusic;

	bool playingBGSpedUp;

	FoodTable* fodTab;

	float restartTimer;

	float beginGameTimer;

	bool endChime;


	Entity* getReady;
	Entity* startCook;
	Entity* finishGame;

	bool startOfGame;
	WinCard * winningCard;

	bool addedWinCard;

	int playerWinner;


	float pointsWinnerTimer;

	bool canRestartGameEnd;


	std::vector<int> playerPoints;
	std::vector<Text*> playerPointsText;

	bool toMenu;

};