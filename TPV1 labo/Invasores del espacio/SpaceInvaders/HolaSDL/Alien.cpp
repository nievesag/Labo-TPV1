#include "Alien.h"
#include "Game.h"

Alien::~Alien()
{
	// destruye cosas
}

void Alien::render()
{
	// posicion para el coso 
	

	// tamaño
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();

	// lo mete en el render
	texture->renderFrame(destRect, type, 0);
}

bool Alien::update(bool pum)
{
	// si esta muerto devuelve false
	if (!alive) return false;

	// se mueve
	move();

	// gestiona los disparos
	attack();

	// si esta vivo devuelve true
	return true;
}


void Alien::hit() {

	// lo mata oops
	alive = false;

}

void Alien::move()
{
	// mueve al alien
	position.setX(position.getX() + (game->getDirection() * speed));

	// si se pasa de corto o de largo cambia la direccion y lo baja una posicion
	if (position.getX() < 0 || position.getX() > game->getWinWidth() - texture->getFrameWidth()) {
		game->cannotMove();
	}
}

void Alien::lowerAlien()
{
	// lo baja 
	position.setY(position.getY() + alienOffSet);
}


void Alien::shoot() 
{
	//	
	if (attackCDcounter >= attackCD) {

		// crea un laser nuevo
		game->fireLaser(this->getPosition(), Vector2D<double>(0, LASER_SPEED), false);
	}

	
}

void Alien::attack()
{
	// si es del tipo de alien que dispara
	if (type == 0) {

		// gestion de cooldown
		if (attackCDcounter >= attackCD) {

			// elige un nuevo cooldown 
			attackCD = game->getRandomRange(1500, 2000);

			// reinicia el contador
			attackCDcounter = 0;


		}
		else 
			attackCDcounter++;



		shoot();
	}

}
