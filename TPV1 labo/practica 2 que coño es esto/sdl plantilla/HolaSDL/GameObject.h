#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"

class Game;

using namespace std;
using uint = unsigned int;

class GameObject
{
	// atributos privados
private:

	// puntero al game
	Game* game;

	// metodos publicos
public:

	GameObject::GameObject(Game* game)
		: game(game)
	{
		// ??????????????????
	}

	// destructora virtual para por polimorfismo
	virtual GameObject::~GameObject();

	// metodos virtuales puros AKA estan vacios y preparados para un override en los objetos especificos

	// render
	virtual void render() const;

	// update
	virtual void update();

	// save del objeto
	virtual void save(ostream&) const;



};
#endif