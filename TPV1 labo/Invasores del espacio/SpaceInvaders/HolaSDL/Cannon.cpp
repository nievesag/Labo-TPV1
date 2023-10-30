#include "Cannon.h"

void Cannon::render()
{
	// posicion para el coso 
	SDL_Rect destRect;

	// tamaño
	destRect.w = texture->getFrameWidth();
	destRect.h = texture->getFrameHeight();

	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();

	// lo mete en el render
	texture->render(destRect);
}

void Cannon::update()
{
	// actualiza el movimiento
	movement();
}

void Cannon::handleEvents(SDL_Event event)
{
	// actualiza direccion de movimiento (izq, der, quieto)
	// le dice al update hacia donde moverse

	// escanea y evalua que tecla has tocado
	SDL_Scancode key = event.key.keysym.scancode;

	if (event.type == SDL_KEYDOWN) {
		// movimento a la izq
		if (key == SDL_SCANCODE_A) {
			keyA = true;
		}
		// movimiento a la derecha
		else if (key == SDL_SCANCODE_D) {
			keyD = true;
		}
		else if (key == SDL_SCANCODE_B)
			keyB = true;
	}
	else if (event.type == SDL_KEYUP) {
		// movimento a la izq
		if (key == SDL_SCANCODE_A) {
			keyA = false;
		}
		// movimiento a la derecha
		else if (key == SDL_SCANCODE_D) {
			keyD = false;
		}
		else if (key == SDL_SCANCODE_B)
			keyB = false;
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

	//position = position + (direction * speed);

	position.setX(position.getX() + (direction.getX() * speed));
	position.setY(position.getY() + (direction.getY() * speed));



	// debug (placeholder)
	if (keyB) {

		//std::cout << position.getX() << " " << position.getY() << endl;

		std::cout << direction.getX() << " " << direction.getY() << endl;

		//std::cout << keyA << " " << keyD << endl;


	}
	
}
