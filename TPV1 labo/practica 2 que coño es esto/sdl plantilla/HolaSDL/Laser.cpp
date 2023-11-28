#include "Laser.h"

// bestie que es esto ????????? y por que lo arregla todo????? bestie??????
#include "Game.h"

void Laser::render() const
{
	// si es amigo/enemigo pintar de un color u otro
	if (laserType == 'r')
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
	if (game->damage(this) || isOut()) {

		// le dice al game que ha muerto
		game->hasDied(it);
	}
}

bool Laser::hit(SDL_Rect* rect, char frenemy)
{
	// si colisiona con un laser amigo 
	if (SDL_HasIntersection(rect, &destRect) && frenemy != laserType) {

		//cout << "ESTA CHIUS AQUI QUE FUERTE Y SIN BATA" << endl;

		game->hasDied(it);

		return true;
	}
	// si no
	return false;
}

bool Laser::isOut()
{
	return ((this->position.getY() >= winHeight - 10 && 'r')
		|| (this->position.getY() <= 0 + 10 && 'a'));
}

void Laser::move()
{
	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! pasar a variable

	// mueve al laser
	position.setY(position.getY() - (vel.getY()*0.2));
}

void Laser::updateRect()
{
	// posicion               
	destRect.x = position.getX();
	destRect.y = position.getY();
}


