#ifndef GAMESTATE_H
#define GAMESTATE_H

using namespace std;
using uint = unsigned int;

// includes
#include <SDL.h>		// SDL
#include <fstream>		// stream
#include <list>			// listas

// 
#include "gameList.h"
#include "SceneObject.h"
#include "EventHandler.h"

class Game;


class GameState {


protected:
	// referencia al game
	Game* game;

	// lista de objetos del juego mediante gameList
	GameList<GameObject, true> gamelist;

	// lista de eventos a gestionar
	list<EventHandler*> eventList;


public:

	// constructora normal por puntero a game
	GameState(Game* game) : game(game) {};

	// constructora por copia
	GameState(const GameState& gamestate) : game(gamestate.game) {
		gamelist = gamestate.gamelist;
		eventList = gamestate.eventList;
	};

	// render del estado
	void render() const;

	// actualiza el estado
	void update();

	// gestiona los eventos del estado
	void handleEvent(const SDL_Event& event);

	// guarda el estado
	void save(ostream& file);

	// comento porque esta incompleta
	void hasDied(GameList<GameObject, true>::anchor);

	// getter del juego
	Game getGame() const;

	// añade un listener a eventos
	void addEventListener(SDL_Event& event);

	// añade un objeto a la lista de objetos
	void addObject(SceneObject& object);

};

#endif