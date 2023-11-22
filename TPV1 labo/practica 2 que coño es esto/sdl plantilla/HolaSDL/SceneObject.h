#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"

using namespace std;
using uint = unsigned int;

class SceneObject : GameObject
{
	// atributos privados
protected:

	// posicion del objeto
	Point2D<int> position;

	// dimension del objeto (height & width)
	int width, height;

	// vidas del objeto
	int vidas;

	Texture* texture;

	// rectangulo del render
	SDL_Rect destRect;

	// metodos publicos
public:

	SceneObject::SceneObject(Point2D<int> position, int width, int height, int vidas, Texture* texture, Game* game)
		: position(position), width(width), height(height), vidas(vidas), texture(texture), GameObject(game)
	{
		// ????
	}


	// -------------> los override van en las clases hijas que lo especifiquen <-------------------------
	// (en alien, cannon etc)
	/*
	// virtual para que lo usen los hijos, const porque el ordiginal es const (y no es un metodo que cambie datos)
	//
	virtual void render() const override;

	//
	virtual void update() override;

	//
	virtual void save(ostream&) const override;
	*/
	



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