#include "GameStateMachine.h"

GameStateMachine::~GameStateMachine()
{
	// mientras la pila de estados no este vacia elimina el estado superior de la pila
	while (!states.empty()) { popState(); }

	// elimina cada elemento de la lista de estados a eliminar
	for (const auto i : statesToDelete) { delete i; }
}

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
			// lo mete en la lista de estados a borrar
			statesToDelete.push_back(states.top());

			// lo quita del stack
			states.pop();
		}
	}
}

void GameStateMachine::replaceState(GameState* state)
{
	if (!states.empty())
	{
		if (states.top()->getID() == state->getID())
		{
			return; // no hace nada
		}
		if (states.top()->onExit())
		{
			// lo mete en la lista de estados a borrar
			statesToDelete.push_back(states.top());

			// lo quita del stack
			states.pop();
		}
	}
	pushState(state);
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
		states.top()->HandleEvent(event);
	}

	// borra los estados a borrar
	while (!statesToDelete.empty()) {
		
		delete statesToDelete.front();

		statesToDelete.pop_front();
	}
}