#include "ScrollingState.h"

ScrollingState::ScrollingState(SDLApplication* game, Texture* texture, GameState* next) :
			GameState(game)
{

}

void ScrollingState::render() const
{
	application->getTexture(YouWon)->render();
}

bool ScrollingState::onEnter() const
{
	return false;
}

bool ScrollingState::onExit() const
{
	return false;
}

std::string ScrollingState::getID() const
{
	return std::string();
}


