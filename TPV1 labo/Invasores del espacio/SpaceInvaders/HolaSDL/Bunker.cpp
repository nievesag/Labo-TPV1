#include "Bunker.h"

void Bunker::render()
{
	// tamaño
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();

	// lo mete en el render
	texture->renderFrame(destRect, 0, 0);
}

bool Bunker::update()
{
	//if (lifes <= 0) return false;

	return true;
}

void Bunker::hit()
{
	hits++;
}

