#ifndef BUNKER_H
#define BUNKER_H

#include "Vector2D.h"
#include "texture.h"
#include "SceneObject.h"
#include "GameObject.h"

using namespace std;
using uint = unsigned int;

class Bunker : public SceneObject
{
	int lifes,					// vidas restantes
		hits;					// contador de golpes

	// atributos privados
private:
	// ---- constructora ----
	Bunker(int lifes, int hits, Point2D<double> position, int typeObj, int width, int height, int vidas, Texture* texture, Game* game)
		: lifes(lifes), hits(hits), SceneObject(position, typeObj, width, height, vidas, texture, game)
	{
		typeObj = 2;
	};

	// metodos publicos
public:


};

#endif