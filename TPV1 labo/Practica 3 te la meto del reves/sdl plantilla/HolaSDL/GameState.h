#ifndef GAMESTATE_H
#define GAMESTATE_H

using namespace std;
using uint = unsigned int;

// includes
#include <SDL.h>		// SDL
#include <fstream>		// stream
#include <list>			// listas
#include <string>		// string
#include "checkML.h"

// 
#include "gameList.h"
#include "SceneObject.h"
#include "EventHandler.h"
#include "GameObject.h"


class SDLApplication;

class GameState {
protected:
	// referencia al game
	SDLApplication* application;

	// lista de objetos del juego mediante gameList
	GameList<GameObject, true> gamelist;

	// lista de punteros a oyentes
	list<EventHandler*> eventListeners;

public:
	// constructora normal por puntero a game
	GameState(SDLApplication* game) : application(game) {};

	// constructora por copia
	GameState(const GameState& gamestate) : application(gamestate.application) {
		gamelist = gamestate.gamelist;
	};

	// ---------------------------------- BASICOS ----------------------------
	// render del estado
	virtual void render() const;

	// actualiza el estado
	virtual void update();

	// guarda el estado
	virtual void save(ostream& file);

	// cuando entra
	virtual bool onEnter();

	// cuando sale
	virtual bool onExit();

	// --------------------------------- OTHER --------------------------------
	// gestiona los eventos del estado
	virtual void HandleEvent(const SDL_Event &event);

	// comento porque esta incompleta
	virtual void hasDied(GameList<GameObject, true>::anchor);

	// ---------------------------------- GETTERS Y SETTERS -------------------------
	// getter del juego
	SDLApplication* getApplication() { return application; }

	virtual string getID() const;

	//
	SDL_Renderer getAppRenderer();

	// ---------------------- EVENTOS Y OBJETOS -------------------
	// añade un objeto a la lista de objetos
	void addObject(GameObject* object);

	// para registrar oyentes
	void addEventListener(EventHandler* listener);
};

#endif