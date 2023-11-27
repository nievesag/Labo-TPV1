#include "Laser.h"

void Laser::render() const
{
	
	// si es amigo/enemigo pintar de un color u otro
	if (laserType == rojo)
		SDL_SetRenderDrawColor(game->getRenderer(), 255, 0, 114, 255);	// cannon
	else
		SDL_SetRenderDrawColor(game->getRenderer(), 255, 242, 0, 255);	// aliens


	// dibuja el rectangulo
	SDL_RenderFillRect(game->getRenderer(), &destRect);
}

void Laser::update()
{
	// mueve al laser
	move();

	// actualiza el rect (colisiones)
	updateRect();

	// le pregunta si hay alguien a quien pegar un hostion
	game->damage(this);

}

bool Laser::hit(SDL_Rect* rect, char frenemy)
{
	// si colisiona con un laser amigo 
	if (SDL_HasIntersection(rect, &destRect) && frenemy) {

		cout << "OUCHIEEEEE " << endl;

		return true;
	}
	// si no
	else return false;
}

void Laser::move()
{
	// mueve al laser
	position = position - vel;
}

void Laser::updateRect()
{
	// posicion                  offset !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	destRect.x = position.getX() + 10;
	destRect.y = position.getY();
}


