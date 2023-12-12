#include "GameState.h"

void GameState::render()
{
}

void GameState::update()
{
}

void GameState::save(ostream& file)
{
}

bool GameState::onEnter()
{
	return false;
}

bool GameState::onExit()
{
	return false;
}

void GameState::handleEvent(const SDL_Event& event)
{
}

void GameState::hasDied(GameList<GameObject, true>::anchor)
{
}

string GameState::getID() const
{
	return " ";
}

void GameState::addEventListener(SDL_Event& event)
{
}

void GameState::addObject(SceneObject& object)
{
}


