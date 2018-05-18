#include <string>
#include "../Platform.h"

#include "../entities/Entity.h"
#include "../Camera.h"
#include "../text/Text.h"

#pragma once


struct TextModMat
{
	Model* m;
	Texture* t;
	glm::mat4 matrix;
};




class StateManager;

/**
@class State
@brief A game state that contains one screen of the game such as a Menu or the game itself
*/
class State
{
public:

	/**
	@brief Create the State.
	
	@param [in,out] manager  - Pointer to the current state manager.
	@param [in,out] platform - Platform containing OS dependent data.
	 */
	State(StateManager* manager, Platform* platform);

	virtual ~State() {}

	/**
	@brief Handles any events such as keyboard/mouse input.
	
	@return true to exit, false to continue.
	 */
	virtual bool eventHandler() = 0;

	/**
	@brief Update any internal values.
	
	@param dt - delta time.
	 */
	virtual void update(float dt) = 0;



	/** @brief Starts loading the state. */
	void startLoading();

	/** @brief Starts unloading the state. */
	void startUnloading();

	/**
	@brief Get this states name
	@return std::string - Name
	*/
	std::string getStateName() { return stateName; }

	/**
	@brief Query if this State is active.
	
	@return true if active, false if not.
	 */
	bool isActive() { return active; }

	/**
	@brief Set the active state to true or false
	@param a Boolean to set active to
	*/
	void setActive(bool a) { active = a; }


	std::vector<Entity*> getRenderables();


	std::vector<Entity*> getHUDElements() { return hudElements;  }

	std::vector<Text*> getStateText();

	Camera* getCamera();


	std::vector<TextModMat*> getTMC();





protected:
	///Pointer to state manager
	StateManager* stateManager;

	/// Platform class containing Window/Renderer and other OS dependent data
	Platform* platform;

	/** @brief Is this state currently active */
	bool active;

	/** @brief Is this state currently loaded */
	bool loaded;

	/**
	@brief Loads this State.
	*/
	virtual void load() = 0;

	/**
	@brief Unloads this State.
	*/
	virtual void unload() = 0;

	///This state's name
	std::string stateName = "";



	std::vector<Entity*> entities;

	std::vector<Entity*> hudElements;


	std::vector<Text*> stateText;
	Camera *camera;




	std::vector<TextModMat*>  tmc;
};