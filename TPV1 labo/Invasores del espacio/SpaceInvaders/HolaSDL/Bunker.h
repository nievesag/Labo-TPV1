#ifndef BUNKER_H
#define BUNKER_H

#include "checkML.h"
#include <SDL.h>
#include "texture.h"
#include "Vector2D.h"

// para evitar la inclusión cruzada
// estableces la existencia de la clase porque solo se va a usar a través de un puntero
class Game;

using namespace std;
using uint = unsigned int;

class Bunker
{
	// atributos privados
private:
	Vector2D<double> position; // posicion actual en Point2D
	int lifes; // vidas restantes
	Texture* texture = nullptr; // punteron a su textura

	// metodos publicos
public:
	// ---- constructora ----
	Bunker(Point2D<double> position, Texture* texture, int lifes)
		// inicializacion de los valores
		: position(position), texture(texture), lifes(lifes){}; 

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