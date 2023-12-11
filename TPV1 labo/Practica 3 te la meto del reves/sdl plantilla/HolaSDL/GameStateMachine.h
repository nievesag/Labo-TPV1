#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

// includes
//
#include<SDL.h>		// SDL
#include<stack>	// stack

// 
#include "GameState.h"

using namespace std;
using uint = unsigned int;

class GameStateMachine {

protected:

	// stack de estados:
	//		Cada vez que se cambie de estado se anyadira a la pila para mantener
	// un especie de 'historial' de estados donde siempre se pueda volver al
	// anterior con solo mirar a la pila.
	// 
	// Todos los metodos se ocupan de gestionar la pila 
	stack<GameState> states;


public:

	GameStateMachine() {

	}

	// empuja un estado a la pila
	void pushState(GameState* newState);

	// saca el estado mas reciente de la pila
	void popState();

	// intercambia el estado por el marcado, elimina el estado en la cima y anyade otro
	void replaceState(GameState* state);

	//
	void update();

	// renderiza 
	void render() const;

	// 
	void handleEvent(const SDL_Event& event);





};

#endif