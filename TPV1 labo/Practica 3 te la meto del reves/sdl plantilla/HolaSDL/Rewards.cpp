#include "Rewards.h"
#include "SDLApplication.h"

void Rewards::render() const
{

}

void Rewards::update()
{
	// mueve al laser
	move();

	// actualiza el rect (colisiones)
	updateRect();

	// le pregunta si hay alguien a quien pegar un hostion
	if (playState->damage(destRect, 'r') || isOut()) {

		// le dice al game que ha muerto
		playState->hasDied(sceneanc);
	}
}

bool Rewards::obtain(SDL_Rect* rect, char frenemy)
{
	// WIP
	return (SDL_HasIntersection(rect, &destRect));
}

bool Rewards::isOut()
{
	return (this->position.getY() >= winHeight);
}

void Rewards::move()
{
	// mueve la reward
	position.setY(position.getY() - (vel.getY() * REWARD_SPEED));
}

void Rewards::updateRect()
{
	// posicion               
	destRect.x = position.getX();
	destRect.y = position.getY();
}