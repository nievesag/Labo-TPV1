#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "GameObject.h"
#include "Vector2D.h"
#include "texture.h"
#include <list>

using namespace std;
using uint = unsigned int;

class SceneObject : public GameObject
{
	// atributos protegidos
protected:

	// posicion del objeto
	Point2D<double> position;

	// dimension del objeto (height & width)
	int width, height;

	// vidas del objeto
	int vidas;

	Texture* texture;

	// rectangulo del render
	SDL_Rect destRect;

	// iterador de la lista
	list<SceneObject*>::iterator it;

	char frenemy;
	
	// metodos publicos
public:

	SceneObject::SceneObject(SDL_Rect destRect, Point2D<double> position, int width, int height, int vidas, Texture* texture, Game* game)
		: destRect(destRect), position(position), width(width), height(height), vidas(vidas), texture(texture), GameObject(game) { }

	// -------------> los override van en las clases hijas que lo especifiquen <--------------
	// (en alien, cannon, laser, bunker)
	// metodo virtual: para que lo usen los hijos
	// const: porque no es un metodo que cambie datos

	//
	virtual void render() const;

	//
	virtual bool update();

	//
	virtual void save(ostream&) const;

	// ataque al objeto (basicamente colisiones)
	virtual bool hit(SDL_Rect* ataque, char frenemy);

	// devuelve rect (posicion) de cada objeto
	SDL_Rect* getRect() { SDL_Rect* rect = &destRect; return rect; };

	// ----- Iterador de la lista ------
	// Un iterador funciona como un puntero que apunta a los items de la lista 
	// Tipos: begin(), end(), advance(), next(), prev(), inserter()
	void setListIterator(list<SceneObject*>::iterator newit)
	{
		// setea el iterador de la posicion del objeto en la lista
		it = newit;
	};

	Point2D<double> getPosition() const { return position; };

	Texture* getTexture() const { return texture; };

	char getFrenemy() { return frenemy; };
};

#endif