#ifndef BUNKER_H
#define BUNKER_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Game.h"

using namespace std;
using uint = unsigned int;

class Bunker
{
	// atributos privados
private:
	Vector2D<int> position; // posicion actual en Point2D !!!!!!!!!!!!!!!!!!! USAR POINT2D
	int lifes; // vidas restantes
	SDL_Texture* texture = nullptr; // punteron a su textura

	// metodos publicos
public:
	// ---- constructora ----


	// ---- render ----
	void render();

	// ---- update ----
	// return false -> 0 vidas -> delete del juego
	void update();

	// ---- hit ----
	// recibir daño -> -1 vida, cambiar textura
	void hit();

};

#endif