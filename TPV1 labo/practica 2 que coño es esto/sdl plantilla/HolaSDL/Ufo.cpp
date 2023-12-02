#include "Ufo.h"
#include "Game.h"

void Ufo::render() const
{
	// lo mete en el render
	texture->renderFrame(destRect, 5, hits);
}

void Ufo::update()
{
	// actualiza el rect (colisiones)
	updateRect();

	if (state != destruido) {

		// mueve al laser
		move();
		manageCooldown();
	}
}

void Ufo::updateRect()
{
	// posicion               
	destRect.x = position.getX();
	destRect.y = position.getY();
}

bool Ufo::hit(SDL_Rect* rect, char frenemy)
{
	if (SDL_HasIntersection(rect, &destRect) && frenemy) {

		hits++;

		if (hits >= vidas) game->hasDied(it);
		state = destruido;
		game->increaseScore(UfoScore);

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
		game->showUfo(spawn);
		state = visible;
	}
	else state = oculto;
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

void Ufo::save(ostream& out) const
{
	// guarda el indicador de numero, la altura, el estado y el cooldown (y los golpes)
	out << "5 "
		<< spawn.getY() << " " 
		<< state << " " 
		<< cooldown << " " 
		<< hits << endl;

}