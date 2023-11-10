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
	move();

	return alive;
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
	position.setY(position.getY() + alienOffSet);
}