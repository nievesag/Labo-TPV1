#include "Alien.h"

// bestie got bestied ?????? like what ????????
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

void Alien::save(ostream&) const
{
	cout << "coñardo";
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

		//cout << "bruh" << endl;

		// informa al game que ha muerto
		game->hasDied(it);

		return true;
	}

	// si no
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
	// se anima omg
	alienFrame = (alienFrame + 1) % 2;

}

void Alien::updateRect()
{
	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();

}
