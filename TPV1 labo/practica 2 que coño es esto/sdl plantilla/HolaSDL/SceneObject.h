#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "GameObject.h"
#include "Vector2D.h"

using namespace std;
using uint = unsigned int;

class SceneObject : GameObject
{
	// atributos privados
private:

	// posicion del objeto
	Point2D<double> position;

	// dimension del objeto (height & width)
	int width, height;

	// vidas del objeto
	int vidas;

	// metodos publicos
public:

	SceneObject::SceneObject(Point2D<double> position, int width, int height, int vidas, Game* game) 
		: position(position), width(width), height(height), vidas(vidas), GameObject(game)
	{
		// ????
	}

	// ataque al objeto (basicamente colisiones)
	virtual void hit(SDL_Rect ataque, bool frenemy);

	// iterador de objetos (que cojones es esto)
	// es como los operadores, creo que básicamente 
	// se refiere a definir operadores para leer la 
	// lista de objetos???? 
	// MIRAR LISTA DE GAME -> es lo mismo????
	// iterator listObjects;

};

#endif