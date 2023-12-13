#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* newState)
{
	// anyade el estado
	states.push(newState);

	// activa el onEnter del nuevo estado
	states.top()->onEnter();
}

void GameStateMachine::popState()
{
	// si el stack no esta vacio
	if (!states.empty())
	{
		// si sale
		if (states.top()->onExit())
		{
			// borra el puntero
			delete states.top();

			// lo quita del stack
			states.pop();
		}
	}
}

void GameStateMachine::replaceState(GameState* state)
{
	if (!states.empty())
	{
		if (states.top()->getID()  == state->getID())
		{
			return; // no hace nada
		}
		if (states.top()->onExit())
		{
			// lo mismo que en popState
			delete states.top();
			states.pop();
		}
	}


	// esto es push state asi queeee
	pushState(state);
	/*
	// 
	states.push(*state);

	// 
	states.top().onEnter();
	*/
}

void GameStateMachine::update()
{
	// si no esta vacia la pila actualiza el ultimo estado
	if (!states.empty())
	{
		states.top()->update();
	}
}

void GameStateMachine::render()
{
	// si no esta vacia la pila renderiza el ultimo estado
	if (!states.empty())
	{
		states.top()->render();
	}
}

void GameStateMachine::handleEvent(const SDL_Event& event)
{
	// si no esta vacia la pila renderiza el ultimo estado
	if (!states.empty())
	{
		states.top()->handleEvent(event);
	}
}

