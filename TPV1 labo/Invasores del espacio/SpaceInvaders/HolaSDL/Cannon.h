#ifndef CANNON_H
#define CANNON_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Game.h"

using namespace std;
using uint = unsigned int;

class Cannon
{
	// atributos privados
private:
	SDL_Texture* texture = nullptr; // punteron a su textura
	Game* game = nullptr; // puntero al juego -> para lanzar laseres
	Vector2D<int> position(); // posicion actual en Point2D !!!!!!!!!!!!!!!!!!! USAR POINT2D
	int lifes, // numero de vidas restantes
		laserCoolDown; // tiempo de regarga del laser

	// no sé si tiene que ser un enum, es para los eventos -> int?
	enum movState still {}, right{}, left{}; // estados de movimiento

	// metodos publicos
public:
	// ---- constructura ----
	Cannon(Vector2D<int> position, SDL_Texture* texture, int lifes, int laserCoolDown)
		: texture(texture), lifes(lifes), laserCoolDown(laserCoolDown) {}; // falta inicializar la position (estoy en ello je)
	Cannon(const Cannon& cannon);

	// ---- render ----
	// renderiza el estado del jugador
	void render();

	// ---- update ----
	// actualiza el estado del jugador
	void update();

	// ---- hit ----
	// recibir daño
	void hit();

	// ---- handleEvent ----
	// para el input (determina estado de movimiento + disparar laser)
	void handleEvents();
};
#endif // CANNON_H
