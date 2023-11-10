#ifndef ALIEN_H
#define ALIEN_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"

// para evitar la inclusi�n cruzada
// estableces la existencia de la clase porque solo se va a usar a trav�s de un puntero
class Game ;

using namespace std;
using uint = unsigned int;

class Alien
{
	// atributos privados
private:
	Vector2D<double> position; // posicion actual en Point2D
	int type;
	double speed = 0.01;
	bool alive;
	Texture* texture = nullptr; // punteron a su textura
	Game* game = nullptr; // puntero al juego -> para saber la dir com�n de movimiento de ese tipo de aliens
						  // + informar de que ya no se puede desplazar en ella
	double alienOffSet = 10;

	// rectangulo del render
	SDL_Rect destRect;

	// metodos publicos 
public:
	// ---- constructora ----
	Alien(Point2D<double> position, Texture* texture, int type, Game* game)
		: position(position), texture(texture), type(type), game(game) { alive = true; };

	Alien(const Alien& oldalien);

	// ---- destructora ----
	Alien::~Alien();

	// ---- render ----
	void render();

	// ---- update ----
	// movimiento, disparar aleatoriamente despu�s del cooldown 
	// return false -> el alien ha sido da�ado
	bool update(bool pum);

	// ---- hit ----
	// recibir da�o
	void hit();

	// ---- move ----
	// mueve al alien
	void move();

	// baja al alien 1
	void lowerAlien();


	// devuelve el rect 
	SDL_Rect* getRect() { SDL_Rect* rect = &destRect; return rect; };


};

#endif