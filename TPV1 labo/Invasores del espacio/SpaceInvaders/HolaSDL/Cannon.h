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
	Point2D<double> position;	// posicion actual en Point2D

	int lifes,					// numero de vidas restantes
		laserCoolDown,			// tiempo de recarga del laser
		cdstart = 0;

	// MOVIMIENTO
	Vector2D<double> direction;	// direccion de movimiento
	float speed = 0.05;			// velocidad de movimiento
	// input
	bool keyA = false, keyD = false, keyE = false, keySpace = false;

	// posicion para el coso 
	SDL_Rect destRect;

	// metodos publicos
public:
	// ---- constructura ----
	Cannon(Point2D<double> position, Texture* texture, int lifes, int laserCoolDown,
		Vector2D<double> direction, Game* game)
		// inicializacion de los valores
		: position(position), texture(texture), lifes(lifes), laserCoolDown(laserCoolDown),
		  direction(direction), game(game){}; 

	Cannon(const Cannon& cannon);
	
	// ---- render ----
	// renderiza el estado del jugador
	void render();

	// ---- update ----
	// actualiza el estado del jugador
	// todos los update devuelven un booleano indicando si el objeto sigue vivo o 
	// ha de ser eliminado por Game (que maneja la coleccion de elementos de la escena)
	bool update(bool damage);

	// ---- hit ----
	// recibir daño
	void hit();

	// ---- handleEvent ----
	// para el input (determina estado de movimiento + disparar laser)
	void handleEvents(SDL_Event event);

	// returns position
	Point2D<double> getPosition() { return position; }

	// devuelve el rect del render
	SDL_Rect* getRect() { SDL_Rect* rect = &destRect; return rect; };

	// metodos auxiliares
private:
	// movimiento
	void movement();

	// disparo
	void shoot();
};
#endif // CANNON_H
