#ifndef SHOOTERALIEN_H
#define SHOOTERALIEN_H

#include "Alien.h"
#include <SDL.h>

using namespace std;
using uint = unsigned int;

class ShooterAlien : public Alien
{
	// atributos privados
private:
	// cooldown del disparo
	int cooldown;
	Vector2D<double> position;  // posicion actual en Point2D
	double attackCD,			// cooldown del disparo
		attackCDcounter,		// contador de cooldown del disparo
		minCD, maxCD;		// minimo y maximo cooldown

	// metodos publicos
public:
	// desde esta constructora invocar a la contructora padre (Alien)
	ShooterAlien(int cooldown, double minCD, double maxCD, Mothership* mothership, int type, Point2D<double> position, int width, int height, int vidas, Texture* texture, Game* game)
		: cooldown(cooldown), minCD(minCD), maxCD(maxCD), Alien(mothership, type, position, width, height, vidas, texture, game) { }

	// el alien dispara
	void shoot();

	// gestiona el cooldown de los disparos
	void attack();

	// settea cooldown del alien
	void setAttackCD(double newCD) { attackCD = newCD; }

};
#endif