#include "Cannon.h"

void Cannon::render()
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
	texture->render(destRect);
}

void Cannon::update()
{
	// NO MODIFICAR POSICION SI NO DIRECCION
	// se mueve según su direccion
}

void Cannon::handleEvents(SDL_Event& event)
{
	// actualiza direccion de movimiento (izq, der, quieto)
	// le dice al update hacia donde moverse
}
