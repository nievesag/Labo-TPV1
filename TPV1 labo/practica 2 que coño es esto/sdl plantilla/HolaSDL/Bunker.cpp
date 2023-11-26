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

	// así no se recorta
	// texture->render(destRect);
}

bool Bunker::update()
{
	// si esta muerto devuelve false
	if (hits == lifes) return false;

	// si esta vivo devuelve true
    return true;
}
