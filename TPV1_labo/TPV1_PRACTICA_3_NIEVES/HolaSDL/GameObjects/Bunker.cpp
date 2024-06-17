#include "../checkML.h"
#include "Bunker.h"
#include "../SDLApplication.h"

void Bunker::render() const
{
	// lo mete en el render
	texture->renderFrame(destRect, 0, hits);
}

void Bunker::save(ostream& out) const
{
	// guarda el indicador de numero
	out << "4 ";

	// guarda la posicion
	SceneObject::save(out);

	// guarda las vidas y golpes recibidos (es que lo hacemos por hits por comodidad)
	out << vidas << " " << hits << endl;
}

void Bunker::update()
{
	updateRect();
}

bool Bunker::hit(SDL_Rect* rect, Weapon* frenemy)
{	
	if (SDL_HasIntersection(rect, &destRect)) 
	{
		if(frenemy->getChar() == 'b' || frenemy->getChar() == 'k')
		{
			hits = hits + 2;
		}
		else
		{
			hits++;
		}

		if (hits >= vidas) playState->hasDied(sceneanc);

		return true;
	}
	// si no
	return false;
}

void Bunker::updateRect()
{
	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();
}