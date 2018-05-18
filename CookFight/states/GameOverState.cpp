#include "GameOverState.h"




GameOverState::GameOverState(StateManager* manager, Platform *platform, ResourceManager* rm)
	: State(manager, platform), rm(rm)
{

}

GameOverState::~GameOverState()
{

}

bool GameOverState::eventHandler()
{
	return false;
}

void GameOverState::update(float dt)
{
	
}

void GameOverState::load()
{
	
	
}

void GameOverState::unload()
{
	
}