#ifndef CANNON_H
#define CANNON_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
//#include "Game.h"

// es una promesa de la existencia de la clase game
class Game;

using namespace std;
using uint = unsigned int;

class Cannon
{
	// atributos privados
private:
	SDL_Texture* texture = nullptr; // punteron a su textura
	Game* game = nullptr; // puntero al juego -> para lanzar laseres
	Point2D<int> position; // posicion actual en Point2D
	int lifes,				 // numero de vidas restantes
		laserCoolDown;			// tiempo de regarga del laser

	Vector2D<int> direction;

	// metodos publicos
public:
	
	// ---- constructura ----
	Cannon(Point2D<int> position, SDL_Texture* texture, int lifes, int laserCoolDown, Vector2D<int> direction)
		: position(position), texture(texture), lifes(lifes), laserCoolDown(laserCoolDown), direction(direction) {}; // falta inicializar la position (estoy en ello je) !!!!!!!!!
	Cannon(const Cannon& cannon);
	
	// ---- render ----
	// renderiza el estado del jugador
	void render();

	// ---- update ----
	// actualiza el estado del jugador
	void update();

	// ---- hit ----
	// recibir daño
	void hit();

	// ---- handleEvent ----
	// para el input (determina estado de movimiento + disparar laser)
	void handleEvents();
};
#endif // CANNON_H
