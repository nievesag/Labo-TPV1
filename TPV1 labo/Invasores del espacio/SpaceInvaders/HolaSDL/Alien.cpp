#include "Alien.h"
#include "Game.h"

void Alien::render()
{
	// posicion para el coso 
	SDL_Rect destRect;

	// tamaño
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();

	// lo mete en el render
	texture->renderFrame(destRect, type, 0);
}


void Alien::update(bool pum)
{
	//
	move();

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
