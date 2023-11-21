#ifndef ALIEN_H
#define ALIEN_H

#include "checkML.h"
#include <SDL.h>
//#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "GameObject.h"


class Mothership;
class Game;

using namespace std;
using uint = unsigned int;

class Alien : public SceneObject
{
	// atributos privados
private:
	Mothership* mothership;	  // puntero a mothership

	/*
	
	
	//Point2D<double> position;  // posicion actual en Point2D
	int type;
	//double speed = 0.01;
	//bool alive;
	//Texture* texture = nullptr; // punteron a su textura
	//Game* game = nullptr;		// puntero al juego -> para saber la dir común de movimiento de ese tipo de aliens
	// + informar de que ya no se puede desplazar en ella

	//double alienOffSet = 10;
	//int alienFrame;

	//int alienPoints;

	//double extraSpeed; // velocidad añadida

	// rectangulo del render
	//SDL_Rect destRect;
	*/

	int type;



	// metodos publicos 
public:
	// ---- constructora ----

	//Alien() {}

	Alien(int type, Point2D<double> position, int width, int height, int vidas, Texture* texture, Game* game)
		: type(type), SceneObject(position, width, height, vidas, texture, game) { }


};
#endif