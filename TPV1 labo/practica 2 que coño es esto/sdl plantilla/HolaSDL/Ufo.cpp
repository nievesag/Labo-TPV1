#include "Ufo.h"
#include "Game.h"

void Ufo::render() const
{
	// lo mete en el render
	texture->renderFrame(destRect, 10, hits);
}

void Ufo::update()
{

}

void Ufo::updateState()
{

}

bool Ufo::hit(SDL_Rect* rect, char frenemy)
{
	if (SDL_HasIntersection(rect, &destRect) && frenemy) {

		hits++;

		if (hits >= vidas) game->hasDied(it);

		return true;
	}
	// si no
	return false;
}

void Ufo::move()
{

}
