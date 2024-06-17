#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

#include <SDL.h>	
#include <string>
#include <stack>	// stack

#include "GameState.h"

class GameStateMachine {

protected:
	// STACK DE ESTADOS:
	// Cada vez que se cambie de estado se anyadira a la pila para mantener
	// un especie de 'historial' de estados donde siempre se pueda volver al
	// anterior con solo mirar a la pila.

	// Pila de estados
	std::stack<GameState*> states; // Todos los metodos se ocupan de gestionar la pila 

	// Lista de estados a eliminar
	std::list<GameState*> statesToDelete;

public:
	GameStateMachine() {}

	~GameStateMachine();

	// empuja un estado a la pila
	void pushState(GameState* newState);

	// saca el estado mas reciente de la pila
	void popState();

	// intercambia el estado por el marcado, elimina el estado en la cima y anyade otro
	void replaceState(GameState* state);

	// actualiza
	void update();

	// renderiza 
	void render();

	// maneja eventos
	void handleEvent(const SDL_Event& event);
};
#endif