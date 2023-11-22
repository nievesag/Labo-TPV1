#include "Cannon.h"

void Cannon::handleEvent(SDL_Event event)
{

	// escanea y evalua que tecla has tocado
	SDL_Scancode key = event.key.keysym.scancode;

	if (event.type == SDL_KEYDOWN) {
		// movimento a la izq
		if (key == SDL_SCANCODE_A) keyA = true;

		// movimiento a la derecha
		else if (key == SDL_SCANCODE_D) keyD = true;

		// disparar
		else if (key == SDL_SCANCODE_SPACE) keySpace = true;

		// salir del juego
		else if (key == SDL_SCANCODE_B) keyE = true;
	}

	else if (event.type == SDL_KEYUP) {
		// movimento a la izq
		if (key == SDL_SCANCODE_A) keyA = false;

		// movimiento a la derecha
		else if (key == SDL_SCANCODE_D) keyD = false;

		// disparar
		else if (key == SDL_SCANCODE_SPACE) keySpace = false;

		// salir del juego
		else if (key == SDL_SCANCODE_E) keyE = false;
	}

}
