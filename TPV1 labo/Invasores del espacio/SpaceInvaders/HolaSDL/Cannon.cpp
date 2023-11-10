#include "Cannon.h"
#include "Game.h"

void Cannon::render()
{

	// tamanio
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();

	// lo mete en el render
	texture->render(destRect);
}

void Cannon::update(bool pum)
{
	// actualiza el movimiento
	movement();

	// dispara
	shoot();
}

void Cannon::handleEvents(SDL_Event event)
{
	// escanea y evalua que tecla has tocado
	SDL_Scancode key = event.key.keysym.scancode;

	if (event.type == SDL_KEYDOWN) {
		// movimento a la izq
		if (key == SDL_SCANCODE_A) keyA = true;

		// movimiento a la derecha
		else if (key == SDL_SCANCODE_D) keyD = true;

		// disparar
		else if (key == SDL_SCANCODE_SPACE) keySpace = true;

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

void Cannon::movement()
{
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
	if (keyE) game->setExit(true);

	// se mueve la nave
	position.setX(position.getX() + (direction.getX() * speed));

	// para que no se pase de largo la nave
	if (position.getX() < 0) 
		position.setX(0);
	else if(position.getX() > game->getWinWidth()-texture->getFrameWidth())
		position.setX(game->getWinWidth() - texture->getFrameWidth());
}

void Cannon::shoot()
{
	int elapsedTime = SDL_GetTicks() - cdstart;

	if (keySpace && elapsedTime >= laserCoolDown) {


		std::cout << elapsedTime << " " << laserCoolDown << endl;
		// firea un laser
		game->fireLaser(true, Vector2D<double>(0, -game->LASER_SPEED));

		// debug
		//std::cout << "COJONEEEEEEEEES" << " ";

		cdstart = SDL_GetTicks(); // resetea el contador del cd al 0 relativo
	}
}
