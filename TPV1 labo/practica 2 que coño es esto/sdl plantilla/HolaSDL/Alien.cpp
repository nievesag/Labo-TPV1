#include "Alien.h"
#include "Game.h"

void Alien::render() const
{
	// lo mete en el render
	texture->renderFrame(destRect, type, alienFrame);
}

void Alien::update()
{
	if (mothership->shouldMove()) {

		// se mueve
		move();

		// anima
		animate();

		// actualiza el rect (para colisiones)
		updateRect();
	}
}

void Alien::lowerAlien()
{
	// si no se acaba (PLACEHOLDER!!!!!!!!!!!!!!!!!!!!!)
	if (true) {
		// lo baja 
		position.setY(position.getY() + mothership->getLevel());
	}
	else {
		// acaba el juego
		game->EndGame();
	}
}

bool Alien::hit(SDL_Rect* rect, char frenemy)
{
	if (SDL_HasIntersection(rect, &destRect) && frenemy == 'a') {

		// informa al game que ha muerto
		game->hasDied(it);

		game->increaseScore(GetAlienPoints());

		return true;
	}
	else return false;
}



void Alien::move()
{
	// mueve al alien
	position.setX(position.getX() + (mothership->getDirection().getX() * alienSpeed));

	// si se pasa de corto o de largo cambia la direccion y lo baja una posicion
	if (position.getX() < 0 || position.getX() > game->getWinWidth() - texture->getFrameWidth()) {
		mothership->cannotMove();
	}
}

void Alien::animate()
{
	// se anima
	alienFrame = (alienFrame + 1) % 2;
}

void Alien::updateRect()
{
	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();
}

void Alien::save(ostream& out) const
{
	// guarda el indicador de numero
	out << "1 ";

	//  guarda la posicion
	SceneObject::save(out);

	// guarda el subtipo
	out << type << endl;

}