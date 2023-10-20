#ifndef ALIEN_H
#define ALIEN_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Game.h"

using namespace std;
using uint = unsigned int;

class Alien
{
	// atributos privados
private:
	Vector2D<int> position; // posicion actual en Point2D !!!!!!!!!!!!!!!!!!! USAR POINT2D
	int type;
	SDL_Texture* texture = nullptr; // punteron a su textura
	Game* game = nullptr; // puntero al juego -> para saber la dir com�n de movimiento de ese tipo de aliens
						  // + informar de que ya no se puede desplazar en ella

	// metodos publicos
public:
	// ---- constructora ----


	// ---- render ----
	void render();

	// ---- update ----
	// movimiento, disparar aleatoriamente despu�s del cooldown 
	// return false -> el alien ha sido da�ado
	void update();

	// ---- hit ----
	// recibir da�o
	void hit();
};

#endif