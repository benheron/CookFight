#include "State.h"

State::State(StateManager* stateManager, Platform* platform)
	:stateManager(stateManager), platform(platform), active(false)
{
	camera = new Camera();
	loaded = false;
}

State::~State()
{
	for (int i = entities.size() - 1; i > -1; i--)
	{
		delete entities[i];
	}
	entities.clear();


	for (int i = hudElements.size() - 1; i > -1; i--)
	{
		delete hudElements[i];
	}
	delete camera;
	hudElements.clear();
}

void State::startLoading()
{
	active = true;
	if (!loaded)
	{
		load();
		loaded = true;
	}
}

void State::startUnloading()
{
	active = false;
	unload();
}





std::vector<Entity*> State::getRenderables()
{
	return entities;
}

std::vector<Text*> State::getStateText()
{
	return stateText;
}

Camera *State::getCamera()
{
	return camera;
}


std::vector<TextModMat*> State::getTMC()
{
	return tmc;
}