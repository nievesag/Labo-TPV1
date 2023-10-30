#ifndef CANNON_H
#define CANNON_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"

// es una promesa de la existencia de la clase game
// para evitar inclusiones cruzadas
class Game;

using namespace std;
using uint = unsigned int;

class Cannon
{
	// atributos privados
private:
	Texture* texture = nullptr;	// punteron a su textura
	Game* game = nullptr;		// puntero al juego -> para lanzar laseres
	Point2D<> position;		// posicion actual en Point2D

	int lifes,					// numero de vidas restantes
		laserCoolDown;			// tiempo de regarga del laser

	// MOVIMIENTO
	Vector2D<> direction;	// direccion de movimiento
	float speed = 5;			// velocidad de movimiento
	bool keyA, keyD;			// tecla pulsada A o D !!!!! añadir espacio para el disparo?

	// metodos publicos
public:
	// ---- constructura ----
	Cannon(Point2D<> position, Texture* texture, int lifes, int laserCoolDown, 
		Vector2D<> direction, Game* game)
		// inicializacion de los valores
		: position(position), texture(texture), lifes(lifes), laserCoolDown(laserCoolDown), 
		  direction(0,0), game(game){}; 

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
	void handleEvents(SDL_Event event);

	// metodos auxiliares
private:
	void movement();
};
#endif // CANNON_H
