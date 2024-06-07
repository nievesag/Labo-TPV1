#include "../checkML.h"
#include "Bomb.h"
#include "../SDLApplication.h"

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

	// le pregunta si hay alguien a quien pegar un hostion
	if (playState->damage(destRect, c)) {

		hits++;

		if (hits >= vidas) {

			// le dice al game que ha muerto
			playState->hasDied(sceneanc);
		}
	}
	else if (isOut()) {

		playState->hasDied(sceneanc);
	}
}

bool Bomb::hit(SDL_Rect* rect, char frenemy)
{
	return SDL_HasIntersection(rect, &destRect) && (frenemy != 'b');
}

bool Bomb::isOut() const
{
	return (this->position.getY() >= winHeight);
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