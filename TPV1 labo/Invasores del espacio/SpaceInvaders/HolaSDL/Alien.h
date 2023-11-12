#ifndef ALIEN_H
#define ALIEN_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"

// para evitar la inclusión cruzada
// estableces la existencia de la clase porque solo se va a usar a través de un puntero
class Game ;

using namespace std;
using uint = unsigned int;

class Alien
{
	// atributos privados
private:
	Vector2D<double> position;  // posicion actual en Point2D
	int type;
	double speed = 0.01;
	bool alive;
	Texture* texture = nullptr; // punteron a su textura
	Game* game = nullptr;		// puntero al juego -> para saber la dir común de movimiento de ese tipo de aliens
								// + informar de que ya no se puede desplazar en ella

	double alienOffSet = 10;

	double attackCD,
		   attackCDcounter,		// cooldown del disparo
		   minCD, maxCD,
			extraSpeed;

	// rectangulo del render
	SDL_Rect destRect;

	// metodos publicos
public:
	// ---- constructora ----
	Alien(Point2D<double> position, Texture* texture, int type, Game* game, double minCD, double maxCD)
		: position(position), texture(texture), type(type), game(game), minCD(minCD), maxCD(maxCD)
	{
		alive = true; 
		extraSpeed = 0;
	};

	Alien(const Alien& oldalien);

	// ---- destructora ----
	Alien::~Alien();

	// ---- render ----
	void render();

	// ---- update ----
	// movimiento, disparar aleatoriamente después del cooldown 
	// return false -> el alien ha sido dañado
	bool update(bool pum);

	// ---- hit ----
	// recibir daño
	void hit();

	// ---- move ----
	// mueve al alien
	void move();

	// baja al alien 1
	void lowerAlien();

	// el alien dispara
	void shoot();

	// gestiona el cooldown de los disparos
	void attack();

	// dice si ha llegado al final de la linea 
	bool checkEnd();

	// devuelve el rect 
	SDL_Rect* getRect() { SDL_Rect* rect = &destRect; return rect; };

	Point2D<double> getPosition() { return position; }

	void setAttackCD(double newCD) { attackCD = newCD; }
};

#endif