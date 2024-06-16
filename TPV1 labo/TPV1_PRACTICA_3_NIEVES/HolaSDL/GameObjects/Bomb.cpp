#include "../checkML.h"
#include "Bomb.h"
#include "../SDLApplication.h"

Bomb::Bomb(char type, Point2D<double> position, int width, int height, int vidas, Texture* texture, PlayState* game)
	: SceneObject(position, width, height, vidas, texture, game), Weapon(type)
{
	// inicializa alive a true al construirse
	alive = true;

	hits = 0;

	vel.setY(-1);

	c = type;
};

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

	// le pregunta si hay alguien a quien dar
	if (playState->damage(destRect, c)) 
	{
		hits++;

		if (hits >= vidas) 
		{
			// le dice al game que ha muerto
			playState->hasDied(sceneanc);
		}
	}
	else if (isOut()) {

		playState->hasDied(sceneanc);
	}
}

bool Bomb::hit(SDL_Rect* rect, Weapon* frenemy)
{
	return SDL_HasIntersection(rect, &destRect) && (frenemy->getChar() != 'b') && (frenemy->getChar() != 'k');
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