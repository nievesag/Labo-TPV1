#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

// includes
//
#include<SDL.h>

// 
#include "GameState.h"

using namespace std;
using uint = unsigned int;

class GameStateMachine {

protected:

	// stack

public:

	// empuja un estado a la pila
	void pushState(GameState* state) const;

	// saca el estado mas reciente de la pila
	void popState();

	// intercambia el estado por el marcado
	void replaceState(GameState* state);

	//
	void update();

	// renderiza 
	void render() const;

	// 
	void handleEvent(const SDL_Event& event);





};

#endif