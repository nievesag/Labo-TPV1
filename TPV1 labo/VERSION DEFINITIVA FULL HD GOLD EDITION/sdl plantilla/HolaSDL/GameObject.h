#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"

#include "gameList.h"

class SDLApplication;
class GameState;
class PlayState;

class GameObject
{
	// atributos protegidos
protected:

	// puntero al game
	SDLApplication* application = nullptr;

	// puntero al estado de juego (no al sdl application, al playState)
	GameState* game = nullptr;

	// anchor
	GameList<GameObject, true>::anchor anc = nullptr;

	// metodos publicos
public:
	// constructora con el estado (botones del playstate)
	GameObject(GameState* game);

	GameObject(PlayState* game);

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
	virtual void save(std::ostream& out) const;

	// anchor
	void setListAnchor(GameList<GameObject, true>::anchor newanc) // list<SceneObject*>::iterator& newit
	{
		// setea el iterador de la posicion del objeto en la lista
		anc = newanc;
	};
	
	GameList<GameObject, true>::anchor getListAnchor() const { return anc; };
};
#endif