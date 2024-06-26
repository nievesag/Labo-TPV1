#ifndef SHOOTERALIEN_H
#define SHOOTERALIEN_H

#include "Alien.h"

class Mothership;

class ShooterAlien : public Alien
{
	// atributos privados
private:
	// cooldown del disparo
	double cooldown,		// cooldown del disparo
			CDcounter = 0,		// contador de cooldown del disparo
			minCD = 10, 
			maxCD = 20;	// minimo y maximo cooldown

	// metodos publicos
public:
	// desde esta constructora invocar a la contructora padre (Alien)
	ShooterAlien(double cooldown, Mothership* mothership, int alienFrame, int type, Point2D<double> position,
		int width, int height, int vidas, Texture* texture, PlayState* game);
		
	// el alien dispara
	void shoot();

	// gestiona el cooldown de los disparos
	void manageCooldown();

	// settea cooldown del alien
	void setAttackCD(double newCD) { cooldown = newCD; }

	void setCD();

	void update() override;

	void save(std::ostream& out) const override;
};
#endif