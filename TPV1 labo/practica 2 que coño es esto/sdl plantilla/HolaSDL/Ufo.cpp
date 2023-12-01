#include "Ufo.h"
#include "Game.h"

void Ufo::render() const
{
	// lo mete en el render
	texture->renderFrame(destRect, 10, hits);
}

void Ufo::update()
{
	// mueve al laser
	move();

	manageCooldown();

	// actualiza el rect (colisiones)
	updateRect();


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

void Ufo::appear()
{
	if (CDcounter >= cooldown)
	{
		// crea un laser nuevo
		game->showUfo(this->getPosition(), 1);
	}
}

void Ufo::manageCooldown()
{
	// gestion de cooldown
	if (CDcounter >= cooldown) {
		// elige un nuevo cooldown 
		cooldown = game->getRandomRange(minCD, maxCD);

		// reinicia el contador
		CDcounter = 0;
	}
	else
		CDcounter++;

	appear();
}

void Ufo::setCD()
{
	// elige un nuevo cooldown 
	cooldown = game->getRandomRange(minCD, maxCD);

	CDcounter = 0;
}

void Ufo::move()
{
	// mueve al laser
	position.setX(position.getX() - (vel.getX() * 0.2));
}

void Ufo::updateRect()
{
	// posicion               
	destRect.x = position.getX();
	destRect.y = position.getY();
}

void Ufo::save(ostream&) const
{

}