#ifndef LASER_H
#define LASER_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"


class Game;

using namespace std;
using uint = unsigned int;

class Laser
{
	// atributos privados
private:
	Vector2D<double> position; 
	Vector2D<double> vel;
	bool frenemy; // laser de alien o de nave
				  // si es del cannon es true, si es del alien es false (basciamente friend or no)
	double speed;
	Game* game;
	int offset = 15;

	SDL_Rect destRect;

	// metodos publicos
public:
	// ---- constructora ----
	Laser(Vector2D<double> position, Vector2D<double> velocity, bool frenemy, Game* game)
		: position(position), vel(velocity), frenemy(frenemy), game(game) {};

	// ---- render ----
	void render();

	// ---- update ----
	//  avanzar con su velocidad y comprobar si ha acertado a algún objetivo
	bool update(bool pum);

	//
	void getPosition();

	//
	bool getFrenemy() { return frenemy; };

	SDL_Rect* getRect() { SDL_Rect* rect = &destRect; return rect; };

protected:
	// mueve el laser segun el vector velocidad
	void move();

	// mira si puede seguir moviendose
	bool cannotMove();

	//
	void killLaser();
};
#endif