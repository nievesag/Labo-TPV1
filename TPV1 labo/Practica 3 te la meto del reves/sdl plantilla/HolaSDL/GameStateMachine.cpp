#include "GameStateMachine.h"

void GameStateMachine::pushState(GameState* newState)
{
	// ESTO ES QUITANDO EL CONST DEL METODO :(

	// crea una copia del estado
	GameState state = *newState;

	// anyade el estado idicado
	states.push(state);

}

void GameStateMachine::popState()
{
	// quita el estado de arriba
	states.pop();
}

void GameStateMachine::replaceState(GameState* state)
{
	// que cojones quiere

}

void GameStateMachine::update()
{
	// 

}

void GameStateMachine::render() const
{
	//

}

void GameStateMachine::handleEvent(const SDL_Event& event)
{
	//

}
