#include "checkML.h"
#include "Cannon.h"
#include "SDLApplication.h"

Cannon::Cannon(int cooldown, Point2D<double> position, int width, int height, int vidas, Texture* texture, PlayState* game) 
	: cooldown(cooldown), SceneObject(position, width, height, vidas, texture, game) 
{
	currentCD = 0;

	// registra el cannon como oyente de eventos
	// para reaccionar a input de teclado
	playState->addEventListener(this);
}

void Cannon::render() const
{	
	// lo mete en el render
	texture->render(destRect);
}

void Cannon::update()
{
	// actualiza el movimiento
	movement();

	// dispara si puede
	manageCooldown();

	// actualiza el rect
	updateRect();
}

void Cannon::updateRect()
{
	// posicion
	destRect.x = position.getX();
	destRect.y = position.getY();
}

void Cannon::handleEvent(const SDL_Event& event)
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
		else if (key == SDL_SCANCODE_E) keyE = true;
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
	if (SDL_HasIntersection(rect, &destRect) && frenemy == 'r') {
		// informa al game que ha muerto
		playState->hasDied(sceneanc);

		//application->EndGame();

		return true;
	}
	// si no
	return false;
}

void Cannon::manageCooldown()
{
	if (currentCD < cooldown) {
		currentCD++;
	}
	else {

		cout << "???" << endl;
		shoot();
		currentCD = 0;
	}
}

void Cannon::shoot()
{
	if (keySpace) {

		cout << "holi" << endl;
		playState->fireLaser(this->position, 'a');

	}
		
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
	else if (keyA != keyD) // si NO se pulsan 2 teclas a la vez
	{
		if (keyA) {

			// movimiento a la izq x de direction = -1
			direction = Vector2D<double>(-1, 0);
		}
		else if (keyD) {
			// movimiento a la der x de direction = +1
			direction = Vector2D<double>(1, 0);
		}
	}
	if (keyE) playState->EndGame();

	// se mueve la nave
	position.setX(position.getX() + (direction.getX() * CANNON_SPEED));

	// para que no se pase de largo la nave
	if (position.getX() < 0) {
		position.setX(0);
	}	
	else if (position.getX() > application->getWinWidth() - texture->getFrameWidth()) {
		position.setX(application->getWinWidth() - texture->getFrameWidth());
	}
}

void Cannon::save(ostream& out) const
{
	// guarda el indicador de numero
	out << "0 ";

	// guarda la posicion
	SceneObject::save(out);

	// guarda las vidas del cannon y el cooldown del disparo
	out << vidas << " " << cooldown << endl;
}