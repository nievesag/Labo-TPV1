#include "../checkML.h"
#include "Kamikaze.h"
#include "../SDLApplication.h"

Kamikaze::Kamikaze(char type, Point2D<double> position, int vidas, int width, int height, Texture* texture, PlayState* game) :
		SceneObject(position, width, height, vidas, texture, game), Weapon(type)
{
	vel.setX(0.3);
	vel.setY(0.1);
}

void Kamikaze::render() const
{
	double angle = 180 / (M_PI * (atan(position.getX() / position.getY())));
	texture->render(destRect);
}

void Kamikaze::update()
{
	//cout << position.getY();

	// mueve al kamikaze
	move();

	// actualiza el rect (colisiones)
	updateRect();

	// le pregunta si hay alguien a quien pegar un hostion
	if (playState->damage(destRect, *this) || isOut()) {

		// le dice al game que ha muerto
		playState->hasDied(sceneanc);
	}
}

void Kamikaze::save(std::ostream& out) const
{

}

bool Kamikaze::hit(SDL_Rect* rect, Weapon* frenemy)
{
	if (SDL_HasIntersection(rect, &destRect) && frenemy->getChar() == 'a') {

		// informa al game que ha muerto
		playState->hasDied(sceneanc);

		mothership->alienDied();

		return true;
	}
	else return false;
}

void Kamikaze::move()
{
	cannonPos.setX(playState->getCannonPos().getX());
	cannonPos.setY(playState->getCannonPos().getY());

	dir = 0;

	// para que no se mueva una vez llegue a la altura del cannon
	if (position.getY() <= cannonPos.getY())
	{
		// si estas mas a la izq del cannon -> te mueves a la der
		if(position.getX() < cannonPos.getX())
		{
			dir = 1;
		}

		// si estas mas a la der del cannon -> te mueves a la izq
		else if(position.getX() > cannonPos.getX())
		{
			dir = -1;
		}
	}

	Vector2D<double> aux;
	aux.setX(vel.getX() * dir);
	aux.setY(vel.getY());

	position = position + aux;
}

void Kamikaze::updateRect()
{
	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();
}

bool Kamikaze::isOut() const
{
	return position.getY() >= winHeight + texture->getFrameHeight();
}