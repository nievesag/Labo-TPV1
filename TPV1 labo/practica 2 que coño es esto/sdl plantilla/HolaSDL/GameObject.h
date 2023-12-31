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
	// atributos protegidos
protected:

	// puntero al game
	Game* game;

	// metodos publicos
public:

	GameObject () {}

	GameObject(Game* game)
		: game(game) {}

	// destructora virtual para por polimorfismo
	virtual ~GameObject();

	// metodos virtuales puros -> estan vacios y preparados para un override en los objetos especificos
	// ---- render ----
	virtual void render(SDL_Rect destRect) const;

	// cuando se iguala un metodo a 0 obliga a todas las clases hijas a crearlas tmb (override)
	// si no se va a quejar
	// ---- update ----
	virtual void update() = 0;

	// ---- save del objeto ----
	virtual void save(ostream& out) const = 0;
};
#endif