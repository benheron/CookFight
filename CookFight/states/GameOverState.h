#include "State.h"
#include "../ResourceManager.h"
#include "../text/Text.h"
#include "../Camera.h"
#include "../Collision.h"
#include "GameState.h"




class GameOverState : public State
{
public:
	GameOverState(StateManager* manager, Platform *platform, ResourceManager* rm);
	virtual ~GameOverState();

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

	ResourceManager* rm;

};