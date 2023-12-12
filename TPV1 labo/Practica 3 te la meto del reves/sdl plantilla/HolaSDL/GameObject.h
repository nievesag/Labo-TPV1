#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"

class SDLApplication;
class PlayState;

using namespace std;
using uint = unsigned int;

class GameObject
{
	// atributos protegidos
protected:

	// puntero al game
	SDLApplication* application;

	// puntero al estado de juego (no al sdl application, al playState)
	PlayState* game;

	// metodos publicos
public:
	GameObject() {}

	GameObject(PlayState* game)
		: game(game) {}

	// destructora virtual para por polimorfismo
	virtual ~GameObject();

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