#include "StateManager.h"

#include "../text/Text.h"
#include "../Camera.h"
#include "../Collision.h"

#include "../entities/HUD/Button.h"

#include "../ResourceManager.h"
#include "MainMenuState.h"

class PauseState : public State
{
public:
	PauseState(StateManager* manager, Platform *platform, ResourceManager* rm);
	virtual ~PauseState();

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


	void pauseStateReference(std::string &pa) { pauseAction = pa; }

	std::string getPauseAction() { std::string retPause = pauseAction; pauseAction = ""; return retPause; }



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


	Gamepad* gp;
	KeyboardManager* km;
	bool removeThisState;

	bool quitToDesk;

	std::vector<Button*> buttons;
	int indexHighlighted;

	std::string pauseAction;

};