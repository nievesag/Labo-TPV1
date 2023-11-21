#ifndef SHOOTERALIEN_H
#define SHOOTERALIEN_H

#include "Alien.h"

using namespace std;
using uint = unsigned int;

class ShooterAlien : public Alien
{
	// atributos privados
private:

	// cooldown del disparo
	int cooldown;

	// metodos publicos
public:

	ShooterAlien::ShooterAlien(int cooldown, Point2D<double> position, Texture* texture, int type, Game* game, double minCD, double maxCD)
		: cooldown(cooldown), Alien(position, texture, type, game, minCD, maxCD)
	{
		// ¿?¿?¿?¿?¿?¿?¿?

	}

};
#endif