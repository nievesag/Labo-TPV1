#ifndef LASER_H
#define LASER_H

#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "GameObject.h"

using namespace std;
using uint = unsigned int;

class Laser : SceneObject
{
	// rojo si viene de la nave
	// azul si viene de los aliens
	enum { rojo, azul };

	// atributos privados
private:

	// ---- constructora ----
	Laser(int lifes, int hits, Point2D<double> position, int typeObj, int width, int height, int vidas, Texture* texture, Game* game)
		: SceneObject(position, typeObj, width, height, vidas, texture, game) { };

	// metodos publicos 
public:


};

#endif