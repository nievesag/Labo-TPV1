#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"

class Game;

using namespace std;
using uint = unsigned int;

class GameObject : public SceneObject
{
	// atributos privados
private:

	// puntero al game
	Game* game;

	// metodos publicos
public:

	GameObject::GameObject(Game* game, Point2D<double> position, int width, int height, int vidas)
		: game(game), SceneObject(position, width, height, vidas)
	{
		// ??????????????????
	}

	//GameObject::~GameObject()

	// render
	void const render();

	// update
	void update();

	// save (guarda partida en un txt)
	void const save(ostream&);

	// destructora virtual para por polimorfismo
	virtual GameObject::~GameObject();

};
#endif