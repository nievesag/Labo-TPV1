#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "GameObject.h"
#include "Vector2D.h"

using namespace std;
using uint = unsigned int;

class SceneObject 
{
	// atributos privados
private:

	// posicion del objeto
	Point2D<double> position;

	// dimension del objeto (height & width)
	//Vector2D<double> dimension;
	int width, height;

	// vidas del objeto
	int vidas;


	// metodos publicos
public:

	SceneObject::SceneObject(Point2D<double> position, int width, int height, int vidas) 
		: position(position), width(width), height(height), vidas(vidas)
	{
		// ????
	}

	// ataque al objeto (basicamente colisiones)
	virtual void hit(SDL_Rect ataque, bool frenemy);

	// iterador de objetos (que cojones es esto)
	//iterator lisObjects;

};

#endif