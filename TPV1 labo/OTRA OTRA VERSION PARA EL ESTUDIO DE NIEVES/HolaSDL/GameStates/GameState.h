#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL.h>		// SDL
#include <fstream>		// stream
#include <list>			// listas
#include <string>		// string
#include "../checkML.h"

#include "../GameObjects/gameList.h"
#include "../GameObjects/SceneObject.h"
#include "../EventHandler.h"
#include "../GameObjects/GameObject.h"

class SDLApplication;

class GameState {
protected:
	// referencia al game
	SDLApplication* application;

	// lista de objetos del juego mediante gameList
	GameList<GameObject, true> gamelist;

	// lista de punteros a oyentes
	std::list<EventHandler*> eventListeners;

public:
	// constructora normal por puntero a game
	GameState(SDLApplication* game) : application(game) {};

	// constructora por copia
	GameState(const GameState& gamestate) : application(gamestate.application) {
		gamelist = gamestate.gamelist;
	};

	virtual ~GameState() = default;

	// ------------------------- BASICOS -------------------------
	// render del estado
	virtual void render() const;

	// actualiza el estado
	virtual void update();

	// guarda el estado
	virtual void save(std::ostream& file);

	// cuando entra
	virtual bool onEnter() const;

	// cuando sale
	virtual bool onExit() const;

	// ------------------------- OTHER -------------------------
	// gestiona los eventos del estado
	virtual void HandleEvent(const SDL_Event &event);

	// comento porque esta incompleta
	virtual void hasDied(GameList<GameObject, true>::anchor);

	// ------------------------- GETTERS Y SETTERS -------------------------
	// getter del juego
	SDLApplication* getApplication() const { return application; }

	virtual std::string getID() const;

	// ------------------------- EVENTOS Y OBJETOS -------------------------
	// añade un objeto a la lista de objetos
	void addObject(GameObject* object);

	// para registrar oyentes
	void addEventListener(EventHandler* listener);
};
#endif