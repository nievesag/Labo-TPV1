#include "Bomb.h"
#include "SDLApplication.h"

void Bomb::render() const
{
	// lo mete en el render
	texture->render(destRect);
}

void Bomb::update()
{
	// mueve al laser
	move();

	// actualiza el rect (colisiones)
	updateRect();
}

bool Bomb::hit(SDL_Rect* rect, char frenemy)
{
	// mira la interseccion
	if (SDL_HasIntersection(rect, &destRect) && frenemy == 'r') {

		// suma golpes
		hits++;

		// si tiene mas golpes que vidas le dice que ha muerto
		if (hits >= vidas) playState->hasDied(sceneanc);

		return true;
	}
	else return false;
}

bool Bomb::isOut()
{
	return ((this->position.getY() >= winHeight)
		|| (this->position.getY() <= 0));
}

void Bomb::move()
{
	// mueve la BOMBA
	position.setY(position.getY() - (vel.getY() * BOMBA_SPEED));
}

void Bomb::updateRect()
{
	// posicion               
	destRect.x = position.getX();
	destRect.y = position.getY();
}
