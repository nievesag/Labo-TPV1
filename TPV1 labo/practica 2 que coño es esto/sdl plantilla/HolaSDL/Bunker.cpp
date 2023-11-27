#include "Bunker.h"

void Bunker::render() const
{
	SDL_Rect destRect;

	// tamanio
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();

	// lo mete en el render
	texture->renderFrame(destRect, 0, hits);
}

void Bunker::update()
{
	// update
}

bool Bunker::hit(SDL_Rect* rect, char frenemy)
{
	return false;
}
