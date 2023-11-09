#ifndef ALIEN_H
#define ALIEN_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"

// para evitar la inclusión cruzada
// estableces la existencia de la clase porque solo se va a usar a través de un puntero
class Game ;

using namespace std;
using uint = unsigned int;

class Alien
{
	// atributos privados
private:
	Vector2D<double> position; // posicion actual en Point2D
	int type;
	double speed = 0.01;
	Texture* texture = nullptr; // punteron a su textura
	Game* game = nullptr; // puntero al juego -> para saber la dir común de movimiento de ese tipo de aliens
						  // + informar de que ya no se puede desplazar en ella
	double alienOffSet = 10;

	// metodos publicos 
public:
	// ---- constructora ----
	Alien(Point2D<double> position, Texture* texture, int type, Game* game)
		: position(position), texture(texture), type(type), game(game) {};

	Alien(const Alien& oldalien);

	// ---- destructora ----
	Alien::~Alien();

	// ---- render ----
	void render();

	// ---- update ----
	// movimiento, disparar aleatoriamente después del cooldown 
	// return false -> el alien ha sido dañado
	void update(bool pum);

	// ---- hit ----
	// recibir daño
	void hit();

	// ---- move ----
	// mueve al alien
	void move();

	// baja al alien 1
	void lowerAlien();
};

#endif