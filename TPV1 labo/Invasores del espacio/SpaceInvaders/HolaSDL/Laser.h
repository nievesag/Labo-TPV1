#ifndef LASER_H
#define LASER_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Game.h"

using namespace std;
using uint = unsigned int;

class Laser
{
	// atributos privados
private:
	Vector2D<int> position; // posicion actual en Point2D !!!!!!!!!!!!!!!!!!! USAR POINT2D
	Vector2D<int> vel;
	bool frenemy; // laser de alien o de nave

	// metodos publicos
public:
	// ---- constructora ----


	// ---- render ----
	void render();

	// ---- update ----
	//  avanzar con su velocidad y comprobar si ha acertado a algún objetivo
	void update();
};

#endif