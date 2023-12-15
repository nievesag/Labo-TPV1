#include "GameState.h"

void GameState::render() const
{
	for (SceneObject& objects : gamelist) {
		objects.render();
	}
}

void GameState::update()
{
	for (SceneObject& objects : gamelist) {
		objects.update();
	}
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
	for (EventHandler*& listener : eventListeners)
		listener->handleEvent(event);
}

void GameState::hasDied(GameList<GameObject, true>::anchor)
{

}

string GameState::getID() const { return " "; }

void GameState::addEventListener(EventHandler* listener)
{
	eventListeners.push_back(listener);
}

void GameState::addObject(SceneObject* object)
{
	gamelist.push_back(object);
}