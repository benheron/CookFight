#include "StateManager.h"
#include "State.h"


StateManager::StateManager()
{

}

StateManager::~StateManager()
{
	clearStates();
}

void StateManager::clearStates()
{
	for (auto s : states)
	{
		s->startUnloading();
		delete s;
	}
	states.clear();
}

void StateManager::addState(State* state)
{
	states.push_back(state);
	
	state->startLoading();
	
}

void StateManager::addExistingState(State* state)
{
	states.push_back(state);

	state->setActive(true);
	//state->startLoading();

}



void StateManager::prepareToChangeState()
{
	//Stop Music and Clear the timers
	
}

void StateManager::changeState(State* state)
{
	clearStates();
	addState(state);
}

void StateManager::popLastState()
{
	states.back()->startUnloading();
	delete states.back();
	states.pop_back();
	states.back()->setActive(true);
}


void StateManager::popLastStateWithoutDelete()
{
	states.back()->startUnloading();
	states.pop_back();
	states.back()->setActive(true);
}

bool StateManager::eventHandler()
{
/*
	//Handle events on queue
	while (SDL_PollEvent(&e))
	{
		//User requests quit
		switch (e.type)
		{
		case SDL_QUIT:
			
			break;

		case SDL_KEYDOWN:
			keyHandler(e, true);
			break;
		case SDL_KEYUP:
			keyHandler(e, false);
			break;
		}
	}*/






	if (!states.empty() && states.back() != nullptr && states.back()->isActive())
	{
		return states.back()->eventHandler();
	}
	else
	{
		return false;
	}
}

void StateManager::update(float dt)
{
	if (!states.empty() && states.back() != nullptr && states.back()->isActive())
		states.back()->update(dt);
}


std::vector<State*> StateManager::getStates()
{
	return states;
}





