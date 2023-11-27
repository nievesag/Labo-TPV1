#include "Cannon.h"

void Cannon::render() const
{	
	// lo mete en el render
	texture->render(destRect);
}

void Cannon::update()
{
	// actualiza el movimiento
	movement();

	// dispara
	shoot();

	// actualiza el rect
	updateRect();

}

void Cannon::save(ostream&) const
{


}

void Cannon::handleEvent(SDL_Event event)
{
	// escanea y evalua que tecla has tocado
	SDL_Scancode key = event.key.keysym.scancode;

	if (event.type == SDL_KEYDOWN) {
		// movimento a la izq
		if (key == SDL_SCANCODE_A) keyA = true;

		// movimiento a la derecha
		else if (key == SDL_SCANCODE_D) keyD = true;

		// disparar
		else if (key == SDL_SCANCODE_SPACE) {
			cout << "disparo" << endl;  
			keySpace = true;
		}

		// salir del juego
		else if (key == SDL_SCANCODE_B) keyE = true;
	}

	else if (event.type == SDL_KEYUP) {
		// movimento a la izq
		if (key == SDL_SCANCODE_A) keyA = false;

		// movimiento a la derecha
		else if (key == SDL_SCANCODE_D) keyD = false;

		// disparar
		else if (key == SDL_SCANCODE_SPACE) keySpace = false;

		// salir del juego
		else if (key == SDL_SCANCODE_E) keyE = false;
	}
}

bool Cannon::hit(SDL_Rect* rect, char frenemy)
{
	return false;
}

void Cannon::updateRect()
{
	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();
}

void Cannon::movement()
{
	Vector2D<double> direction(0, 0);

	// se queda quieto
	if (keyA == keyD) // si se pulsan 2 teclas a la vez
	{
		direction = Vector2D<double>(0, 0);
	}
	// se mueve
	else if (keyA != keyD) {
		if (keyA) {
			// movimiento a la izq x de direction = -1
			direction = Vector2D<double>(-1, 0);
		}
		else if (keyD) {
			// movimiento a la der x de direction = +1
			direction = Vector2D<double>(1, 0);
		}
	}
	if (keyE) game->EndGame();

	// se mueve la nave
	position.setX(position.getX() + (direction.getX() * CANNON_SPEED));

	// para que no se pase de largo la nave
	if (position.getX() < 0)
		position.setX(0);
	else if (position.getX() > game->getWinWidth() - texture->getFrameWidth())
		position.setX(game->getWinWidth() - texture->getFrameWidth());
}

void Cannon::shoot()
{
	//


}
