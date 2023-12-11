#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"

class SDLApplication;

using namespace std;
using uint = unsigned int;

class GameObject
{
	// atributos protegidos
protected:

	// puntero al game
	SDLApplication* application;

	// metodos publicos
public:

	GameObject::GameObject () {}

	GameObject::GameObject(SDLApplication* application)
		: application(application) {}

	// destructora virtual para por polimorfismo
	virtual GameObject::~GameObject();

	// metodos virtuales puros -> estan vacios y preparados para un override en los objetos especificos
	// ---- render ----
	virtual void render() const;

	// ---- update ----
	// actualiza
	virtual void update();

	// ---- save del objeto ----
	virtual void save(ostream& out) const = 0;
};
#endif