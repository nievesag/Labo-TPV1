#ifndef ALIEN_H
#define ALIEN_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"
//#include "Game.h"

// para evitar la inclusión cruzada
// estableces la existencia de la clase porque solo se va a usar a través de un puntero
class Game; 

using namespace std;
using uint = unsigned int;

class Alien
{
	// atributos privados
private:
	Vector2D<int> position; // posicion actual en Point2D !!!!!!!!!!!!!!!!!!! USAR POINT2D
	int type;
	Texture* texture = nullptr; // punteron a su textura
	Game* game = nullptr; // puntero al juego -> para saber la dir común de movimiento de ese tipo de aliens
						  // + informar de que ya no se puede desplazar en ella

	// metodos publicos 
public:
	// ---- constructora ----
	Alien(Point2D<int> position, Texture* texture, int type, Game* game)
		: position(position), texture(texture), type(type), game(game) {};

	Alien(const Alien& oldalien);

	// ---- render ----
	void render();

	// ---- update ----
	// movimiento, disparar aleatoriamente después del cooldown 
	// return false -> el alien ha sido dañado
	void update();

	// ---- hit ----
	// recibir daño
	void hit();
};

#endif