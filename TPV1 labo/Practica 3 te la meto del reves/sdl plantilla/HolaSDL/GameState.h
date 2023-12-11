#ifndef GAMESTATE_H
#define GAMESTATE_H

using namespace std;
using uint = unsigned int;

// includes
#include <SDL.h>		// SDL
#include <fstream>		// stream
#include <list>			// listas
#include <string>		// string

// 
#include "gameList.h"
#include "SceneObject.h"
#include "EventHandler.h"

class Game;


class GameState {


protected:
	// referencia al game
	SDLApplication* application;

	// lista de objetos del juego mediante gameList
	GameList<GameObject, true> gamelist;

	// lista de eventos a gestionar
	list<EventHandler*> eventList;

	// id para cada estado
	virtual std::string getStateID() const = 0;

public:

	// constructora normal por puntero a game
	GameState(Game* game) : application(application) {};

	// constructora por copia
	GameState(const GameState& gamestate) : application(gamestate.application) {
		gamelist = gamestate.gamelist;
		eventList = gamestate.eventList;
	};

	// ---------------------------------- BASICOS ----------------------------
	// render del estado
	virtual void render() const = 0;

	// actualiza el estado
	virtual void update() = 0;

	// guarda el estado
	virtual void save(ostream& file);

	// cuando entra
	virtual bool onEnter() = 0;

	// cuando sale
	virtual bool onExit() = 0;


	// --------------------------------- OTHER --------------------------------
	// gestiona los eventos del estado
	void handleEvent(const SDL_Event& event);

	// comento porque esta incompleta
	virtual void hasDied(GameList<GameObject, true>::anchor);


	// ---------------------------------- GETTERS Y SETTERS -------------------------
	// getter del juego
	Game getGame() const;

	virtual string getID() const = 0;


	// ---------------------- EVENTOS Y OBJETOS -------------------
	// añade un listener a eventos
	void addEventListener(SDL_Event& event);

	// añade un objeto a la lista de objetos
	void addObject(SceneObject& object);

};

#endif