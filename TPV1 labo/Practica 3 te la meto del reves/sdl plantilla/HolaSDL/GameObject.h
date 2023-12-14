#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"

class SDLApplication;
class GameState;

using namespace std;
using uint = unsigned int;

class GameObject
{
	// atributos protegidos
protected:

	// puntero al game
	SDLApplication* application;

	// puntero al estado de juego (no al sdl application, al playState)
	GameState* game;

	// metodos publicos
public:
	GameObject() {}

	// constructora con el estado (botones del playstate)
	GameObject(GameState* game)
		: game(game) {

		application = nullptr;

	}

	// constructora con el application (botones fuera del playstate)
	GameObject (SDLApplication* application) : application(application) {
		game = nullptr;
	}

	// destructora virtual para por polimorfismo
	virtual ~GameObject();

	// metodos virtuales puros -> estan vacios y preparados para un override en los objetos especificos
	// ---- render ----
	virtual void render() const;

	// ---- update ----
	// actualiza
	virtual void update();

	// ---- save del objeto ----
	virtual void save(ostream& out) const;

	// anchor
	//void setListAnchor(GameList<SceneObject, true>::anchor newanc);
	
};
#endif