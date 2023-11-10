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