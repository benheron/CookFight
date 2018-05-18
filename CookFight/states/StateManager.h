#include "State.h"
#include <vector>
#include "../Keyboard.h"

#pragma once

/**
@class StateManager
@brief Manages the creation, switching and function forwarding for States
*/
class StateManager
{
public:

	/**
	@brief Create the State Manager.
	 */
	StateManager();

	~StateManager();

	/**
	@brief Add a new state on top of the previous state.
	
	@param [in,out] state - The new state.
	*/
	void addState(State* state);


	/**
	@brief Add an existing state on top of the previous state.

	@param [in,out] state - The new state.
	*/
	void addExistingState(State* state);

	/**
	@brief Resets the Timer class otherwise conflicts happen
	*/
	void prepareToChangeState();

	/**
	@brief Change to a new state while deleting all previous states.
	
	@param [in,out] state - The new State.
	*/
	void changeState(State* state);

	/**
	@brief Deletes the most recent state 
	*/
	void popLastState();


	/**
	@brief Removes the most recent state without deleting it
	*/
	void popLastStateWithoutDelete();

	//Pass through functions that call the states internal functions

	/**
	@brief Calls the event handler in the current state.
	
	@return true to exit, false to continue.
	*/
	bool eventHandler();

	/**
	@brief Calls the update in the current state.
	
	@param dt - delta time.
	*/
	void update(float dt);




	std::vector<State*> getStates();

private:
	/**
	@brief Deletes all currently loaded states
	*/
	void clearStates();

	///All the currently loaded states
	std::vector<State*> states;




};