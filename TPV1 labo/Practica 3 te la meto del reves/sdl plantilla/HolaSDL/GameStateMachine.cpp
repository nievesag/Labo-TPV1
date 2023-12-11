#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* newState)
{
	// añade el estado
	states.push(*newState);

	// activa el onEnter del nuevo estado
	states.top().onEnter();


}

void GameStateMachine::replaceState(GameState* state)
{

	if (!states.empty())
	{
		if (states.top().getStateID() == state->getStateID())
		{
			return; // do nothing
		}
		if (states.top().onExit())
		{
			delete &states.top();
			states.pop();
		}
	}

	// 
	states.push(*state);

	// 
	states.top().onEnter();

}

void GameStateMachine::popState()
{
	// si el stack no esta vacio
	if (!states.empty())
	{
		// si sale
		if (states.top().onExit())
		{
			// borra el puntero
			delete &states.top();

			// lo quita del stack
			states.pop();
		}

}
